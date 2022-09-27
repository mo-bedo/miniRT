/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by mweitenb          #+#    #+#             */
/*   Updated: 2022/09/22 12:39:01 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

#include "main.h"

t_xyz	add_vectors(t_xyz v1, t_xyz v2);
t_xyz	substract_vectors(t_xyz v1, t_xyz v2);
t_xyz	multiply_vector(t_xyz vector, double number);
t_xyz	divide_vector(t_xyz vector, double number);
double	get_vector_magnitude(t_xyz v);
double	get_2d_vector_magnitude(t_xyz v);
t_xyz	normalize_vector(t_xyz vector);
double	get_dot_product(t_xyz v1, t_xyz v2);
t_xyz	get_cross_product(t_xyz v1, t_xyz v2);
double	get_angle_between_vectors(t_xyz v1, t_xyz v2);

#endif 		// VECTOR_MATH
