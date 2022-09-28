/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/28 17:10:29 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "ray_trace.h"
#include "utils/utils.h"
#include "utils/vector_math.h"

static bool	ray_is_parallel_to_object(t_ray ray, t_xyz vector_orientation)
{
	return (get_dot_product(ray.direction, vector_orientation) == 0.0);
}

// t = distance to intersection = 1 / (d . n) * (w . n - p . n)
//		d = intersection.ray.direction;
//		w = plane.position;
//		n = plane.normal;
//		p = intersection.ray.origin_point;
static double	get_distance_to_intersection(t_ray ray, t_plane plane)
{
	double	dot_product;
	double	t;

	dot_product = get_dot_product(
			ray.direction, plane.vector_orientation);
	t = get_dot_product(
			substract_vectors(plane.xyz, ray.origin_point),
			plane.vector_orientation) / dot_product;
	return (t);
}

bool	plane_intersect(t_plane plane, t_intersection *intersection)
{
	double	t;

	if (ray_is_parallel_to_object(intersection->ray, plane.vector_orientation))
		return (false);
	t = get_distance_to_intersection(intersection->ray, plane);
	if (t < RAY_T_MIN || t > intersection->t)
		return (false);
	intersection->t = t;
	intersection->plane = &plane; //hoezo moet dit?
	return (true);
}
