/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/12 11:24:11 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

// plaatst midden van sphere in het midden van xyz
static t_ray	transpose_ray(t_ray ray, t_xyz centre)
{
	ray.origin = substract_vectors(ray.origin, centre);
	return (ray);
}

// Computes the intersection of a ray and a sphere. Returns the values
// of t for the intersections.
// Quadratic Formula:
// when ax^2 + bx + c = 0
// 	  x = -b+sqrt((b)^2 - 4ac)) / 2 a
// or x = -b-sqrt((b)^2 - 4ac)) / 2 a
// if discriminant is smaller than zero it means there is no intersection;
// ray intersects two times with sphere (distance.x and distance.y)
// t1 < RAY_T_MIN 		this means it can reflect itself
float	get_intersection_ray_sphere(t_ray ray, t_object sphere)
{
	t_uv	uv;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	ray = transpose_ray(ray, sphere.center);
	a = get_dot_product(ray.direction, ray.direction);
	b = 2 * get_dot_product(ray.origin, ray.direction);
	c = get_dot_product(ray.origin, ray.origin) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0 || a == 0)
		return (RAY_T_MAX);
	uv.u = (-b + sqrt(discriminant)) / (2 * a);
	uv.v = (-b - sqrt(discriminant)) / (2 * a);
	return (ft_min_float(uv.u, uv.v));
}
