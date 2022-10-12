/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/12 13:56:47 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "intersection/i_plane.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"
#include "utils/matrices.h"
#include "utils/u_invert_matrix.h"


void	get_cylinder_normal(t_object *object)
{
	t_xyz	normal;
	
	object->normal = object->vector_orientation;
 
}

// Creating an infinite cylinder with the quadratic equation
static t_t4	create_infinite_cylinder(t_ray ray, t_object *cylinder)
{
	float	a;
	float	b;
	float	c;
	float	det;
	t_t4	t;
	t_xyz	temp_cross;
	t_xyz	temp_cross2;

	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;
	temp_cross = cross(ray.direction, cylinder->vector_orientation);
	temp_cross2 = cross(substract_vectors(ray.origin, cylinder->center), cylinder->vector_orientation);
	a = get_dot_product(temp_cross, temp_cross);
	b = 2 * get_dot_product(temp_cross, temp_cross2);
	c = get_dot_product(temp_cross2, temp_cross2) - (pow(cylinder->radius, 2) 
		* get_dot_product(cylinder->vector_orientation, cylinder->vector_orientation));
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
		return (t);
	a = 2 * a;
	det = sqrt(det);
	t.t1 = (-b - det) / a;	
	t.t2 = (-b + det) / a;	
	return (t);	
	
	// float t = RAY_T_MAX;
	// if (t_[0] >= 0 && t > t_[0])
	// 	t = t_[0];
	// if (t_[1] >= 0 && t > t_[1])
	// 	t = t_[1];
	// if (t == RAY_T_MAX)
	// 	return (t);	
}

// Checks if the infinite cylinder values are between the caps of the cylinder by comparing them
// to the heigth (max).  
static t_t4	create_finite_cylinder_no_caps(t_ray ray, t_object *cylinder, t_t4 t)
{
	double	max_len;
	t_xyz	intersect;
	t_xyz	len;
	
	if (t.t2 < 0) 			// is dit nodig?
	{
		// t.t1 = RAY_T_MAX; 
		t.t2 = RAY_T_MAX;
		return t;
	}
	
			// t = (temp_t[0] > 0 ? temp_t[0] : temp_t[1]);

	// max is dus de maximale lengte die tussen het centerpoint en het intersectie punt mag zitten.
	// Dit is dus de afstand van het center naar de rand van de cirkel (en bereken we door pythagoras)
	max_len = sqrt(pow(cylinder->height / 2, 2) + pow(cylinder->radius, 2));
	// double max = sqrt(pow(cylinder->height / 2, 2) + pow(cylinder->radius, 2)); // met pythagoras bereken je afstand cylinder center tot rand van cap

	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t.t1));
	// t_xyz point = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	
	// lengte tussen cylinder center en punt van intersect
	len = substract_vectors(intersect, cylinder->center);
	// t_xyz len = substract_vectors(point, cylinder->center);
	
	// Als deze if waar is dan is het intersectie punt dus niet tussen de cylinder caps
	if (get_vector_length(len) > max_len) 
		t.t1 = RAY_T_MAX;	
	
	// dan nog een keer hetzelfde voor t2 proberen 
	
	//////////////////////////////		//////////////////////////////
	////////////////////////////// TEST	//////////////////////////////
	
	//  evt hier sneller maken door eerder te returnen met valid t1 waarde?

	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t.t2));
	len = substract_vectors(intersect, cylinder->center);
	if (get_vector_length(len) > max_len) 
		t.t2 = RAY_T_MAX;	
	return (t);
}

// Cylinder.center is het midden van cylinder (en dus niet het midden van 1 van de uiteindes) 
// Deze functie berekend het quadratic deel. 
float	get_intersection_ray_cylinder(t_ray ray, t_object *cylinder)
{
	t_t4	t;

	t = create_infinite_cylinder(ray, cylinder);
	if ((t.t1 < 0 || t.t1 >= RAY_T_MAX) && (t.t2 < 0 || t.t2 >= RAY_T_MAX))
		return (RAY_T_MAX);					// misschien later check voor invalid values (samen met t3 en t4))
	t = create_finite_cylinder_no_caps(ray, cylinder, t);
	
	


		// HIER t returnen is infinite cylinder
	return (ft_min_float(t.t1, t.t2));

	// 


	/*
	If the distance between the intersection and the center of the cylinder is higher 
	than the length of the cylinder, then we do not consider an intersection. Even though
	 there is no intersection at the closest intersection (which is too high), there is one 
	 behind it which might be in the range of the height of the cylinder. And this is the 
	 intersection that we need to get the other side of our cylinder.

			** PSUEDO **
	// I assume you already found t1 and t2, the two intersections
	if (t2 < 0) return ;
	t = (t1 > 0 ? t1 : t2);

	double max = sqrt(pow(cylinder.height / 2, 2) + pow(cylinder.radius, 2)); //pythagoras theorem
	t_vect point = ray.origin + ray.direction * t;
	t_vect len = point - cylinder.center;
	if (norm(len) > max) // if t1 is too high we try with t2
	t = t2;

	t_vect point = ray.origin + ray.direction * t;
	len = point - cylinder.center;
	if (norm(len) > max) // if t2 is too high too then there is no intersection, else t2 is the intersection. And t2 is in the second half of the cylinder
	return;

	*/

	float	t1 = RAY_T_MAX;
	float	t2 = RAY_T_MAX;
	// float	t;

	
	// return (ft_min_float(t1, t2));			// hier returnen voor cylinders zonder cap


	// maak 2 planes voor de caps en bereken de t waardes, kijk dan of 
	// die binnen de radius van de cylinder zijn vanaf de top en bottom
	float	t3 = RAY_T_MAX;
	float	t4 = RAY_T_MAX;

	t_object	top_cap;
	t_object	bottom_cap;	

	top_cap.vector_orientation = cylinder->vector_orientation;
	bottom_cap.vector_orientation = cylinder->vector_orientation;

	top_cap.center = add_vectors(cylinder->center, multiply_vector(cylinder->vector_orientation, cylinder->height / 2));
	bottom_cap.center = add_vectors(cylinder->center, multiply_vector(cylinder->vector_orientation, -(cylinder->height / 2)));
	// bottom_cap.center = cylinder.center;

	t3 = get_intersection_ray_plane(ray, bottom_cap);
	t4 = get_intersection_ray_plane(ray, top_cap);
	

	//	(Q3 - P1)^2 < R^2
	//	(Q4 - P2)^2 < R^2
	//	Qi = p + v Ti 
	//	P1 = bottomcap center
	// dus (lengte van Q3 - P1)^2 < R^2 anders is plane_intersectie niet op de cap
	// zie hieronder 

	// voor t4 moet dit nog goed worden geschreven

	t_xyz 	bottom_plane_intersect;
	t_xyz	top_plane_intersect;
	float	x;
	float	y;
	float	z;
	float	r; 


	bottom_plane_intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t3));
	

	t_xyz math;
	float	math_len;




	math = substract_vectors(bottom_plane_intersect, bottom_cap.center);
	math_len = get_vector_length(math);
	math_len = pow(math_len, 2); 

	r = pow(cylinder->radius, 2);


	if ((t3 < 0) || (math_len > r))
		t3 = RAY_T_MAX;

	top_plane_intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t4));

	
	math = substract_vectors(top_plane_intersect, top_cap.center);
	math_len = get_vector_length(math);
	
	math_len = pow(math_len, 2); 
	
	// if ((t4 > 0) && (math_len < r))
	if ((t4 < 0) || (math_len > r))
		t4 = RAY_T_MAX;
	
	// if ((t3 > 0) && (x < r) && (y < r) && (z < r))
	// 	t3 = t3;
	// else
	// 	t3 = RAY_T_MAX;

	// top_plane_intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t4));
	// x = pow(top_plane_intersect.x - top_cap.center.x, 2);
	// y = pow(top_plane_intersect.y - top_cap.center.y, 2);
	// z = pow(top_plane_intersect.z - top_cap.center.z, 2);
	// if ((t4 > 0) && (x < r) && (y < r) && (z < r))
	// 	t4 = t4;
	// else

	float	small;
	float	small1;

	small = ft_min_float(t1, t2);
	small1 = ft_min_float(t3, t4);
	
	if (small1 < small)		// in dit geval heeft 1 van de caps de kleinste t waarde
	{	
		cylinder->normal = cylinder->vector_orientation;
		if (t3 < t4)
			cylinder->color.y = 255;			
		else
			cylinder->color.z = 255;

	}
	return (ft_min_float(small, small1));
}
