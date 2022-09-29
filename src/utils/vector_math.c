/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 13:51:58 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "main.h"
// #include "utils/vector_math.h"
// #include <math.h>

// // vector magnitude is de 'lengte' van de vector
// double	get_vector_magnitude(t_xyz v)
// {
// 	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
// }

// // lengte van vector in 2d
// double	get_2d_vector_magnitude(t_xyz v)
// {
// 	return (v.x * v.x + v.y * v.y + v.z * v.z);
// }

// // normal vector or unit vector is de vector gedeeld door zijn eigen magnitude.
// t_xyz	normalize_vector(t_xyz vector)
// {
// 	double	magnitude;

// 	magnitude = get_vector_magnitude(vector);
// 	return (divide_vector(vector, magnitude));
// }

// // dot product
// // is a measure of similarity 
// //  1 = same direction
// //  0 = at angle of 90 degrees
// // -1 = opposite direction
// double	get_dot_product(t_xyz v1, t_xyz v2)
// {
// 	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
// }

// // cross product
// // is a measure of difference
// //  0 = same direction
// //  1 = at angle of 90 degrees
// // -1 = opposite direction
// t_xyz	get_cross_product(t_xyz v1, t_xyz v2)
// {
// 	t_xyz	cross;

// 	cross.x = v1.y * v2.z - v1.z * v2.y;
// 	cross.y = v1.z * v2.x - v1.x * v2.z;
// 	cross.z = v1.x * v2.y - v1.y * v2.x;
// 	return (cross);
// }
