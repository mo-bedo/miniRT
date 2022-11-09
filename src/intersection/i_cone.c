/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_cone.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/09 18:58:02 by mweitenb      ########   odam.nl         */
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
		* pow(get_dot_product(ray_direction, orientation), 2);
	b = 2 * (get_dot_product(ray_direction, c_o) - (theta)
			* get_dot_product(ray_direction, orientation)
			* get_dot_product(c_o, orientation));
	c = get_dot_product(c_o, c_o) - (theta)
		* pow(get_dot_product(c_o, orientation), 2.0);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (t);
	a = 2 * a;
	discriminant = sqrt(discriminant);
	t.t1 = (-b - discriminant) / a;
	t.t2 = (-b + discriminant) / a;
	return (t);
}

static t_t4	compute_t_for_cone(t_ray ray, t_object cone, float theta)
{
	t_t4	t;
	t_xyz	from_center_of_cone_to_origin;
	t_xyz	bottom_center;

	bottom_center = add_vectors(cone.center,
			multiply_vector(cone.orientation, cone.height / 2));
	from_center_of_cone_to_origin = subtract_vectors(ray.origin, bottom_center);
	t = quadratic_formula_infinite_cone(ray.direction, cone.orientation,
			theta, from_center_of_cone_to_origin);
	t = check_cone_top_bottom(ray, cone, t, bottom_center);
	return (t);
}

float	get_intersect_with_cap_cone(t_ray ray, t_object cone, float theta)
{
	t_object	cap;
	t_xyz		intersect;
	float		capcenter_to_intersect;
	float		t;

	cone.radius /= 1 + theta * theta * theta;
	cap.orientation = cone.orientation;
	cap.center = add_vectors(cone.center, multiply_vector(
				cone.orientation, (cone.height / 2) * -1));
	t = get_intersection_ray_plane(ray, cap);
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	capcenter_to_intersect = get_vector_length(
			subtract_vectors(cap.center, intersect));
	if ((t < RAY_T_MIN) || (capcenter_to_intersect >= cone.radius))
		t = RAY_T_MAX;
	return (t);
}

// To get the normal we need to calculate the point on the axis with the same 
// height as the intersect(axis_intersect).  
// Then it's just normal = intersect - axis_intersect
// 					tip, theta		theta = atan(radius / heigth)
// 					   /|
//  tip_to_intersect  / | 			tip_to_intersect = ||tip - intersect||
// 					 /  | axis_to_intersect	
// 					/___|
// 			intersect	 ?(axis_intersect)
// We get there by calculating the lenght of the axis up to the point at the 
// same height as the intersect (axis_to_intersect) by using 
// cos(theta) = axis_to_intersect / tip_to_intersect,
// Since we know theta and tip_to_intersect we can get axis_to_intersect.
// axis_to_intersect = cos(theta) * tip_to_intersect
static void	compute_cone_normal(t_ray ray, t_object *c, float t, float theta)
{
	float	tip_to_intersect;
	float	axis_to_intersect;
	t_xyz	axis_intersect;
	t_xyz	height_vector;
	t_xyz	tip;

	height_vector = multiply_vector(c->orientation, c->height * 2);
	tip = add_vectors(c->center, get_negative_vector(height_vector));
	c->intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	tip_to_intersect = get_vector_length(subtract_vectors(c->intersect, tip));
	axis_to_intersect = tip_to_intersect * cosf(theta);
	axis_intersect = add_vectors(tip,
			multiply_vector(c->orientation, axis_to_intersect));
	c->normal = subtract_vectors(c->intersect, axis_intersect);
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
	t_t4	t;
	float	smallest_t;
	float	theta;

	theta = atanf(cone->radius / cone->height);
	t = compute_t_for_cone(ray, *cone, theta);
	t.t3 = get_intersect_with_cap_cone(ray, *cone, theta);
	smallest_t = ft_min_float(t.t1, t.t2);
	if (smallest_t > t.t3)
	{
		cone->normal = cone->orientation;
		cone->is_cap = true;
		return (t.t3);
	}
	compute_cone_normal(ray, cone, smallest_t, theta);
	return (smallest_t);
}
