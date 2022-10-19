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

static void	initialize_quaternion(t_wxyz *q, float w, float x, float y, float z)
{
	q->w = w;
	q->x = x;
	q->y = y;
	q->z = z;
}

static t_wxyz	multiply_quaternion(t_wxyz q1, t_wxyz q2)
{
	t_wxyz	result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z; 
	result.x = q1.w * q2.x + q1.x * q2.w - q1.y * q2.z + q1.z * q2.y; 
	result.y = q1.w * q2.y + q1.x * q2.z + q1.y * q2.w - q1.z * q2.x; 
	result.z = q1.w * q2.z - q1.x * q2.y + q1.y * q2.x + q1.z * q2.w;
	return (result);
}

// lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final
// static t_wxyz	normalize_unit_quaternion(t_wxyz quaternion)
// {
// 	float m;

// 	m = sqrt(2 + 2 * quaternion.w);
// 	quaternion.w = 0.5 * m;
// 	quaternion.x = (1 / m) * quaternion.x;
// 	quaternion.y = (1 / m) * quaternion.y;
// 	quaternion.z = (1 / m) * quaternion.z;
// 	return (quaternion);
// }

t_xyz	get_orthogonal(t_xyz vec)
{
	float x = abs(vec.x);
	float y = abs(vec.y);
	float z = abs(vec.z);

	t_xyz	basis_vector;
	if (x < y && x < z)
		initialize_vector(&basis_vector, 1, 0, 0);
	if (y < x && y < z)
		initialize_vector(&basis_vector, 0, 1, 0);
	else
		initialize_vector(&basis_vector, 0, 0, 1);
	return (get_cross_product(vec, basis_vector));
}

// stackoverflow.com/question/1171849/finding-quaternion-representing-the-rotation-from-one-vector-to-another
static t_wxyz	get_rotation_quaternion_by_vector(t_xyz v1, t_xyz v2)
{
	t_xyz	imaginary_part;
	float	real_part;
	t_wxyz	quaternion;

	normalize_vector(&v1);
	normalize_vector(&v2);
	// real_part = get_dot_product(v1, v2);
	// if (real_part < 0.01)
	// {
	// 	real_part = 0;
	// 	if (abs(v1.x) > abs(v1.z))
	// 		initialize_vector(&imaginary_part, -v1.y, v1.x, 0);
	// 	else
	// 		initialize_vector(&imaginary_part, 0, -v1.z, v1.y);
	// }
	// else
	// 	imaginary_part = get_cross_product(v1, v2);
	// initialize_quaternion(&quaternion, real_part,
	// 		imaginary_part.x, imaginary_part.y, imaginary_part.z);
	// return (normalize_unit_quaternion(quaternion));
	if (v1.x == -v2.x && v1.y == -v2.y && v1.z == -v2.z)
	{
		real_part = 0;
		imaginary_part = get_orthogonal(v1);
		normalize_vector(&imaginary_part);
	}
	else
	{
		t_xyz half = add_vectors(v1, v2);
		normalize_vector(&half);
		real_part = get_dot_product(v1, half);
		imaginary_part = get_cross_product(v1, half);
	}
	initialize_quaternion(&quaternion, real_part,
			imaginary_part.x, imaginary_part.y, imaginary_part.z);
	return (quaternion);
}

// danceswihtcode.net/engineeringnotes/quaternions/quaternions.html
t_xyz	rotate_vector(t_xyz vector, t_xyz old_orientation, t_xyz new_orientation)
{
	t_wxyz	p;
	t_wxyz	q;
	t_wxyz	q_;
	t_wxyz	p_;
	t_xyz	result;

	initialize_quaternion(&p, 0, vector.x, vector.y, vector.z);
	q = get_rotation_quaternion_by_vector(old_orientation, new_orientation);
	initialize_quaternion(&q_, q.w, -q.x, -q.y, -q.z);
	p_ = multiply_quaternion(multiply_quaternion(q_, p), q);
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

	initialize_quaternion(&p, 0, vector.x, vector.y, vector.z);
	q = get_rotation_quaternion_by_angle(orientation, angle);
	initialize_quaternion(&q_, q.w, -q.x, -q.y, -q.z);
	p_ = multiply_quaternion(multiply_quaternion(q_, p), q);
	initialize_vector(&result, p_.x, p_.y, p_.z);
	normalize_vector(&result);
	return (result);
}

