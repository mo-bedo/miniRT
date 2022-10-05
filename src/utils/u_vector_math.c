/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_vector_math.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 19:26:59 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "utils/u_vector_math.h"
#include <math.h>

double	get_vector_length(t_xyz vector)
{
	return (sqrt(get_dot_product(vector, vector)));
}

// dot product
// is a measure of similarity 
//  1 = same direction
//  0 = at angle of 90 degrees
// -1 = opposite direction
double	get_dot_product(t_xyz v1, t_xyz v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// normal vector or unit vector is de vector gedeeld door zijn eigen magnitude.
t_xyz	normalize_vector(t_xyz vector)
{
	double	magnitude;

	magnitude = get_vector_length(vector);
	return (divide_vector(vector, magnitude));
}

// 												-1
// angle tussen 2 vectors berekenen je door cosˆ   (dot van vector_normal,
// 													dot van vector_normal 2)
// cos tot de macht -1 == acos()
// if (angle != angle) checkt of er sprake is van NaN waarde
double	get_angle_between_vectors(t_xyz v1, t_xyz v2)
{
	t_xyz	unit_v1;
	t_xyz	unit_v2;
	double	angle;

	unit_v1 = normalize_vector(v1);
	unit_v2 = normalize_vector(v2);
	angle = get_dot_product(unit_v1, unit_v2);
	if (angle != angle)
		return (0);
	return (acos(angle));
}
