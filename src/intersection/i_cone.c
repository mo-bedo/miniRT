/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/11/09 17:15:16 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "main.h"
#include "intersection/i_utils.h"
#include "intersection/i_plane.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"


#include <math.h>
#include <stdlib.h>

#include "main.h"
#include "utils/u_.h"

float	get_intersect_with_cap_cone(t_ray ray, t_object cone, float theta);

static void compute_cone_normal(t_object *cone, float theta)
{
    t_xyz   b;
    t_xyz   c;
    initialize_vector(&b, 0, cone->intersect.y, 0);
    initialize_vector(&c, 0, b.y/tan(theta), 0);
    t_xyz cb = subtract_vectors(c, b);
    t_xyz ba = subtract_vectors(b, cone->intersect);
    cone->normal = subtract_vectors(cb, ba);
}

static t_xyz	get_orthogonal(t_xyz vec)
{
	float	x;
	float	y;
	float	z;
	t_xyz	basis_vector;

	x = fabsf(vec.x);
	y = fabsf(vec.y);
	z = fabsf(vec.z);
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

static t_wxyz	get_rotation_quaternion_by_angle(t_xyz orientation, float angle)
{
	t_wxyz	result;

	result.w = cos(angle / 2);
	result.x = orientation.x * sin(angle / 2);
	result.y = orientation.y * sin(angle / 2);
	result.z = orientation.z * sin(angle / 2);
	return (result);
}


/*


	nieuwe quadratic formula gaat volgens deze website

	http://www.illusioncatalyst.com/notes_files/mathematics/line_cone_intersection.php


*/

static t_t4	NEW_quadratic_formula_infinite_cone(t_ray ray, t_xyz ray_direction,
		t_xyz orientation,	float theta, t_xyz c_o, t_xyz cone_center, t_xyz ray_pos, t_object cone)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_t4	t;
	
	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;

	t_xyz	tip_of_cone = add_vectors(cone.center, multiply_vector(cone.orientation, -cone.height));
	t_xyz	bottom_of_cone = add_vectors(cone.center, multiply_vector(cone.orientation, cone.height));

	t_xyz h = subtract_vectors(bottom_of_cone, tip_of_cone);
	t_xyz v = ray_direction;
	t_xyz w = subtract_vectors(ray_pos, tip_of_cone);
	float m = (cone.radius * cone.radius) / (get_vector_length(h) * get_vector_length(h));


	h = divide_vector(subtract_vectors(bottom_of_cone, tip_of_cone), get_vector_length(subtract_vectors(bottom_of_cone, tip_of_cone)));

	a = get_dot_product(v, v) - m * (pow(get_dot_product(v, h), 2)) - pow(get_dot_product(v, h), 2);
	b = 2 * (get_dot_product(v, w) - m * get_dot_product(v, h) * get_dot_product(w, h) - get_dot_product(v, h) * get_dot_product(w, h));
	c = get_dot_product(w, w) - m * (pow(get_dot_product(w, h), 2)) - (pow(get_dot_product(w, h), 2));

	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (t);
	a = 2 * a;
	discriminant = sqrt(discriminant);
	t.t1 = (-b - discriminant) / a;
	t.t2 = (-b + discriminant) / a;

	if (t.t1 < RAY_T_MIN)
		t.t1 = RAY_T_MAX;
	if (t.t2 < RAY_T_MIN)
		t.t2 = RAY_T_MAX;
	float t_ = ft_min_float(t.t1, t.t2);

	t_xyz	intersect = add_vectors(ray_pos, multiply_vector(ray_direction, t_));

	t_xyz 	intersect_to_tip = subtract_vectors(intersect, tip_of_cone);

	float	test = get_dot_product(intersect_to_tip, h);

	
	/*	
	if (0 <= (L.int - H) . h <= h.length)
	 	cone surface hit	
	*/	
	if (0 >= test && test <= get_vector_length(h))
		return t;

	/*
	if (L.int - H) . h > h.length)
		below cone base, test for cap intersect
	*/
	if (test > get_vector_length(h))
	{
		
		t.t1 = RAY_T_MAX;
		t.t2 = RAY_T_MAX;
		// waardes van t1 en t2 op max???????
		t.t3 = get_intersect_with_cap_cone(ray, cone, theta);
		return t;
	}

	/*
	if (L.int - H) . h < 0)
		intersect is boven top cone, dus geen intersecct
	*/
	if (test < 0)
	{
		t.t1 = RAY_T_MAX;
		t.t2 = RAY_T_MAX;
		t.t3 = RAY_T_MAX;
	}

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
	t = NEW_quadratic_formula_infinite_cone(ray, ray.direction, cone.orientation, theta, cone_tip_to_origin, cone.center, ray.origin, cone);
	return (t);	
}

t_xyz	return_normal_vector(t_xyz vector)
{
	float	magnitude;

	magnitude = get_vector_length(vector);
	vector = divide_vector(vector, magnitude);
	return (vector);
}

static t_t4	compute_t_for_cone(t_ray ray, t_object cone, float theta)
{
	t_t4	t;
	t_xyz	from_center_of_cone_to_origin;
	t_xyz	bottom_center;

	bottom_center = add_vectors(cone.center,
			multiply_vector(cone.orientation, cone.height / 2));
	from_center_of_cone_to_origin = subtract_vectors(ray.origin, bottom_center);
	t = NEW_quadratic_formula_infinite_cone(ray, ray.direction, cone.orientation,
			theta, from_center_of_cone_to_origin, cone.center, ray.origin, cone);
	return (t);
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

	t_xyz	y_axis;
	
	y_axis.x = 0;
	y_axis.y = 1;
	y_axis.z = 0;


	t_wxyz	p;
	t_wxyz	q;
	t_wxyz	q_;
	t_wxyz	p_;
	t_xyz	result;

	t_xyz	rotated_cone;
	t_xyz	rotated_ray_direction;
	
	initialize_quaternion(&p, 0, cone->orientation);
	q = get_rotation_quaternion_by_vector(cone->orientation, y_axis);
	q_.w = q.w;
	q_.x = -q.x;
	q_.y = -q.y;
	q_.z = -q.z;
	p_ = multiply_quaternion(multiply_quaternion(q, p), q_);
	initialize_vector(&rotated_cone, p_.x, p_.y, p_.z);
	cone->orientation = rotated_cone;		
	initialize_quaternion(&p, 0, ray.direction);
	p_ = multiply_quaternion(multiply_quaternion(q, p), q_);
	initialize_vector(&rotated_ray_direction, p_.x, p_.y, p_.z);
	ray.direction = rotated_ray_direction;
	ray = transpose_cone_ray(ray, cone->center);

	theta = atan(cone->radius / cone->height);

	
	t = compute_t_for_cone(ray, *cone, theta);
	

	// cone->orientation = save_cone_orientation;
	
	

	// t.t3 = get_intersect_with_cap_cone(ray, *cone, theta);
	smallest_t = ft_min_float(t.t1, t.t2);
	// if (smallest_t > t.t3)
	// {
	// 	cone->normal = cone->orientation;
	// 	cone->is_cap = true;
	// 	return (t.t3);
	// }
	compute_cone_normal(cone, theta);
	
	cone->orientation = save_cone_orientation;
	
	return (smallest_t);
}



/*

		PROBEREN

		https://stackoverflow.com/questions/34157690/points-of-intersection-of-vector-with-cone
		of
		http://www.illusioncatalyst.com/notes_files/mathematics/line_cone_intersection.php
		
		'ray cone intersect'
		



	normal anders berekenen (zeker voor in de punt)




*/





























//////////////////////////	//////////////////////////	//////////////////////////	//////////////////////////	//////////////////////////
//////////////////////////																						//////////////////////////
//////////////////////////									OUDE CODE											//////////////////////////
//////////////////////////																						//////////////////////////
//////////////////////////	//////////////////////////	//////////////////////////	//////////////////////////	//////////////////////////





// goede uitleg!
//https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone



// static t_t4	compute_t_for_cone(t_ray ray, t_object cone, float theta)
// {
// 	t_t4	t;
// 	t_xyz	from_center_of_cone_to_origin;
// 	t_xyz	bottom_center;

// 	bottom_center = add_vectors(cone.center,
// 			multiply_vector(cone.orientation, cone.height / 2));
// 	from_center_of_cone_to_origin = subtract_vectors(ray.origin, bottom_center);
// 	t = NEW_quadratic_formula_infinite_cone(ray.direction, cone.orientation,
// 			theta, from_center_of_cone_to_origin);
// 	t = check_cone_top_bottom(ray, cone, t, bottom_center);

// 	// if (t.t1 != RAY_T_MAX || t.t2 != RAY_T_MAX)
// 	// 	printf("%f\t\t\t%f\n", t.t1, t.t2);

// 	return (t);
// }

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
// static void	compute_cone_normal(t_ray ray, t_object *c, float t, float theta)
// {
// 	float	tip_to_intersect;
// 	float	axis_to_intersect;
// 	t_xyz	axis_intersect;
// 	t_xyz	height_vector;
// 	t_xyz	tip;

// 	height_vector = multiply_vector(c->orientation, c->height * 2);					//// waarom * 2 	?
// 	tip = add_vectors(c->center, get_negative_vector(height_vector));
// 	c->intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
// 	tip_to_intersect = get_vector_length(subtract_vectors(c->intersect, tip));
// 	axis_to_intersect = tip_to_intersect * cos(theta);
// 	axis_intersect = add_vectors(tip,
// 			multiply_vector(c->orientation, axis_to_intersect));
// 	c->normal = subtract_vectors(c->intersect, axis_intersect);
// }

// static void compute_cone_normal(t_object *cone, float theta)
// {
//     t_xyz   b;
//     t_xyz   c;
//     initialize_vector(&b, 0, cone->intersect.y, 0);
//     initialize_vector(&c, 0, b.y/tan(theta), 0);
//     t_xyz cb = subtract_vectors(c, b);
//     t_xyz ba = subtract_vectors(b, cone->intersect);
//     cone->normal = subtract_vectors(cb, ba);
// }






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
