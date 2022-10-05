/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:10:30 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "ray_trace.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

double	get_dot_product(t_xyz v1, t_xyz v2);
t_xyz	substract_vectors(t_xyz v1, t_xyz v2);

static bool	ray_is_parallel_to_object(t_ray ray, t_xyz vector_orientation)
{
	return (get_dot_product(ray.direction, vector_orientation) == 0.0);
}

// t = distance to intersection = 1 / (d . n) * (w . n - p . n)
//		d = intersection.ray.direction;
//		w = plane.position;
//		n = plane.normal;
//		p = intersection.ray.origin;
static double	get_distance_to_intersection(t_ray ray, t_plane plane)
{
	double	dot_product;
	double	t;

	dot_product = get_dot_product(
			ray.direction, plane.vector_orientation);
	t = get_dot_product(
			substract_vectors(plane.center, ray.origin),
			plane.vector_orientation) / dot_product;
	return (t);
}

float	get_intersection_ray_plane(t_ray ray, t_plane plane)
{
	if (ray_is_parallel_to_object(ray, plane.vector_orientation))
		return (RAY_T_MAX);
	return (get_distance_to_intersection(ray, plane));
}
