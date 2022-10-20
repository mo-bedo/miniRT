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
#include <stdlib.h>

#include "main.h"
#include "utils/u_.h"

static t_xyz	get_orthogonal(t_xyz vec)
{
	float	x;
	float	y;
	float	z;
	t_xyz	basis_vector;

	x = abs(vec.x);
	y = abs(vec.y);
	z = abs(vec.z);
	if (x < y && x < z)
		initialize_vector(&basis_vector, 1, 0, 0);
	if (y < x && y < z)
		initialize_vector(&basis_vector, 0, 1, 0);
	else
		initialize_vector(&basis_vector, 0, 0, 1);
	return (get_cross_product(vec, basis_vector));
}

// stackoverflow.com/question/1171849/
// finding-quaternion-representing-the-rotation-from-one-vector-to-another
static t_wxyz	get_rotation_quaternion_by_vector(t_xyz v1, t_xyz v2)
{
	t_xyz	imaginary_part;
	float	real_part;
	t_wxyz	quaternion;
	t_xyz	half;

	if (v1.x == -v2.x && v1.y == -v2.y && v1.z == -v2.z)
	{
		real_part = 0;
		imaginary_part = get_orthogonal(v1);
		normalize_vector(&imaginary_part);
	}
	else
	{
		half = add_vectors(v1, v2);
		normalize_vector(&half);
		real_part = get_dot_product(v1, half);
		imaginary_part = get_cross_product(v1, half);
	}
	initialize_quaternion(&quaternion, real_part, imaginary_part);
	return (quaternion);
}

// danceswihtcode.net/engineeringnotes/quaternions/quaternions.html
t_xyz	rotate_vector(t_xyz vector,
	t_xyz old_orientation, t_xyz new_orientation)
{
	t_wxyz	p;
	t_wxyz	q;
	t_wxyz	q_;
	t_wxyz	p_;
	t_xyz	result;

	initialize_quaternion(&p, 0, vector);
	q = get_rotation_quaternion_by_vector(old_orientation, new_orientation);
	q_.w = q.w;
	q_.x = -q.x;
	q_.y = -q.y;
	q_.z = -q.z;
	p_ = multiply_quaternion(multiply_quaternion(q, p), q_);
	initialize_vector(&result, p_.x, p_.y, p_.z);
	return (result);
}

static t_wxyz	get_rotation_quaternion_by_angle(t_xyz orientation, float angle)
{
	t_wxyz	result;

	result.w = cos(angle / 2);
	result.x = orientation.x * sin(angle / 2);
	result.y = orientation.y * sin(angle / 2);
	result.z = orientation.z * sin(angle / 2);
	return (result);
}

// danceswihtcode.net/engineeringnotes/quaternions/quaternions.html
t_xyz	rotate_vector_by_angle(t_xyz vector, t_xyz orientation, float angle)
{
	t_wxyz	p;
	t_wxyz	q;
	t_wxyz	q_;
	t_wxyz	p_;
	t_xyz	result;

	initialize_quaternion(&p, 0, vector);
	q = get_rotation_quaternion_by_angle(orientation, angle);
	q_.w = q.w;
	q_.x = -q.x;
	q_.y = -q.y;
	q_.z = -q.z;
	p_ = multiply_quaternion(multiply_quaternion(q_, p), q);
	initialize_vector(&result, p_.x, p_.y, p_.z);
	normalize_vector(&result);
	return (result);
}
