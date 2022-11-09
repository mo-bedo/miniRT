/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_cone.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/07 14:23:17 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "main.h"
#include "intersection/i_utils.h"
#include "intersection/i_plane.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"






static t_t4	compute_t_for_cone(t_ray ray, t_object cone, float theta);





static t_t4	NEW_quadratic_formula_infinite_cone(t_xyz ray_direction,
		t_xyz orientation,	float theta, t_xyz c_o)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_t4	t;

	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;

	// theta *= 2;

	theta = (theta * theta);
	a = pow(get_dot_product(ray_direction, orientation), 2) - (theta);
//								(D . V)					 					(CO . V)		 -						D . CO				
	b = 2 * (get_dot_product(ray_direction, orientation) * get_dot_product(c_o, orientation) - get_dot_product(ray_direction, c_o) * theta);
	c = pow(get_dot_product(c_o, orientation), 2) - get_dot_product(c_o, c_o) * theta;
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (t);
	a = 2 * a;
	discriminant = sqrt(discriminant);
	t.t1 = (-b - discriminant) / a;
	t.t2 = (-b + discriminant) / a;
	return (t);
}

t_t4 	NEW_compute_t_for_cone(t_ray ray, t_object cone, float theta)
{
	t_t4	t;
	t_xyz	cone_tip;
	t_xyz	cone_tip_to_origin;

	cone_tip = add_vectors(cone.center,
			multiply_vector(cone.orientation, - cone.height / 2));
	cone_tip_to_origin = subtract_vectors(ray.origin, cone_tip);
	t = NEW_quadratic_formula_infinite_cone(ray.direction, cone.orientation, theta, cone_tip_to_origin);
	return (t);	
}


// t_t4 	get_intersect_with_cap_cone(t_ray ray, t_object cone, float theta)
// {
// 	t_t4	t;

// 	return (t);
// }


t_xyz	return_normal_vector(t_xyz vector)
{
	float	magnitude;

	magnitude = get_vector_length(vector);
	vector = divide_vector(vector, magnitude);
	return (vector);
}


//														
// angle tussen 2 vectors (A en B) berekenen je door acos ((A . B) / (vector_length(A) * (vector_length(B)))
// cos tot de macht -1 == acos()
float	get_angle_between_vectors(t_xyz v1, t_xyz v2)
{
	float	unit_v1;
	float	unit_v2;
	float	angle;

	unit_v1 = get_vector_length(v1);
	unit_v2 = get_vector_length(v2);
	angle = acos(get_dot_product(v1, v2) / (unit_v1 * unit_v2));
	return (angle);
}

static t_ray	transpose_cone_ray(t_ray ray, t_xyz center)
{
	ray.origin = subtract_vectors(ray.origin, center);
	return (ray);
}



// verschuif cone.center naar 0.0.0 punt op de as

float	get_intersection_ray_cone(t_ray ray, t_object *cone)
{
	t_t4	t;
	float	smallest_t;
	float	theta;

	t_xyz	save_cone_orientation = cone->orientation;
	t_xyz	save_ray_direction = ray.direction;

	
	// ray = transpose_cone_ray(ray, cone->center);

	t_xyz	y_axis;
	
	y_axis.x = 0;
	y_axis.y = 1;
	y_axis.z = 0;

	float angle = get_angle_between_vectors(y_axis, cone->orientation);
	// printf("%f\n", angle * (180 / PI));
	// cone->orientation = rotate_vector(cone->orientation, y_axis,  cone->orientation);

	cone->orientation = rotate_vector_by_angle(cone->orientation, y_axis, angle);
	ray.direction = rotate_vector_by_angle(ray.direction, y_axis, angle);

	theta = atan(cone->radius / cone->height);

	
	t = compute_t_for_cone(ray, *cone, theta);
	// t = NEW_compute_t_for_cone(ray,  *cone, theta);
	

	cone->orientation = save_cone_orientation;
	
	

	// t.t3 = get_intersect_with_cap_cone(ray, *cone, theta);
	smallest_t = ft_min_float(t.t1, t.t2);
	// if (smallest_t > t.t3)
	// {
	// 	cone->normal = cone->orientation;
	// 	cone->is_cap = true;
	// 	return (t.t3);
	// }
	// compute_cone_normal(ray, cone, smallest_t, theta);
	return (smallest_t);
}



/*

		PROBEREN

		https://stackoverflow.com/questions/34157690/points-of-intersection-of-vector-with-cone
		of
		http://www.illusioncatalyst.com/notes_files/mathematics/line_cone_intersection.php
		
		'ray cone intersect'
		

*/









//////////////////////////	//////////////////////////	//////////////////////////	//////////////////////////	//////////////////////////
//////////////////////////																						//////////////////////////
//////////////////////////									OUDE CODE											//////////////////////////
//////////////////////////																						//////////////////////////
//////////////////////////	//////////////////////////	//////////////////////////	//////////////////////////	//////////////////////////





// goede uitleg!
//https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone

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

// dot product is a measure of similarity 
//  1 = same direction
//  0 = at angle of 90 degrees
// -1 = opposite direction

// cone_orientation points from tip of cone to bottom, so:
// if cone_orientation and tip_to_intersect > 0:
// 		ray hits cone below the tip
static bool	intersect_below_tip(t_xyz cone_orientation,
	t_xyz intersect, t_xyz cone_tip)
{
	t_xyz	tip_to_intersect;

	tip_to_intersect = subtract_vectors(intersect, cone_tip);
	if (get_dot_product(cone_orientation, tip_to_intersect) > 0)
		return (true);
	return (false);
}

// cone_orientation points from tip of cone to bottom, so:
// if cone_orientation and bottom_to_intersect < 0:
// 		ray hits cone above the bottom
static bool	intersect_above_bottom(t_xyz cone_orientation,
	t_xyz intersect, t_xyz bottom_center)
{
	t_xyz	bottom_to_intersect;

	bottom_to_intersect = subtract_vectors(intersect, bottom_center);
	if (get_dot_product(cone_orientation, bottom_to_intersect) < 0)
		return (true);
	return (false);
}

// Checks if intersect points are between the top and bottom of cone.
// if (ray hits cone below tip and above center)
// 		ray hits cone
// else
// 		ray goes over/under cone, therefoe t = RAY_T_MAX
static t_t4	check_cone_top_bottom(t_ray ray, t_object cone,
	t_t4 t, t_xyz bottom_center)
{
	t_xyz	intersect_1;
	t_xyz	intersect_2;
	t_xyz	cone_tip;

	intersect_1 = add_vectors(ray.origin, multiply_vector(ray.direction, t.t1));
	intersect_2 = add_vectors(ray.origin, multiply_vector(ray.direction, t.t2));
	cone_tip = add_vectors(bottom_center, get_negative_vector(multiply_vector(
					cone.orientation, cone.height)));
	if (!(intersect_above_bottom(cone.orientation, intersect_1, bottom_center)
			&& intersect_below_tip(cone.orientation, intersect_1, cone_tip)))
		t.t1 = RAY_T_MAX;
	if (!(intersect_above_bottom(cone.orientation, intersect_2, bottom_center)
			&& intersect_below_tip(cone.orientation, intersect_2, cone_tip)))
		t.t2 = RAY_T_MAX;
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

// Hoe werkt de cone.radius resize?
// Waarom if ((t < 0) en niet: if ((t < RAY_T_MIN) ?
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

	height_vector = multiply_vector(c->orientation, c->height * 2);					//// waarom * 2 	?
	tip = add_vectors(c->center, get_negative_vector(height_vector));
	c->intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	tip_to_intersect = get_vector_length(subtract_vectors(c->intersect, tip));
	axis_to_intersect = tip_to_intersect * cos(theta);
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
// float	get_intersection_ray_cone(t_ray ray, t_object *cone)
// {
// 	t_t4	t;
// 	float	smallest_t;
// 	float	theta;

// 	t_xyz	save_cone_orientation = cone->orientation;

// 	t_xyz	y_axis;
	
// 	y_axis.x = 0;
// 	y_axis.y = 1;
// 	y_axis.z = 0;


// 	cone->orientation = rotate_vector(cone->orientation, y_axis,  cone->orientation);


// 	theta = atan(cone->radius / cone->height);
// 	t = compute_t_for_cone(ray, *cone, theta);
// 	t.t3 = get_intersect_with_cap_cone(ray, *cone, theta);
// 	smallest_t = ft_min_float(t.t1, t.t2);
// 	if (smallest_t > t.t3)
// 	{
// 		cone->normal = cone->orientation;
// 		cone->is_cap = true;
// 		return (t.t3);
// 	}
// 	compute_cone_normal(ray, cone, smallest_t, theta);
// 	return (smallest_t);
// }
