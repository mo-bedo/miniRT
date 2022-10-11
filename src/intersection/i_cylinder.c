/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/10 16:01:16 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"
#include "utils/matrices.h"
#include "utils/u_invert_matrix.h"


static void	cylinder_cap(float *t, t_xyz intersect, t_xyz cyl_orientation, t_plane plane)
{
	float	a;
	float	b;
	float	temp_t;

	a = get_dot_product(substract_vectors(intersect, plane.center), plane.vector_orientation);
	b = get_dot_product(cyl_orientation, plane.vector_orientation);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return ;
	temp_t = -a / b;
	if (temp_t < 0 || *t < temp_t)
		return ;
	*t = temp_t;
}

float	get_intersection_ray_cylinder(t_closest_object *o, t_ray ray, t_cylinder cylinder)
{
	float	a;
	float	b;
	float	c;
	float	det;
	float	t_[2];

	t_xyz	temp_cross = cross(ray.direction, cylinder.vector_orientation);
	t_xyz	s_sub = substract_vectors(ray.origin, cylinder.center);
	t_xyz	temp_cross2 = cross(s_sub, cylinder.vector_orientation);

	a = get_dot_product(temp_cross, temp_cross);
	b = 2 * get_dot_product(temp_cross, temp_cross2);
	c = get_dot_product(temp_cross2, temp_cross2) - (pow(cylinder.radius, 2) 
		* get_dot_product(cylinder.vector_orientation, cylinder.vector_orientation));
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
		return (RAY_T_MAX);
	a = 2 * a;
	det = sqrt(det);
	t_[0] = (-b - det) / a;	
	t_[1] = (-b + det) / a;	


	float t = RAY_T_MAX;

	if (t_[0] >= 0 && o->t > t_[0])
		t = t_[0];
	else if (t_[1] >= 0 && o->t > t_[1])
		t = t_[1];
	if (t == RAY_T_MAX)
		return (t);	


	t_xyz intersect;

	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));

	t_plane plane;
	float	result_t = RAY_T_MAX;		// als je deze op result_t = t zet krijg je infinite cylinder

	plane.vector_orientation = cylinder.vector_orientation;
	plane.center = cylinder.center;
	cylinder_cap(&t, intersect, cylinder.vector_orientation, plane);
	if (t <= cylinder.height / 2)
		result_t = t;
	cylinder_cap(&t, intersect, multiply_vector(cylinder.vector_orientation, -1), plane);
	if (t <= cylinder.height / 2)
		result_t = t;
	return (result_t);
}
