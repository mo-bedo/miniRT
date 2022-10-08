/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:18:19 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace/rt_.h"
#include "ray_trace/rt_lighting.h"
#include "ray_trace/rt_pixel_put.h"
#include "intersection/i_.h"
#include "utils/u_.h"
#include "utils/u_rotate_vector.h"
#include "utils/u_vector_math.h"

// fastgraph.com/makegames/3drotation
// tutorialandexample.com/3d-rotation
t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera, float x, float y)
{
	t_xyz	vector;

	vector.x = x / (float)WINDOW_HEIGHT;
	vector.y = y / (float)WINDOW_HEIGHT;
	vector.z = camera.canvas_distance;
	return (rotate_vector(vector, camera.rotation_angles));
}

t_ray	compute_ray(t_mlx mlx, t_xyz origin, t_xyz direction)
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

	reflected_ray = compute_ray(*mlx, ray.object.position,
			compute_reflected_ray(view, ray.object.normal));
	reflected_color = get_color(mlx, reflected_ray, --depth);
	reflected_color.x = reflected_color.x * ray.object.reflective;
	reflected_color.y = reflected_color.y * ray.object.reflective;
	reflected_color.z = reflected_color.z * ray.object.reflective;
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
	ray.object.color = compute_lighting(mlx, view, ray.object);
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
			if (x == 0 && y == 0)
				print_time("rt_start_ray");
			direction = convert_2d_canvas_to_3d_coordinates(mlx->camera, x, y);
			if (x == 0 && y == 0)
				print_time("rt_direction");
			ray = compute_ray(*mlx, mlx->camera.center, direction);
			if (x == 0 && y == 0)
				print_time("rt_compute_ray");
			color = get_color(mlx, ray, RECURSION_DEPTH);
			if (x == 0 && y == 0)
				print_time("rt_get_color");
			pixel_put(&mlx->img, x, y, color);
			if (x == 0 && y == 0)
				print_time("rt_pixel_put");
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
