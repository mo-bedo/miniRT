/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_cylinder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/09 20:00:54 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>

#include "intersection/i_plane.h"
#include "intersection/i_utils.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"

//	ray : P(t) = P + V * t
//	cyl : (((P(t) - O) x D)^2 = r^2
//	
//	O is point on cylinder core, D is direction of cylinder (normalised), 
// 	r is radius.
//	
//	then you combine the two equations and you get a second order 
// 	equation you solve for (t), 
// 	composed of cross products and dot products.
//	
//	with end points B and A...
//	
//	(((P(t) - A) x (B - A))^2 = r^2 * ((B - A) . (B - A)) 
//	
//--------------------------------------------------------------------------
// Ray : P(t) = O + V * t
// Cylinder [O, D, r].
// point Q on cylinder if ((Q - O) x D)^2 = r^2
//
// Cylinder [A, B, r].
// Point P on infinite cylinder if ((P - A) x (B - A))^2 = r^2 * (B - A)^2
// expand : ((O - A) x (B - A) + t * (V x (B - A)))^2 = r^2 * (B - A)^2
// equation in the form (X + t * Y)^2 = d
// where : 
//  X = (O - A) x (B - A)
//  Y = V x (B - A)
//  d = r^2 * (B - A)^2
// expand the equation :
// t^2 * (Y . Y) + t * (2 * (X . Y)) + (X . X) - d = 0
// => second order equation in the form : a*t^2 + b*t + c = 0 where
// a = (Y . Y)
// b = 2 * (X . Y)
// c = (X . X) - d
//--------------------------------------------------------------------------
//		
//	******** known variables ********
//	A 		= cylinder center
//	o 		= ray origin
//	ab 		= cylinder orientation
//	v		= ray direction
//	r		= radius
//	******** dot and cross products ********
//  . = dot product		x = cross product
//
//	ao 		= (o - A); 
//	aoxab	= (ao x ab); 
//	vxab 	= (v x ab); 
//	ab2  	= (ab . ab); 
//	
// ******** quadratic equation ******** 
//	a	    = (vxab . vxab); 
//	b    	= 2 * (vxab . aoxab);
//	c    	= (aoxab . aoxab) - (r*r * ab2);
//
static t_t4	create_infinite_cylinder(t_ray ray, t_object cylinder)
{
	t_xyz	vxab;
	t_xyz	aoxab;
	t_xyz	ao;
	float	ab2;
	t_t4	t;

	ao = subtract_vectors(ray.origin, cylinder.center);
	vxab = get_cross_product(ray.direction, cylinder.orientation);
	aoxab = get_cross_product(ao, cylinder.orientation);
	ab2 = get_dot_product(cylinder.orientation, cylinder.orientation);
	t = quadratic_formula(vxab, aoxab, cylinder.radius, ab2);
	return (t);
}

// Checks if the infinite cylinder values are between the caps of the cylinder 
// by comparing them to the heigth (max).  
// - max_len is de maximale lengte die tussen het cylinder.centerpoint 
//   en het intersectie punt mag zitten. (pythagoras)
// - len is de afstand van het center naar de rand van de cirkel
// - if (get_vector_length(len) > max_len) betekent dat punt van intersectie
//   niet tussen de cylinder caps ligt
// - t.t1 is top cap
// - t.t2 is bottom cap
static t_t4	create_finite_cylinder_no_caps(t_ray ray, t_object cylinder, t_t4 t)
{
	float	max_len;
	t_xyz	intersect;
	t_xyz	len;

	max_len = sqrt(pow(cylinder.height / 2, 2) + pow(cylinder.radius, 2));
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t.t1));
	len = subtract_vectors(intersect, cylinder.center);
	if (get_vector_length(len) > max_len)
		t.t1 = RAY_T_MAX;
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t.t2));
	len = subtract_vectors(intersect, cylinder.center);
	if (get_vector_length(len) > max_len)
		t.t2 = RAY_T_MAX;
	return (t);
}

// Cylinder.center is the exact middle of the cylinder 
// (so not the center of either one of the sides)
// t.t3 is bottom cap
// t.t4 is top cap
float	get_intersection_ray_cylinder(t_ray ray, t_object *cylinder)
{
	t_t4	t;
	float	closest_cylinderwall;
	float	closest_cap;

	t = create_infinite_cylinder(ray, *cylinder);
	t = create_finite_cylinder_no_caps(ray, *cylinder, t);
	t.t3 = get_intersect_with_cap_planes(ray, *cylinder, -1);
	t.t4 = get_intersect_with_cap_planes(ray, *cylinder, 1);
	t = check_t_values(t);
	closest_cylinderwall = ft_min_float(t.t1, t.t2);
	closest_cap = ft_min_float(t.t3, t.t4);
	check_if_camera_is_inside_object(cylinder, ray);
	if (closest_cap < closest_cylinderwall)
	{
		cylinder->is_cap = true;
		return (closest_cap);
	}
	return (closest_cylinderwall);
}
