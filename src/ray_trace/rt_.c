/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/13 21:01:28 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace/rt_.h"
#include "ray_trace/rt_lighting.h"
#include "ray_trace/rt_pixel_put.h"
#include "intersection/i_.h"
#include "utils/u_.h"

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
	if (ray.object.reflective <= 0 || depth <= 0)
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
			// if (x == 0 && y == 0)
				// print_time("rt_start_ray");
			direction = convert_2d_canvas_to_3d_coordinates(mlx->camera, x, y);
			// if (x == 0 && y == 0)
				// print_time("rt_direction");
			ray = compute_ray(*mlx, mlx->camera.center, direction);
			// if (x == 0 && y == 0)
				// print_time("rt_compute_ray");
			color = get_color(mlx, ray, RECURSION_DEPTH);
			// if (x == 0 && y == 0)
				// print_time("rt_get_color");
			pixel_put(&mlx->img, x, y, color);
			// if (x == 0 && y == 0)
				// print_time("rt_pixel_put");
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
