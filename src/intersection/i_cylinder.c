	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/16 15:29:42 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "intersection/i_plane.h"
#include "intersection/i_utils.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

// the hit_pt is on the SIDE of the cylinder. We can use dot product to
// find the point 'pt' on the center line of the cylinder, so that the vector 
// (hit_pt - pt) is orthogonal to the cylinder's orientation.
// t = dot((hit_pt - cy.bottom_center), cy.ori); 
// pt = cy.bottom_center + t * cy.ori;
// surface_normal = normalize(hit_pt - pt)));
static void	get_cylinder_normal(t_ray ray, t_object *cylinder, t_t4 t_)
{
	float	t;
	t_xyz	intersect;
	t_xyz	point_t;

	normalize_vector(&cylinder->orientation);
	t = ft_min_float(t_.t1, t_.t2);
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	t = get_dot_product(subtract_vectors(
				intersect, cylinder->center), cylinder->orientation);
	point_t = add_vectors(cylinder->center,
			multiply_vector(cylinder->orientation, t));
	cylinder->normal = subtract_vectors(intersect, point_t);
	normalize_vector(&cylinder->normal);
}

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
	double	ab2;
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
	double	max_len;
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

//	formules die gelden voor de cap
//	(Q3 - bottomcap)^2 < R^2
//	(Q4 - topcap)^2 < R^2
//	Qi = p + v Ti 
//	dus (lengte van Qi - cap)^2 < R^2 anders is plane_intersectie niet op de cap
//	met flag geef je aan of het de top of de bottom cap is
float	get_intersect_with_cap_planes(t_ray ray, t_object cylinder, float flag)
{
	t_object	cap;
	t_xyz		plane_intersect;
	float		capcenter_to_intersect;
	float		t;

	normalize_vector(&cylinder.orientation);
	cap.orientation = cylinder.orientation;
	cap.center = add_vectors(cylinder.center, multiply_vector(
				cylinder.orientation, (cylinder.height / 2) * flag));
	t = get_intersection_ray_plane(ray, cap);
	plane_intersect = add_vectors(ray.origin,
			multiply_vector(ray.direction, t));
	capcenter_to_intersect = get_vector_length(
			subtract_vectors(plane_intersect, cap.center));
	if ((t < 0) || (capcenter_to_intersect > cylinder.radius))
		t = RAY_T_MAX;
	return (t);
}

// Cylinder.center is the exact middle of the cylinder 
// (so not the center of either one of the sides)
// t.t3 is bottom cap
// t.t4 is top cap
float	get_intersection_ray_cylinder(t_ray ray, t_object *cylinder)
{
	t_t4	t;

	t = create_infinite_cylinder(ray, *cylinder);
	t = create_finite_cylinder_no_caps(ray, *cylinder, t);
	t.t3 = get_intersect_with_cap_planes(ray, *cylinder, -1);
	t.t4 = get_intersect_with_cap_planes(ray, *cylinder, 1);
	t = check_t_values(t);
	if (ft_min_float(t.t1, t.t2) > ft_min_float(t.t3, t.t4))
		cylinder->normal = cylinder->orientation;
	else
		get_cylinder_normal(ray, cylinder, t);
	return (ft_min_float(ft_min_float(t.t1, t.t2), ft_min_float(t.t3, t.t4)));
}
