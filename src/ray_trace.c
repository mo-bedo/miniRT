/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_trace.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:41:59 by mweitenb      ########   odam.nl         */
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

// Converts 2D canvas coordinates to 3D viewport coordinates.
t_xyz	canvas_to_viewport(t_camera camera, float x, float y)
{
	t_xyz	vector;

	vector.x = x * camera.viewport_size / WINDOW_HEIGHT;
	vector.y = y * camera.viewport_size / WINDOW_HEIGHT;
	vector.z = camera.projection_plane_z;
	return (vector);
}

// TO DO: expand to planes etc
t_xyz TraceRay(t_mlx *mlx, t_xyz origin, t_xyz direction, float min_distance, float max_distance, int depth)
{
	t_ray				ray;
	t_closest_object	object;

	ray.origin = origin;
	ray.direction = direction;

	// get closest object
	object = get_closest_intersection(mlx, ray, min_distance, max_distance);
	if (!object.object)
		return (mlx->background_color);

	// compute normal
	t_xyz normal = substract_vectors(object.position, object.sphere->center);
	normal = normalize_vector(normal);

	// calculate lightning
	t_xyz view = multiply_vector(direction, -1);

	// color of object
	t_xyz local_color = multiply_vector(object.sphere->color,
			compute_lighting(mlx, normal, view, object));
	if (object.sphere->reflective <= 0 || depth <= 0)
		return (local_color);

	// compute reflections of reflections
	t_xyz reflected_ray = get_reflection_of_vector_1_towards_vector_2(view, normal);
	t_xyz reflected_color = TraceRay(mlx, object.position, reflected_ray, RAY_T_MIN, RAY_T_MAX, depth - 1);

	// ?
	return (add_vectors(multiply_vector(local_color, 1 - object.sphere->reflective),
			multiply_vector(reflected_color, object.sphere->reflective)));
}

void	ray_trace(t_mlx *mlx)
{
	t_xyz	direction;
	t_xyz	color;
	int		x;
	int		y;

	x = -WINDOW_WIDTH / 2;
	while (x < WINDOW_WIDTH / 2)
	{
		y = -WINDOW_HEIGHT / 2;
		while (y < WINDOW_HEIGHT / 2)
		{
			direction = canvas_to_viewport(mlx->camera, x, y);
			color = TraceRay(mlx, mlx->camera.origin,
					direction, 1, RAY_T_MAX, RECURSION_DEPTH);
			my_mlx_pixel_put(&mlx->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
