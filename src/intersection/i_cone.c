/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_cone.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/09 21:02:28 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "intersection/i_cone_utils.h"
#include "intersection/i_plane.h"
#include "intersection/i_utils.h"
#include "main.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"

// Computes t values for a infinite mirrored cone
static t_t4	quadratic_formula_infinite_cone(t_xyz ray_direction,
		t_xyz orientation,	float theta, t_xyz c_o)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_t4	t;

	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;
	theta = 1 + (theta * theta);
	a = get_dot_product(ray_direction, ray_direction) - (theta)
		* powf(get_dot_product(ray_direction, orientation), 2);
	b = 2 * (get_dot_product(ray_direction, c_o) - (theta)
			* get_dot_product(ray_direction, orientation)
			* get_dot_product(c_o, orientation));
	c = get_dot_product(c_o, c_o) - (theta)
		* powf(get_dot_product(c_o, orientation), 2);
	discriminant = powf(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (t);
	a = 2 * a;
	discriminant = sqrtf(discriminant);
	t.t1 = (-b - discriminant) / a;
	t.t2 = (-b + discriminant) / a;
	return (t);
}

static float	get_intersect_with_cone_side(t_ray ray,
	t_object cone, float theta)
{
	t_t4	t;
	t_xyz	from_cap_center_to_intersect;
	t_xyz	cap_center;

	cap_center = add_vectors(cone.center,
			multiply_vector(cone.orientation, cone.height / 2));
	from_cap_center_to_intersect = subtract_vectors(ray.origin, cap_center);
	t = quadratic_formula_infinite_cone(ray.direction, cone.orientation,
			theta, from_cap_center_to_intersect);
	t = check_cone_top_bottom(ray, cone, t, cap_center);
	return (ft_min_float(t.t1, t.t2));
}

// if ((t < RAY_T_MIN) || (capcenter_to_intersect >= cone.radius))
// veranderen in
// if ((t < RAY_T_MIN) || (capcenter_to_intersect > cone.radius))
// zodat we minder kans op pixelranden hebben ?
float	get_intersect_with_cap_cone(t_ray ray, t_object cone, float theta)
{
	t_object	cap;
	t_xyz		intersect;
	float		capcenter_to_intersect;
	float		t;

	cone.radius /= 1 + theta * theta * theta;
	cap.orientation = cone.orientation;
	cap.center = add_vectors(cone.center,
			multiply_vector(cap.orientation, -cone.height / 2));
	t = get_intersection_ray_plane(ray, cap);
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	capcenter_to_intersect = get_vector_length(
			subtract_vectors(cap.center, intersect));
	if ((t < RAY_T_MIN) || (capcenter_to_intersect >= cone.radius))
		t = RAY_T_MAX;
	return (t);
}

/*
			/|\				theta = angle of tip / 2
	       / | \				  = atan(radius / height)
		  /  |  \
		 /   |   \	
	    /    |c   \			c = cone center
	   /     |     \	
	  /      \/d    \		d = cone orientation, so orientation points 
	 /       |       \			from tip the bottom

if (smallest_t > t.t3)
	this means the ray hits the cone on it's cap
*/
float	get_intersection_ray_cone(t_ray ray, t_object *cone)
{
	float	t_of_closest_side;
	float	t_of_cap;
	float	theta;

	check_if_camera_is_inside_object(cone, ray);
	theta = atanf(cone->radius / cone->height);
	t_of_closest_side = get_intersect_with_cone_side(ray, *cone, theta);
	t_of_cap = get_intersect_with_cap_cone(ray, *cone, theta);
	if (t_of_cap < t_of_closest_side)
	{
		cone->is_cap = true;
		return (t_of_cap);
	}
	return (t_of_closest_side);
}
