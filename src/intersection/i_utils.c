/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_utils.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/13 17:38:30 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "main.h"
#include "intersection/i_plane.h"
#include "intersection/i_utils.h"
#include "utils/u_.h"

t_t4	check_t_values(t_t4 t)
{
	if (t.t1 < RAY_T_MIN)
		t.t1 = RAY_T_MAX;
	if (t.t2 < RAY_T_MIN)
		t.t2 = RAY_T_MAX;
	if (t.t3 < RAY_T_MIN)
		t.t3 = RAY_T_MAX;
	if (t.t4 < RAY_T_MIN)
		t.t4 = RAY_T_MAX;
	return (t);
}

// Quadratic Formula:
// when ax^2 + bx + c = 0
// 	  x = -b+sqrt((b)^2 - 4ac)) / 2 a
// or x = -b-sqrt((b)^2 - 4ac)) / 2 a
// if discriminant is smaller than zero it means there is no intersection;
// ray intersects two times with a 3D object
t_t4	quadratic_formula(t_xyz input1, t_xyz input2,
	float input3, float input4)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_t4	t;

	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;
	a = get_dot_product(input1, input1);
	b = 2 * get_dot_product(input1, input2);
	c = get_dot_product(input2, input2) - (pow(input3, 2) * input4);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (t);
	a = 2 * a;
	discriminant = sqrt(discriminant);
	t.t1 = (-b - discriminant) / a;
	t.t2 = (-b + discriminant) / a;
	return (t);
}

//	formules die gelden voor de cap
//	(Q3 - bottomcap)^2 < R^2
//	(Q4 - topcap)^2 < R^2
//	Qi = p + v Ti 
//	dus (lengte van Qi - cap)^2 < R^2 anders is plane_intersectie niet op de cap
//	met flag geef je aan of het de top of de bottom cap is
float	get_intersect_with_cap_planes(t_ray ray, t_object cylinder, float flag)
{
	t_object	cap;
	t_xyz		plane_intersect;
	float		capcenter_to_intersect;
	float		t;

	cap.orientation = cylinder.orientation;
	cap.center = add_vectors(cylinder.center, multiply_vector(
				cylinder.orientation, (cylinder.height / 2) * flag));
	t = get_intersection_ray_plane(ray, cap);
	plane_intersect = add_vectors(ray.origin,
			multiply_vector(ray.direction, t));
	capcenter_to_intersect = get_vector_length(
			subtract_vectors(plane_intersect, cap.center));
	if ((t < RAY_T_MIN) || (capcenter_to_intersect > cylinder.radius))
		t = RAY_T_MAX;
	return (t);
}
