/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_vector_math.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 14:58:56 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_VECTOR_MATH_H
# define U_VECTOR_MATH_H

# include "main.h"
# include "utils/u_vector_operators.h"

double	get_vector_length(t_xyz vector);
double	get_dot_product(t_xyz v1, t_xyz v2);
void	normalize_vector(t_xyz *vector);
double	get_angle_between_vectors(t_xyz v1, t_xyz v2);
t_xyz	get_cross_product(t_xyz v1, t_xyz v2);

#endif 		// VECTOR_MATH
