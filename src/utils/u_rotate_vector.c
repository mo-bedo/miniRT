/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_trace.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 19:21:13 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

// fastgraph.com/makegames/3drotation
// tutorialandexample.com/3d-rotation
# define PI 3.14f

double	convert_to_radian(double angle)
{
	// angle = angle * (PI / 180);
	// angle.x = angle.x * (PI / 180);
	// angle.y = angle.y * (PI / 180);
	// angle.z = angle.z * (PI / 180);
	return (angle);
}

t_xyz	rotate_along_x_axis(t_xyz old, double angle)
{
	t_xyz	new;

	new.x = old.x;
	new.y = old.y * cos(angle) - old.z * sin(angle);
	new.z = old.y * sin(angle) + old.z * cos(angle);
	return (normalize_vector(new));
}

t_xyz	rotate_along_y_axis(t_xyz old, double angle)
{
	t_xyz	new;

	new.x = old.x * cos(angle) + old.z * sin(angle);
	new.y = old.y;
	new.z = -old.x * sin(angle) + old.z * cos(angle);
	return (normalize_vector(new));
}

t_xyz	rotate_along_z_axis(t_xyz old, double angle)
{
	t_xyz	new;

	new.x = old.x * cos(angle) - old.y * sin(angle);
	new.y = old.x * sin(angle) + old.y * cos(angle);
	new.z = old.z;
	return (normalize_vector(new));
}

t_xyz	rotate_vector(t_xyz old, t_xyz angles)
{
	t_xyz	new;

	new = rotate_along_x_axis(old, convert_to_radian(angles.x));
	new = rotate_along_y_axis(new, convert_to_radian(angles.y));
	new = rotate_along_z_axis(new, convert_to_radian(angles.z));
	return ((new));
}


// t_xyz	transform_vector(t_mlx mlx, t_xyz old, t_xyz vector_orientation)
// {
// 	t_xyz	original_basis;
// 	float	transformation_matrix[3][3];

// 	original_basis = mlx->camera.vector_orientation;
// 	new_basis = vector_orientation;
// 	// where i_hat lands
// 	transformation_matrix[0][0] = original_basis.x;
// 	transformation_matrix[1][0] = original_basis.y;
// 	transformation_matrix[2][0] = original_basis.z;
// 	// where j_hat lands
// 	transformation_matrix[0][1] = original_basis.x;
// 	transformation_matrix[1][1] = original_basis.y;
// 	transformation_matrix[2][1] = original_basis.z;
// 	// where k_hat lands
// 	transformation_matrix[0][2] = original_basis.x;
// 	transformation_matrix[1][2] = original_basis.y;
// 	transformation_matrix[2][2] = original_basis.z;
// }