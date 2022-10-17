/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/17 17:57:33 by jbedaux          ###   ########.fr       */
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




// static	t_xyz	get_normal_vector(t_xyz vector)
// {
// 	double	magnitude;

// 	magnitude = get_vector_length(vector);
// 	vector = divide_vector(vector, magnitude);
// 	return (vector);
// }




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
		t_xyz cone_orientation,	double theta, t_xyz c_o)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_t4	t;

	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;
	theta = 1 + theta * theta;
	a = get_dot_product(ray_direction, ray_direction) - (theta) *
				pow(get_dot_product(ray_direction, cone_orientation), 2);
	b = 2 * (get_dot_product(ray_direction, c_o) - (theta) * 
				get_dot_product(ray_direction, cone_orientation) * 
				get_dot_product(c_o, cone_orientation)); 
	c = get_dot_product(c_o, c_o) - (theta) * 
				pow(get_dot_product(c_o, cone_orientation), 2.0);
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
	if ((get_dot_product(cone.orientation, 
			subtract_vectors(intersect, cone_tip)) > 0.0) && (get_dot_product(
				cone.orientation, subtract_vectors(intersect, cone.center)) < 0.0))
		return (t);
	return (RAY_T_MAX);	
}


float	get_intersect_with_cap_planes_cones(t_ray ray, t_object cylinder)
{
	t_object	cap;
	t_xyz		plane_intersect;
	float		capcenter_to_intersect;
	float		t;

	cap.orientation = cylinder.orientation;
	cap.center = add_vectors(cylinder.center, multiply_vector(
				cylinder.orientation, (cylinder.height / 2) * -1));
	t = get_intersection_ray_plane(ray, cap);
	plane_intersect = add_vectors(ray.origin,
			multiply_vector(ray.direction, t));
	capcenter_to_intersect = get_vector_length(
			subtract_vectors(plane_intersect, cap.center));
	if ((t < 0) || (capcenter_to_intersect > (cylinder.radius / 2)))
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
	t_xyz	c_o;
	
	t_xyz	center;
	
	center = cone.center;
	cone.center = add_vectors(cone.center, 
				multiply_vector(cone.orientation, cone.height / 2));
	c_o = subtract_vectors(ray.origin, cone.center);
	t = quadratic_formula_infinite_cone(ray.direction, cone.orientation, 
				atan(cone.radius / cone.height), c_o);
	t.t1 = check_cone_top_bottom(ray, cone, t.t1);		
	t.t2 = check_cone_top_bottom(ray, cone, t.t2);
	cone.center = add_vectors(cone.center, 
				multiply_vector(get_negative_vector(cone.orientation), cone.height / 2));
	t.t3 = get_intersect_with_cap_planes_cones(ray, cone);
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
static void	compute_cone_normal(t_ray ray, t_object *cone, float t, float theta)
{

	t_xyz	cone_tip;
	float	tip_to_intersect;
	float 	axis_to_intersect;
	t_xyz	axis_intersect;
	
	cone->intersect = add_vectors(ray.origin, multiply_vector(ray.direction, 
						t));
	cone_tip = add_vectors(cone->center, multiply_vector(
			get_negative_vector(cone->orientation), cone->height));
	tip_to_intersect = get_vector_length(subtract_vectors(cone->intersect, 
						cone_tip));
	axis_to_intersect = tip_to_intersect * cos(theta);
	axis_intersect = add_vectors(cone_tip, multiply_vector(cone->orientation, 
						axis_to_intersect));
	cone->normal = subtract_vectors(cone->intersect, axis_intersect);
	normalize_vector(&cone->normal);
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
	t_xyz	non_normalized_orientation;
	
	non_normalized_orientation = cone->orientation;
	// normalize_vector(&cone->orientation);
	t = compute_t_for_cone(ray, *cone);
	smallest_t = ft_min_float(t.t1, t.t2);
	if (smallest_t > t.t3)
	{
		cone->color.z = 255;
		cone->normal = cone->orientation;
		return (t.t3);
	}
	else
	{
		cone->orientation = non_normalized_orientation;
		compute_cone_normal(ray, cone, smallest_t, atan(cone->radius / cone->height));
	}	
	return (smallest_t);
}
