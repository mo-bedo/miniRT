/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_bonus.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/09 20:15:32 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace/rt_bonus.h"
#include "ray_trace/rt_lighting_bonus.h"
#include "ray_trace/rt_pixel_put_bonus.h"
#include "intersection/i_bonus.h"
#include "utils/u_bonus.h"

static t_ray	compute_ray(t_mlx mlx, t_xyz origin, t_xyz direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	ray.object = get_closest_intersection(mlx, ray, RAY_T_MAX);
	return (ray);
}

static t_xyz	compute_reflections_of_reflections(t_mlx *mlx,
	t_ray ray, t_xyz view, int depth)
{
	t_ray	reflected_ray;
	t_xyz	reflected_color;
	t_xyz	reflectivenes_of_object;

	reflected_ray = compute_ray(*mlx, ray.object.intersect,
			compute_reflected_ray(view, ray.object.normal));
	reflected_color = get_color(mlx, reflected_ray, --depth);
	reflected_color = multiply_vector(reflected_color, ray.object.reflective);
	reflectivenes_of_object = multiply_vector(ray.object.color,
			1 - ray.object.reflective);
	return (add_vectors(reflectivenes_of_object, reflected_color));
}

t_xyz	get_color(t_mlx *mlx, t_ray ray, int depth)
{
	t_xyz	view;

	if (!ray.object.type)
		return (mlx->background_color);
	view = multiply_vector(ray.direction, -1);
	compute_lighting(&ray.object, mlx, view);
	if (ray.object.reflective <= 0 || depth <= 0 || ray.object.is_inside)
		return (ray.object.color);
	return (compute_reflections_of_reflections(mlx, ray, view, depth));
}

void	ray_trace(t_mlx *mlx)
{
	t_xyz	color;
	t_xyz	direction;
	t_ray	ray;
	int		x;
	int		y;

	x = -HALF_WINDOW_WIDTH;
	while (x < HALF_WINDOW_WIDTH)
	{
		y = -HALF_WINDOW_HEIGHT;
		while (y < HALF_WINDOW_HEIGHT)
		{
			direction = convert_2d_canvas_to_3d_coordinates(mlx->camera, x, y);
			ray = compute_ray(*mlx, mlx->camera.center, direction);
			color = get_color(mlx, ray, RECURSION_DEPTH);
			pixel_put(&mlx->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
