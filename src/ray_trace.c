/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_trace.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 19:06:09 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace.h"
#include "lighting.h"
#include "pixel_put.h"
#include "intersection/i_.h"
#include "utils/utils.h"
#include "utils/vector_math.h"

static t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera,
	float x, float y)
{
	t_xyz	vector;

	vector.x = x * camera.viewport_size / WINDOW_HEIGHT;
	vector.y = y * camera.viewport_size / WINDOW_HEIGHT;
	vector.z = camera.projection_plane_z;
	return (vector);
}

static t_ray	compute_ray(t_mlx *mlx, t_xyz origin,
	t_xyz direction, float min_distance)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	ray.object = get_closest_intersection(mlx, ray, min_distance, RAY_T_MAX);
	return (ray);
}

static t_xyz	compute_reflections_of_reflections(t_mlx *mlx,
	t_ray ray, t_xyz view, int depth)
{
	t_ray	reflected_ray;
	t_xyz	reflected_color;
	t_xyz	reflectivenes_of_object;

	reflected_ray = compute_ray(mlx, ray.object.position,
			compute_reflected_ray(view, ray.object.normal), RAY_T_MIN);
	reflected_color = multiply_vector(get_color(mlx, reflected_ray, --depth),
			ray.object.reflective);
	reflectivenes_of_object = multiply_vector(ray.object.color,
			1 - ray.object.reflective);
	return (add_vectors(reflectivenes_of_object, reflected_color));
}

t_xyz	get_color(t_mlx *mlx, t_ray ray, int depth)
{
	t_xyz	view;
	double	light_intensity;

	if (!ray.object.object)
		return (mlx->background_color);
	view = multiply_vector(ray.direction, -1);
	light_intensity = compute_lighting(mlx, view, ray.object);
	ray.object.color = multiply_vector(ray.object.color, light_intensity);
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

	x = -WINDOW_WIDTH / 2;
	while (x < WINDOW_WIDTH / 2)
	{
		y = -WINDOW_HEIGHT / 2;
		while (y < WINDOW_HEIGHT / 2)
		{
			direction = convert_2d_canvas_to_3d_coordinates(mlx->camera, x, y);
			ray = compute_ray(mlx, mlx->camera.origin, direction,
					mlx->camera.projection_plane_z);
			color = get_color(mlx, ray, RECURSION_DEPTH);
			my_mlx_pixel_put(&mlx->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
