/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_vector_operators.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 19:25:43 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_VECTOR_OPERATORS_H
# define U_VECTOR_OPERATORS_H

# include "main.h"

t_xyz	add_vectors(t_xyz v1, t_xyz v2);
t_xyz	substract_vectors(t_xyz v1, t_xyz v2);
t_xyz	multiply_vector(t_xyz vector, double number);
t_xyz	divide_vector(t_xyz vector, double number);

#endif 		// VECTOR_MATH
