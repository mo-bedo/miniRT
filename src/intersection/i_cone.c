/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/24 14:46:40 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// goede uitleg!
//https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone

#include <math.h>

#include "main.h"
#include "intersection/i_utils.h"
#include "intersection/i_plane.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"

/*
			  \    /
			   \  /
				\/
				/\
		       /  \
			  /    \
	Computes t values for a infinite mirrored cone
*/
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
	theta = 1 + theta * theta;
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

/*
	Checks if intersect points are between the top and bottom of cone.
	If yes, t = valid.
// dot product is a measure of similarity 
//  1 = same direction
//  0 = at angle of 90 degrees
// -1 = opposite direction
*/
static float	check_cone_top_bottom(t_ray ray, t_object cone,
	float t, t_xyz temp_center)
{
	t_xyz	height_vector;
	t_xyz	cone_tip;
	t_xyz	intersect;
	t_xyz	tip_to_intersect;
	t_xyz	center_to_intersect;

	if (t < RAY_T_MIN || t == RAY_T_MAX)
		return (RAY_T_MAX);
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	height_vector = multiply_vector(cone.orientation, cone.height);
	cone_tip = add_vectors(temp_center, get_negative_vector(height_vector));
	tip_to_intersect = subtract_vectors(cone_tip, intersect);
	center_to_intersect = subtract_vectors(temp_center, intersect);
	if ((get_dot_product(cone.orientation, tip_to_intersect) < 0)
		&& (get_dot_product(cone.orientation, center_to_intersect) > 0))
		return (t);
	return (RAY_T_MAX);
}

float	get_intersect_with_cap_cone(t_ray ray, t_object cone)
{
	t_object	cap;
	t_xyz		intersect;
	float		capcenter_to_intersect;
	float		t;

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
	In the first line we reset to center, so it's located at the 'bottom'
	cap center.
*/
static t_t4	compute_t_for_cone(t_ray ray, t_object cone)
{
	t_t4	t;
	t_xyz	from_center_of_cone_to_origin;
	t_xyz	temp_center;
	float	theta;

	temp_center = add_vectors(cone.center,
			multiply_vector(cone.orientation, cone.height / 2));
	from_center_of_cone_to_origin = subtract_vectors(ray.origin, temp_center);
	theta = atan(cone.radius / cone.height);
	t = quadratic_formula_infinite_cone(ray.direction, cone.orientation,
			theta, from_center_of_cone_to_origin);
	t.t1 = check_cone_top_bottom(ray, cone, t.t1, temp_center);
	t.t2 = check_cone_top_bottom(ray, cone, t.t2, temp_center);
	t.t3 = get_intersect_with_cap_cone(ray, cone);
	return (t);
}

/*
				theta + cone_tip
				/|\
		       / | \
			  /  |  \	
			 /   |   \	
		    /    |    \			
		   /     |     \	
		  /      \/d    \		d = cone orientation, so orientation points 
		 /       |       \			from tip the bottom
				c				c = cone center (is now at the bottom)
	
	To get the normal we need to calculate the point on the axis with the same 
	height as the intersect(axis_intersect).  
	Then it's just normal = intersect - axis_intersect
		
						tip, theta		theta = atan(radius / heigth)
						   /|
	    tip_to_intersect  / | 			tip_to_intersect = ||tip - intersect||
						 /  | axis_to_intersect	
						/___|
				intersect	 ?(axis_intersect)

	We get there by calculating the lenght of the axis up to the point at the 
	same height as the intersect (axis_to_intersect) by using 
	cos(theta) = axis_to_intersect / tip_to_intersect,
	Since we know theta and tip_to_intersect we can get axis_to_intersect.
	axis_to_intersect = cos(theta) * tip_to_intersect
*/
static void	compute_cone_normal(t_ray ray, t_object *c, float t, float theta)
{
	float	tip_to_intersect;
	float	axis_to_intersect;
	t_xyz	axis_intersect;
	t_xyz	height_vector;
	t_xyz	tip;

	height_vector = multiply_vector(c->orientation, c->height / 2);
	tip = add_vectors(c->center, get_negative_vector(height_vector));
	c->intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	tip_to_intersect = get_vector_length(subtract_vectors(c->intersect, tip));
	axis_to_intersect = tip_to_intersect * cos(theta);
	axis_intersect = add_vectors(tip,
			multiply_vector(c->orientation, axis_to_intersect));
	c->normal = subtract_vectors(c->intersect, axis_intersect);
}

/*
				/|\
		       / | \
			  /  |  \
			 /   |   \	
		    /    |c   \			c = cone center
		   /     |     \	
		  /      \/d    \		d = cone orientation, so orientation points 
		 /       |       \			from tip the bottom
*/
float	get_intersection_ray_cone(t_ray ray, t_object *cone)
{
	t_t4	t;
	float	smallest_t;
	float	theta;

	t = compute_t_for_cone(ray, *cone);
	smallest_t = ft_min_float(t.t1, t.t2);
	if (smallest_t > t.t3)
	{
		cone->normal = cone->orientation;
		cone->is_cap = true;
		return (t.t3);
	}
	theta = atan(cone->radius / cone->height);
	compute_cone_normal(ray, cone, smallest_t, theta);
	return (smallest_t);
}
