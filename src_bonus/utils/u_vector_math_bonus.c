/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_vector_math_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by mweitenb          #+#    #+#             */
/*   Updated: 2022/11/07 12:03:35 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "main_bonus.h"
#include "utils/u_vector_math_bonus.h"

float	get_vector_length(t_xyz vector)
{
	return (sqrtf(get_dot_product(vector, vector)));
}

// dot product
// is a measure of similarity 
//  1 = same direction
//  0 = at angle of 90 degrees
// -1 = opposite direction
float	get_dot_product(t_xyz v1, t_xyz v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// normal vector or unit vector is de vector gedeeld door zijn eigen magnitude.
void	normalize_vector(t_xyz *vector)
{
	float	magnitude;

	magnitude = get_vector_length(*vector);
	*vector = divide_vector(*vector, magnitude);
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

void	initialize_vector(t_xyz *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}
