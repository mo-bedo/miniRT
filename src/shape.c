/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/22 15:52:18 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "camera.h"
#include "intersect.h"
#include "math.h"
#include "shape.h"
#include "vector_math.h"

// elk object moet door zijn eigen intersect hen
// vult het intersection object met gegevens
// t = 1 / (d . n) * (w . n - p . n)
// d = direction van de ray, w = startpunt plane, p = startpunt van de ray
// als t = 0 is er geen intersect (tenzij op de plane ligt)
//		d = intersection.ray.direction;
//		w = plane.position;
//		n = plane.normal;
//		p = intersection.ray.origin_point;
bool	plane_intersect(t_plane plane, t_intersection *intersection)
{
	double	d_dot_n;
	double	t;


	d_dot_n = get_dot_product(intersection->ray.direction, plane.vector_orientation);

	if (d_dot_n == 0.0) // dan is ray evenwijdig aan plane
	{
		return (false);
	}
	//// vindt het punt van intersectie
	t = get_dot_product(substract_vectors(plane.xyz, \
			intersection->ray.origin_point), plane.vector_orientation) / d_dot_n;
	if (t < RAY_T_MIN || t > intersection->t)
	{
		return (false);
	}
	intersection->t = t;
	intersection->plane = &plane;

	return (true);
}

// raakt ray de sphere ja of nee, zou door alle objecten moeten loopen en dan
// returnen zodra hij de eerste raakt
bool	plane_does_intersect(t_plane plane, t_ray ray)
{
	double	d_dot_n;
	double	t;

	d_dot_n = get_dot_product(ray.direction, plane.vector_orientation);
	if (d_dot_n == 0.0)
		return (false);
	//// vindt het punt van intersectie
	t = get_dot_product(substract_vectors(plane.xyz, \
			ray.origin_point), plane.vector_orientation) / d_dot_n;
	if (t < RAY_T_MIN || t > ray.t_max)
		return (false);
	return (true);
}

bool	sphere_intersect(t_sphere sphere, t_intersection *intersection)
{
	t_ray	local_ray;

	local_ray = intersection->ray;
	local_ray.origin_point = substract_vectors(local_ray.origin_point, sphere.centre);

	// quadratic
	double	a = get_2d_vector_magnitude(local_ray.direction);
	double	b = 2 * get_dot_product(local_ray.direction, local_ray.origin_point);
	double	c = get_2d_vector_magnitude(local_ray.origin_point) - (sphere.radius * sphere.radius);

	double	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0.0) //// dan raakt ray de sphere niet
		return (false);

	double t1 = (-b - sqrt(discriminant)) / (2 * a);
	double t2 = (-b + sqrt(discriminant)) / (2 * a);

	if (t1 > RAY_T_MIN && t1 < intersection->t)
		intersection->t = t1;
	else if (t2 > RAY_T_MIN && t2 < intersection->t)
		intersection->t = t2;
	else
		return (false);

	intersection->sphere = &sphere;

	return (true);
}

// raakt ray de sphere ja of nee, zou door alle objecten moeten loopen en dan
// returnen zodra hij de eerste raakt

bool	sphere_does_intersect(t_sphere sphere, t_ray ray)
{
	t_ray	local_ray;

	local_ray = ray;
	local_ray.origin_point = substract_vectors(local_ray.origin_point, sphere.centre);

	// quadratic
	double	a = get_2d_vector_magnitude(local_ray.direction);
	double	b = 2 * get_dot_product(local_ray.direction, local_ray.origin_point);
	double	c = get_2d_vector_magnitude(local_ray.origin_point) - (sphere.radius * sphere.radius);

	double	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0.0) //// dan raakt ray de sphere niet
		return (false);

	double t1 = (-b - sqrt(discriminant)) / (2 * a);
	if (t1 > RAY_T_MIN && t1 < ray.t_max)
		return (true);
	double t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t2 > RAY_T_MIN && t2 < ray.t_max)
		return (true);
	return (false);
}

