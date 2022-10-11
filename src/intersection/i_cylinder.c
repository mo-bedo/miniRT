/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/10 16:01:16 by jbedaux          ###   ########.fr       */
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


static float	cylinder_cap(float *t, t_xyz intersect, t_xyz cyl_orientation, t_plane plane)
{
	float	a;
	float	b;
	float	temp_t;

	a = get_dot_product(substract_vectors(intersect, plane.center), plane.vector_orientation);
	b = get_dot_product(cyl_orientation, plane.vector_orientation);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return ;
	temp_t = -a / b;
	if (temp_t < 0 || *t < temp_t)
		return ;
	*t = temp_t;
}

// t_inter_point ft_find_edges(t_pack cylinder, t_ray ray,
//                             t_inter_point inter_point)
// {
//     double a;

//     ft_get_normal(ray, cylinder.pos, &inter_point);
//     if (get_norm(sub(inter_point.coord, cylinder.pos)) > cylinder.height)
//         return (inter_point);
//     a = dot(cylinder.rot, sub(inter_point.coord, cylinder.pos));
//     inter_point.normal = normalize(sub(inter_point.coord, add(cylinder.pos, ft_scale(cylinder.rot, a))));
//     inter_point.hit = TRUE;
//     return (inter_point);
// }



float	get_intersection_ray_cylinder(t_closest_object *o, t_ray ray, t_cylinder cylinder)
{
	float	a;
	float	b;
	float	c;
	float	det;
	float	t_[2];

	t_xyz	temp_cross = cross(ray.direction, cylinder.vector_orientation);
	t_xyz	s_sub = substract_vectors(ray.origin, cylinder.center);
	t_xyz	temp_cross2 = cross(s_sub, cylinder.vector_orientation);

	a = get_dot_product(temp_cross, temp_cross);
	b = 2 * get_dot_product(temp_cross, temp_cross2);
	c = get_dot_product(temp_cross2, temp_cross2) - (pow(cylinder.radius, 2) 
		* get_dot_product(cylinder.vector_orientation, cylinder.vector_orientation));
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
		return (RAY_T_MAX);
	a = 2 * a;
	det = sqrt(det);
	t_[0] = (-b - det) / a;	
	t_[1] = (-b + det) / a;	


	float t = RAY_T_MAX;

	if (t_[0] >= 0 && t > t_[0])
		t = t_[0];
	if (t_[1] >= 0 && t > t_[1])
		t = t_[1];
	if (t == RAY_T_MAX)
		return (t);	

	// HIER t returnen is infinite cylinder

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

	if (t_[1] < 0)
		return RAY_T_MAX;
	t = (t_[0] > 0 ? t_[0] : t_[1]);

	double max = sqrt(pow(cylinder.height / 2, 2) + pow(cylinder.radius, 2)); //pythagoras
	t_xyz point = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	t_xyz len = substract_vectors(point, cylinder.center);
	if (get_vector_length(len) < max) // als t_0 te hoog is probeer je t_1
		t1 = t;
	t = t_[1];
	point = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	len = substract_vectors(point, cylinder.center);
	if (get_vector_length(len) < max) // t_1 te hoog is is er geen intersectie
		t2 = t;
	// return (ft_min_float(t1, t2));			// hier returnen voor cylinders zonder cap


	// maak 2 planes voor de caps en bereken de t waardes, kijk dan of 
	// die binnen de radius van de cylinder zijn vanaf de top en bottom
	float	t3 = RAY_T_MAX;
	float	t4 = RAY_T_MAX;

	t_plane top_cap;
	t_plane	bottom_cap;	

	top_cap.vector_orientation = cylinder.vector_orientation;
	bottom_cap.vector_orientation = cylinder.vector_orientation;

	top_cap.center = add_vectors(cylinder.center, multiply_vector(cylinder.vector_orientation, cylinder.height));
	bottom_cap.center = cylinder.center;

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

	math = substract_vectors(bottom_plane_intersect, cylinder.center);
	math_len = get_vector_length(math);
	math_len *= math_len; 

	r = pow(cylinder.radius, 2);


	if ((t3 > 0) && (math_len < r))
		t3 = t3;
	else
		t3 = RAY_T_MAX;

	
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
		t4 = RAY_T_MAX;

	float	small;
	float	small1;

	// if (t1 < RAY_T_MAX && t3 < RAY)
	// printf("t1 = %f \t t2 = %f \t t3 = %f \t t4 = %f\n", t1, t2, t3, t4);

	small = ft_min_float(t1, t2);
	small1 = ft_min_float(t3, t4);

	return (ft_min_float(small, small1));
}
