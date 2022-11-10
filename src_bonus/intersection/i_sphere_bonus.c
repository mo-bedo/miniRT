/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_sphere_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/07 16:45:10 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>

#include "intersection/i_utils_bonus.h"
#include "ray_trace/rt_bonus.h"
#include "utils/u_bonus.h"

static bool	camera_is_inside_sphere(t_object *sphere,
	t_xyz vector_origin_to_sphere)
{
	if (fabs(vector_origin_to_sphere.x) <= sphere->radius
		&& fabs(vector_origin_to_sphere.y) <= sphere->radius
		&& fabs(vector_origin_to_sphere.z) <= sphere->radius)
	{
		sphere->is_inside = true;
		return (true);
	}
	return (false);
}

// plaatst midden van sphere in het midden van xyz
static t_ray	transpose_ray(t_ray ray, t_xyz centre)
{
	ray.origin = subtract_vectors(ray.origin, centre);
	return (ray);
}

// Computes the intersection of a ray and a sphere. Returns the values
// of t for the intersections.
float	get_intersection_ray_sphere(t_ray ray, t_object *sphere)
{
	t_t4	t;

	ray = transpose_ray(ray, sphere->center);
	t = quadratic_formula(ray.direction, ray.origin, sphere->radius, 1);
	if (camera_is_inside_sphere(sphere, ray.origin))
		return (ft_max_float(t.t1, t.t2));
	return (ft_min_float(t.t1, t.t2));
}
