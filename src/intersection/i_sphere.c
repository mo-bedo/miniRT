/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/16 15:29:42 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>

#include "intersection/i_utils.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"

// plaatst midden van sphere in het midden van xyz
static t_ray	transpose_ray(t_ray ray, t_xyz centre)
{
	ray.origin = subtract_vectors(ray.origin, centre);
	return (ray);
}

// Computes the intersection of a ray and a sphere. Returns the values
// of t for the intersections.
float	get_intersection_ray_sphere(t_ray ray, t_object sphere)
{
	t_t4	t;

	ray = transpose_ray(ray, sphere.center);
	t = quadratic_formula(ray.direction, ray.origin, sphere.radius, 1);
	return (ft_min_float(t.t1, t.t2));
}
