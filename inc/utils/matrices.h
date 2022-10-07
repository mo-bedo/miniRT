/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:52:52 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/03 13:05:47 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

# include "main.h"

// [row][column]
// typedef struct s_matrix4 {
// 	float	value[4][4];
// }	t_matrix4;

// // [row][column]
// typedef struct s_matrix8 {
// 	float value [4][8];
// }		t_matrix8;


double	get_angle_between_vectors(t_xyz v1, t_xyz v2);

t_matrix4	multiply_matrices(t_matrix4 lhs, t_matrix4 rhs);
t_matrix4	add_matrices(t_matrix4 lhs, t_matrix4 rhs);
t_matrix4	negative_matrix(t_matrix4 obj);
t_matrix4	subtract_matrices(t_matrix4 lhs, t_matrix4 rhs);
t_matrix4	set_matrix_element(t_matrix4 obj, int row, int colomn, float value);
t_matrix4	create_transform_matrix(t_xyz translation_vector, 
										t_xyz rotate, t_xyz scale);

t_matrix4	set_rotation_matrix_x_axis(t_matrix4 obj, float theta);
t_matrix4	set_rotation_matrix_y_axis(t_matrix4 obj, float theta);
t_matrix4	set_scale_matrix(t_matrix4 obj, t_xyz);
t_matrix4	set_rotation_matrix_z_axis(t_matrix4 obj, float theta);
t_matrix4	set_translation_matrix(t_matrix4 obj, t_xyz translation);
t_matrix4	set_matrix_to_identity(t_matrix4 obj);


t_xyz	apply_matrix4_to_vector(t_matrix4 m, t_xyz v);

void	print_matrix(t_matrix4 obj);
void	print_matrix8(t_matrix8 obj);

#endif 		// MATRICES_H
