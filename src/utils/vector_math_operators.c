/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math_operators.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 13:51:49 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "utils/vector_math.h"
#include <math.h>

// //    			B
// //	
// //        A-->-->-->-->--C
// // Vector A->C = vector A->B + vector B->C
// t_xyz	add_vectors(t_xyz v1, t_xyz v2)
// {
// 	t_xyz	add;

// 	add.x = v1.x + v2.x;
// 	add.y = v1.y + v2.y;
// 	add.z = v1.z + v2.z;
// 	return (add);
// }

// //    			B
// //	
// //        A-->-->-->-->--C
// // Vector A->B = vector A->C - vector B->C
// t_xyz	substract_vectors(t_xyz v1, t_xyz v2)
// {
// 	t_xyz	sub;

// 	sub.x = v1.x - v2.x;
// 	sub.y = v1.y - v2.y;
// 	sub.z = v1.z - v2.z;
// 	return (sub);
// }

// //        A-->-->--B
// //        A-->-->-->-->-->--C
// // 
// // multiplication of number and vector
// // multiplies the length of the vector
// // Vector A->C = 2 x Vector A->B
// t_xyz	multiply_vector(t_xyz vector, double number)
// {
// 	vector.x *= number;
// 	vector.y *= number;
// 	vector.z *= number;
// 	return (vector);
// }

// //        A-->-->--B
// //        A-->-->-->-->-->--C
// // 
// // multiplication of number and vector
// // multiplies the length of the vector
// // Vector A->B = Vector A->B / 2
// // 
// // omdat / veel meer rekenkracht kost dan * gebruken we hier een inverted number
// t_xyz	divide_vector(t_xyz vector, double number)
// {
// 	double	inverted_number;

// 	inverted_number = 1 / number;
// 	vector.x *= inverted_number;
// 	vector.y *= inverted_number;
// 	vector.z *= inverted_number;
// 	return (vector);
// }

// //												-1
// // angle tussen 2 vectors berekenen je door cosˆ   (dot van vector_normal,
// // 													dot van vector_normal 2)
// // cos tot de macht -1 == acos()
// double	get_angle_between_vectors(t_xyz v1, t_xyz v2)
// {
// 	t_xyz	unit_v1;
// 	t_xyz	unit_v2;
// 	double	angle;

// 	unit_v1 = normalize_vector(v1);
// 	unit_v2 = normalize_vector(v2);
// 	angle = acos(get_dot_product(unit_v1, unit_v2));
// 	return (angle);
// }