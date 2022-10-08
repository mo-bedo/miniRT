/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_cylinder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:07:54 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

static t_ray	transpose_ray(t_ray ray, t_xyz centre)
{
	ray.origin = substract_vectors(ray.origin, centre);
	return (ray);
}

float	get_intersection_ray_cylinder(t_ray ray, t_object cylinder)
{
	ray = transpose_ray(ray, cylinder.center);
	return (RAY_T_MAX);
}
