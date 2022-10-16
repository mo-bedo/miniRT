/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/16 15:29:42 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

static bool	ray_is_parallel_to_object(t_ray ray, t_xyz orientation)
{
	return (get_dot_product(ray.direction, orientation) == 0.0);
}

// t = distance to intersection = 1 / (d . n) * (w . n - p . n)
//		d = intersection.ray.direction;
//		w = plane.intersect;
//		n = plane.normal;
//		p = intersection.ray.origin;
static double	get_distance_to_intersection(t_ray ray, t_object plane)
{
	double	dot_product;
	double	t;

	dot_product = get_dot_product(
			ray.direction, plane.orientation);
	t = get_dot_product(
			subtract_vectors(plane.center, ray.origin),
			plane.orientation) / dot_product;
	return (t);
}

float	get_intersection_ray_plane(t_ray ray, t_object plane)
{
	if (ray_is_parallel_to_object(ray, plane.orientation))
		return (RAY_T_MAX);
	return (get_distance_to_intersection(ray, plane));
}
