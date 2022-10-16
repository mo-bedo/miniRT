/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/16 17:38:30 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// goede uitleg!
// https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/

#include "intersection/i_utils.h"
#include "intersection/i_cylinder.h"
#include "main.h"
#include "ray_trace/rt_.h"
#include "utils/u_vector_math.h"
#include "utils/u_compare.h"

#include <math.h>

/*
			  \    /
			   \  /
				\/
				/\
		       /  \
			  /    \	   
	Computes t values for a infinite mirrored cone
*/
static t_t4	quadratic_formula_infinite_cone(t_xyz ray_direction, t_xyz cone_orientation,
				double theta, t_xyz c_o)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_t4	t;

	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;
	a = get_dot_product(ray_direction, ray_direction) - (1.0 + theta * theta) *
				powf(get_dot_product(ray_direction, cone_orientation), 2);
	b = 2 * (get_dot_product(ray_direction, c_o) - (1.0 + theta * theta) * 
				get_dot_product(ray_direction, cone_orientation) * 
				get_dot_product(c_o, cone_orientation)); 
	c = get_dot_product(c_o, c_o) - (1.0 + theta * theta) * 
				powf(get_dot_product(c_o, cone_orientation), 2.0);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (t);
	a = 2 * a;
	discriminant = sqrt(discriminant);
	t.t1 = (-b - discriminant) / a;
	t.t2 = (-b + discriminant) / a;
	return (t);
}

/*
	Checks if intersect points are beyond the top and bottom of cone.
	If yes, t = invalid.
*/
static float	check_cone_top_bottom(t_ray ray, t_object cone, float t)
{
	t_xyz	intersect;
	t_xyz	cone_tip;

	if (t <= 0 || t == RAY_T_MAX)
		return (RAY_T_MAX);
	cone_tip = add_vectors(cone.center, multiply_vector(
			get_negative_vector(cone.orientation), cone.height));
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	if (get_dot_product(cone.orientation, 
			subtract_vectors(intersect, cone_tip)) < 0.0)
		return (RAY_T_MAX);
	if (get_dot_product(cone.orientation, 
				subtract_vectors(intersect, cone.center)) > 0.0)
			return (RAY_T_MAX);
	return (t);	
}

/*
	theta
	 |\
	 | \
   h |  \
	 |   \
	 |____\
        r
	To get theta we simple use tan = r / h, since we know height and radius
	
	so theta = tanˆ-1(r/h)
*/
static t_t4	compute_t_for_cone(t_ray ray, t_object cone)
{
	t_t4	t;
	t_xyz	c_o;

	cone.center = add_vectors(cone.center, 
				multiply_vector(cone.orientation, cone.height / 2));
	c_o = subtract_vectors(ray.origin, cone.center);
	t = quadratic_formula_infinite_cone(ray.direction, cone.orientation, 
				atan(cone.radius / cone.height), c_o);
	t.t1 = check_cone_top_bottom(ray, cone, t.t1);		
	t.t2 = check_cone_top_bottom(ray, cone, t.t2);
	cone.center = add_vectors(cone.center, 
				multiply_vector(get_negative_vector(cone.orientation), cone.height / 2));
	t.t3 = get_intersect_with_cap_planes(ray, cone, -1);
	return (t);
}


/*


If I is the intersection point on the cone's surface and you know its coordinates,
 and P is the vertex of the cone, whose coordinates you also know, then this is enough:

Normal = (axis x PI) x PI
Normal = Normal / norm(Normal)

where axis is the vector aligned with the axis of the cone.

*/
static void	compute_cone_normal(t_ray ray, t_object *cone, float t)
{
	t_xyz	cone_tip;
	t_xyz	normal;
	t_xyz	pi;
	
	cone->intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	cone_tip = add_vectors(cone->center, multiply_vector(
			get_negative_vector(cone->orientation), cone->height));
	pi = subtract_vectors(cone_tip, cone->orientation);		
	normal = get_cross_product(get_cross_product(cone->orientation, pi), pi);
	cone->normal = divide_vector(normal, get_vector_length(normal));
}

/*

*/

float	get_intersection_ray_cone(t_ray ray, t_object *cone)
{
	t_t4	t;
	float	smallest_t;
	t_xyz	non_normalized_orientation;
	
	non_normalized_orientation = cone->orientation;
	normalize_vector(&cone->orientation);
	t = compute_t_for_cone(ray, *cone);
	smallest_t = ft_min_float(t.t1, t.t2);
	if (smallest_t > t.t3)
	{
		cone->normal = cone->orientation;			//// gaat misschien mis als we gaan object 'live' gaan draaien ?
		return (t.t3);
	}
	else
	{
		cone->orientation = non_normalized_orientation;
		compute_cone_normal(ray, cone, smallest_t);	
	}	
	return (smallest_t);
}
