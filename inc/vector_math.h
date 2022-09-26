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

double	angle_between_vector(t_xyz v1, t_xyz v2);
t_xyz	vector_addition(t_xyz v1, t_xyz v2);
t_xyz	vector_cross(t_xyz v1, t_xyz v2);
double	vector_dot(t_xyz v1, t_xyz v2);
double	vector_magnitude(t_xyz v);
double	vector_magnitude2(t_xyz v);
t_xyz	vector_multi(t_xyz v, double m);
t_xyz	vector_subtraction(t_xyz v1, t_xyz v2);
t_xyz	vector_normal(t_xyz v);

#endif