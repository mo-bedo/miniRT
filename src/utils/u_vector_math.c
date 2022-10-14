/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_vector_math.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 15:01:10 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "main.h"
#include "utils/u_vector_math.h"

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
void	normalize_vector(t_xyz *vector)
{
	double	magnitude;

	magnitude = get_vector_length(*vector);
	*vector = divide_vector(*vector, magnitude);
}

// 												-1
// angle tussen 2 vectors berekenen je door cosˆ   (dot van vector_normal,
// 													dot van vector_normal 2)
// cos tot de macht -1 == acos()
// if (angle != angle) checkt of er sprake is van NaN waarde
double	get_angle_between_vectors(t_xyz v1, t_xyz v2)
{
	double	angle;

	normalize_vector(&v1);
	normalize_vector(&v2);
	angle = get_dot_product(v1, v2);
	if (angle != angle)
		return (0);
	return (acos(angle));
}

// cross product
// is a measure of difference
//  0 = same direction
//  1 = at angle of 90 degrees
// -1 = opposite direction
t_xyz	get_cross_product(t_xyz v1, t_xyz v2)
{
	t_xyz	cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}
