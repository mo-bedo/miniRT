/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_rotate_vector.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:08:42 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "utils/u_.h"

// fastgraph.com/makegames/3drotation
// tutorialandexample.com/3d-rotation
t_xyz	rotate_along_x_axis(t_xyz old, double angle)
{
	t_xyz	new;
	double	sin_angle;
	double	cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	new.x = old.x;
	new.y = old.y * cos_angle - old.z * sin_angle;
	new.z = old.y * sin_angle + old.z * cos_angle;
	return (new);
}

t_xyz	rotate_along_y_axis(t_xyz old, double angle)
{
	t_xyz	new;
	double	sin_angle;
	double	cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	new.x = old.x * cos_angle + old.z * sin_angle;
	new.y = old.y;
	new.z = -old.x * sin_angle + old.z * cos_angle;
	return (new);
}

t_xyz	rotate_along_z_axis(t_xyz old, double angle)
{
	t_xyz	new;
	double	sin_angle;
	double	cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	new.x = old.x * cos_angle - old.y * sin_angle;
	new.y = old.x * sin_angle + old.y * cos_angle;
	new.z = old.z;
	return (new);
}

t_xyz	rotate_vector(t_xyz old, t_xyz angles)
{
	t_xyz	new;

	new = rotate_along_x_axis(old, angles.x);
	new = rotate_along_y_axis(new, angles.y);
	new = rotate_along_z_axis(new, angles.z);
	return (new);
}
