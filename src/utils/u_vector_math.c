/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 19:03:53 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "utils/u_vector_math.h"
#include <math.h>

//    			B
//	
//        A-->-->-->-->--C
// Vector A->C = vector A->B + vector B->C
t_xyz	add_vectors(t_xyz v1, t_xyz v2)
{
	t_xyz	add;

	add.x = v1.x + v2.x;
	add.y = v1.y + v2.y;
	add.z = v1.z + v2.z;
	return (add);
}

//    			B
//	
//        A-->-->-->-->--C
// Vector A->B = vector A->C - vector B->C
t_xyz	substract_vectors(t_xyz v1, t_xyz v2)
{
	t_xyz	sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

//        A-->-->--B
//        A-->-->-->-->-->--C
// 
// multiplication of number and vector
// multiplies the length of the vector
// Vector A->C = 2 x Vector A->B
t_xyz	multiply_vector(t_xyz vector, double number)
{
	vector.x *= number;
	vector.y *= number;
	vector.z *= number;
	return (vector);
}

//        A-->-->-->-->-->--C
//        A-->-->--B
// 
// divide vector by number
// Vector A->B = Vector A->C / 2
// 
// omdat / veel meer rekenkracht kost dan * gebruken we hier een inverted number
t_xyz	divide_vector(t_xyz vector, double number)
{
	double	inverted_number;

	inverted_number = 1 / number;
	vector.x *= inverted_number;
	vector.y *= inverted_number;
	vector.z *= inverted_number;
	return (vector);
}

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
double	get_angle_between_vectors(t_xyz v1, t_xyz v2)
{
	t_xyz	unit_v1;
	t_xyz	unit_v2;
	double	angle;

	unit_v1 = normalize_vector(v1);
	unit_v2 = normalize_vector(v2);
	angle = get_dot_product(unit_v1, unit_v2);
	// DEBUG_STR("");
	// DEBUG_DOUBLE(unit_v1.x);
	// DEBUG_DOUBLE(unit_v1.y);
	// DEBUG_DOUBLE(unit_v1.z);
	// DEBUG_DOUBLE(unit_v2.x);
	// DEBUG_DOUBLE(unit_v2.y);
	// DEBUG_DOUBLE(unit_v2.z);
	// DEBUG_DOUBLE(angle);
	if (angle != angle)
		return (0);
	return (acos(angle));
}

t_xyz	get_angle_over_the_axes(t_xyz vector1, t_xyz vector2)
{
	t_xyz	angles;
	t_xyz	v1;
	t_xyz	v2;

	v1 = vector1;
	v1.x = 0;
	v2 = vector2;
	v2.x = 0;
		angles.x = get_angle_between_vectors(v1, v2);
	if (v2.z >= 0 && v1.y < v2.y)
		angles.x *= -1;
	if (v2.z < 0 && v1.y > v2.y)
		angles.x *= -1;

	v1 = vector1;
	v1.y = 0;
	v2 = vector2;
	v2.y = 0;
		angles.y = get_angle_between_vectors(v1, v2);
	if (v2.z >= 0 && v1.x > v2.x)
		angles.y *= -1;
	if (v2.z < 0 && v1.x < v2.x)
		angles.y *= -1;

	angles.z = 0;
	if (v2.z < 0)
	{
		angles.y -= (180 * (3.14 / 180));
		angles.z -= -180 * (3.14 / 180);
	}
	return (angles);
}