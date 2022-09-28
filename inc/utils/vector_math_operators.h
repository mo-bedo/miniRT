/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math_operators.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/28 15:01:38 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_OPERATORS_H
# define VECTOR_MATH_OPERATORS_H

# include "main.h"

t_xyz	add_vectors(t_xyz v1, t_xyz v2);
t_xyz	substract_vectors(t_xyz v1, t_xyz v2);
t_xyz	multiply_vector(t_xyz vector, double number);
t_xyz	divide_vector(t_xyz vector, double number);
double	get_angle_between_vectors(t_xyz v1, t_xyz v2);

#endif 		// VECTOR_MATH
