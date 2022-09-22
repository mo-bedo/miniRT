/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by mweitenb          #+#    #+#             */
/*   Updated: 2022/09/22 12:39:01 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

t_vec	vector_multi(t_vec v, double m)
{
	v.x *= m;
	v.y *= m;
	v.z *= m;
	return (v);
}

//    				B
//
//        A
//					C
//
// AB + BC = AC
// AB - BC = CA
t_vec	vector_addition(t_vec v1, t_vec v2)
{
	t_vec	add;

	add.x = v1.x + v2.x;
	add.y = v1.y + v2.y;
	add.z = v1.z + v2.z;
	return (add);
}

t_vec	vector_subtraction(t_vec v1, t_vec v2)
{
	t_vec	sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

// vector magnitude is de 'lengte' van de vector
double	vector_magnitude(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vector_magnitude2(t_vec v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

// normal vector or unit vector is de vector gedeeld door zijn eigen magnitude.
// omdat / veel meer rekenkracht kost dan * gebruken we hier een inverted
// magnitude
t_vec	vector_normal(t_vec v)
{
	double	v_magnitude;
	double	inv_magnitude;

	v_magnitude = vector_magnitude(v);
	if (v_magnitude > 0)
	{
		inv_magnitude = 1 / v_magnitude;
		v.x *= inv_magnitude;
		v.y *= inv_magnitude;
		v.z *= inv_magnitude;
	}
	return (v);
}

// dot product
double	vector_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vector_cross(t_vec v1, t_vec v2)
{
	t_vec	cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}

//												-1
// angle tussen 2 vectors berekenen je door cosˆ   (dot van vector_normal,
// 													dot van vector_normal 2)
// cos tot de macht -1 == acos()
double	angle_between_vector(t_vec v1, t_vec v2)
{
	t_vec	unit_v1;
	t_vec	unit_v2;
	double	angle;

	unit_v1 = vector_normal(v1);
	unit_v2 = vector_normal(v2);
	angle = acos(vector_dot(unit_v1, unit_v2));
	return (angle);
}


