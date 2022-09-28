/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 12:38:51 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/28 12:24:43 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "camera.h"
#include "main.h"
#include "vector_math.h"

// vector Ray direction = normalized(camera.forward + x_vector + y_vector);
// x_vector = camera.right * x * camera.width
// y_vector = camera.up * y * camera.height
t_ray	make_ray(int x, int y, t_camera camera)
{
	t_ray	ray;
	t_xyz	x_vector;
	t_xyz	y_vector;

	//// omzetten van 'apart -1 tot +1 coord systeem' naar screen coord
	x = (2.0 * x) / WINDOW_WIDTH - 1.0;
	y = (-2.0 * y) / WINDOW_HEIGHT + 1.0;
	x_vector = multiply_vector(camera.right, (x * camera.width));
	y_vector = multiply_vector(camera.up, (y * camera.height));
	ray.direction = normalize_vector(
			add_vectors(add_vectors(camera.forward, x_vector), y_vector));
	ray.origin_point = camera.origin_point;
	ray.t_max = RAY_T_MAX;
	return (ray);
}
