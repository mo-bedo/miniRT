/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 18:09:06 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "main.h"

t_xyz	add_vectors(t_xyz v1, t_xyz v2);
t_xyz	substract_vectors(t_xyz v1, t_xyz v2);
t_xyz	multiply_vector(t_xyz vector, double number);
double	get_vector_length(t_xyz vector);
double	get_dot_product(t_xyz v1, t_xyz v2);
t_xyz	normalize_vector(t_xyz vector);
double	get_angle_between_vectors(t_xyz v1, t_xyz v2);
t_xyz	get_angle_over_the_axes(t_xyz vector1, t_xyz vector2);

#endif 		// VECTOR_MATH