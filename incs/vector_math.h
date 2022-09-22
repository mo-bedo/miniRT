/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:20:58 by mweitenb          #+#    #+#             */
/*   Updated: 2022/09/22 12:38:02 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "main.h"

double	angle_between_vector(t_vec v1, t_vec v2);
t_vec	vector_addition(t_vec v1, t_vec v2);
t_vec	vector_cross(t_vec v1, t_vec v2);
double	vector_dot(t_vec v1, t_vec v2);
double	vector_magnitude(t_vec v);
t_vec	vector_multi(t_vec v, double m);
t_vec	vector_subtraction(t_vec v1, t_vec v2);
t_vec	vector_normal(t_vec v);

#endif