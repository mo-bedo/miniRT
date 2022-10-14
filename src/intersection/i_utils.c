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
	double input3, double input4)
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
