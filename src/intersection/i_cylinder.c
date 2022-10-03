/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:09:28 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/03 13:46:35 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "main.h"
#include "ray_trace.h"
#include "utils/utils.h"
#include "utils/vector_math.h"

/*
		Psuedo code cylinder

		Ray_inter_finite_cylinder(P,d):
		// Check for intersection with infinite cylinder
		t1,t2 = ray_inter_infinite_cylinder(P,d)
		compute P + t1*d, P + t2*d
		// If intersection, is it between “end caps”?
		if y > 1 or y < -1 for t1 or t2, toss it
		// Check for intersection with top end cap
		Compute ray_inter_plane(t3, plane y = 1)
		Compute P + t3*d
		// If it intersects, is it within cap circle?
		if x2 + z2 > 1, toss out t3
		// Check intersection with other end cap
		Compute ray_inter_plane(t4, plane y = -1)
		Compute P + t4*d
		// If it intersects, is it within cap circle?
		if x2 + z2 > 1, toss out t4
		Among all the t’s that remain (1-4), select the smallest non-negative
		one
 */

//
//float	find_edges(t_cylinder cylinder, t_ray ray, float t)
//{
//
//	t_inter_point ft_find_edges(t_pack cylinder, t_ray ray,
//								t_inter_point inter_point)
//	{
//		double a;
//
//		ft_get_normal(ray, cylinder.pos, &inter_point);
//		if (get_norm(sub(inter_point.coord, cylinder.pos)) > cylinder.height)
//			return (inter_point);
//		a = dot(cylinder.rot, sub(inter_point.coord, cylinder.pos));
//		inter_point.normal = normalize(sub(inter_point.coord, add(cylinder.pos, ft_scale(cylinder.rot, a))));
//		inter_point.hit = TRUE;
//		return (inter_point);
//	}
//}


//	Cylinder eigenscahppen
//∗ identifier: cy
//∗ x,y,z coordinates: 50.0,0.0,20.6
//∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
//∗ the cylinder diameter: 14.2
//∗ the cylinder height: 21.42
//∗ R,G,B colors in range [0,255]: 10, 0, 255



    // the hit_pt is on the TOP CAP of the cylinder:

    // if (length(hit_pt - cy.top_center) < cy.radius)
    //        surface_normal = cy.ori;

    // the hit_pt is on the BOTTOM CAP of the cylinder:

    // if (length(hit_pt - cy.bottom_center) < cy.radius)
    //         surface_normal = -1 * cy.ori;

    // the hit_pt is on the SIDE of the cylinder. We can use dot product to find the point 'pt' on the center line of the cylinder, so that the vector (hit_pt - pt) is orthogonal to the cylinder's orientation.

    // t = dot((hit_pt - cy.bottom_center), cy.ori); // cy.ori should be normalized and so has the length of 1.
    // pt = cy.bottom_center + t * cy.ori;
    // surface_normal = normalize(hit_pt - pt)));

// t_xyz	get_cylinder_normal(t_ray ray, t_closest_object cylinder)
// {
// 	t_xyz	hit_point;
// 	t_xyz	top_cap_center;

// 	hit_point = multiply_vector(ray.direction, cylinder.t);
// 	top_cap_center = add_vectors(cylinder.center, cylinder.vector_orientation)
// }



// {void			get_cylinder_normal(t_vector *normal,
					// t_object *cylinder, t_point *intersection)
// 	t_vector	v;
// 	t_vector	project;
// 	float		dot;
// 	t_vector	n;

// 	n = cylinder->normal;
// 	if (vect_norm(&n) - 1 > 0.05)
// 		normalize_vector(&cylinder->normal);
// 	v.x = intersection->x - cylinder->origin.x;
// 	v.y = intersection->y - cylinder->origin.y;
// 	v.z = intersection->z - cylinder->origin.z;
// 	dot = vect_dot(&v, &cylinder->normal);
// 	project.x = dot * cylinder->normal.x;
// 	project.y = dot * cylinder->normal.y;
// 	project.z = dot * cylinder->normal.z;
// 	normal->x = v.x - project.x;
// 	normal->y = v.y - project.y;
// 	normal->z = v.z - project.z;
// 	normalize_vector(normal);
// }

// //	Calculeert dan het punt op de ray als je waarde t weet
// //	van r = p + td
t_xyz	get_coordinates_of_ray_at_distance(t_ray ray, double distance)
{
	t_xyz	math;

	math = multiply_vector(ray.direction, distance);
	return (add_vectors(ray.origin, math));
}

t_xyz	get_cylinder_normal(t_ray ray, t_closest_object cylinder)
{
	t_xyz	v;
	t_xyz	inter_point;
	t_xyz	project;
	t_xyz	n;
	float	dot;
	
	// n = cylinder.vector_orientation;
	// n = normalize_vector(n); // ?
	inter_point = get_coordinates_of_ray_at_distance(ray, cylinder.t);
	v.x = inter_point.x = cylinder.center.x;
	v.y = inter_point.y = cylinder.center.y;
	v.z = inter_point.z = cylinder.center.z;
	dot = get_dot_product(v, cylinder.vector_orientation);
	project.x = dot * cylinder.vector_orientation.x;
	project.y = dot * cylinder.vector_orientation.y;
	project.z = dot * cylinder.vector_orientation.z;
	n.x = v.x - project.x;
	n.y = v.y - project.y;
	n.z = v.z - project.z;
	n = normalize_vector(n);
	return (n);
}


float	get_intersection_ray_cylinder(t_ray ray, t_cylinder cylinder)
{
	float discriminant;
	t_ray local;
	local = ray;
	local.direction = normalize_vector(ray.direction);
	//// TEST ALS CAMERA NIET OP 0,0,0 staat
	//// zou goed kunnen dat de cylinder op moet worden geschoven zodat hij loodrecht op de y-as staat
//	local.origin.x = 0;
//	local.origin.y = 0;
//	local.origin.z = 0;

	float a = (local.direction.x * local.direction.x) + (local.direction.z * local.direction.z);
	float b = 2 * (local.direction.x * (local.origin.x - cylinder.center.x) +
				   local.direction.z * (local.origin.z - cylinder.center.z));
	float c = (local.origin.x - cylinder.center.x) * (local.origin.x - cylinder.center.x) + \
            (local.origin.z - cylinder.center.z) * (local.origin.z - cylinder.center.z) -
			  (cylinder.radius * cylinder.radius);


	discriminant = (b * b) - 4 * (c * a);

	if (fabs(discriminant) < RAY_T_MIN || discriminant < 0)
		return (-1);

	float t1 = (-b - sqrt(discriminant) / (2 * a));
	float t2 = (-b + sqrt(discriminant) / (2 * a));
	float t;

	if (t1 > t2)
		t = t2;
	else
		t = t1;

	// 			Dit laten return voor een oneindige cylinder
	// if (t < RAY_T_MIN || t > RAY_T_MAX)
	// 	return (-1);
	// else
	// 	return (t);	
	
	//			Dit checked the 'caps'	
	float r = local.origin.y + t * local.direction.y;
	if (r >= cylinder.center.y && r <= cylinder.center.y + cylinder.height)
		return (t);
	return (-1);
}

//	float Cylinder::intersect(Vector cam, Vector ray)
//	{

//		float a = (ray.x * ray.x) + (ray.z * ray.z);
//		float b = 2*(ray.x*(cam.x-center.x) + ray.z*(cam.z-center.z));
//		float c = (cam.x - center.x) * (cam.x - center.x) + \
//			(cam.z - center.z) * (cam.z - center.z) - (radius*radius);
//
//		float delta = b*b - 4*(a*c);
//		if(fabs(delta) < 0.001) return -1.0;
//		if(delta < 0.0) return -1.0;
//
//		float t1 = (-b - sqrt(delta))/(2*a);
//		float t2 = (-b + sqrt(delta))/(2*a);
//		float t;
//
//		if (t1>t2) t = t2;
//		else t = t1;
//
//		float r = cam.y + t*ray.y;
//
//		if ((r >= center.y) and (r <= center.y + height))return t;
//		else return -1;
//	}
//}

//float	get_intersection_ray_cylinder(t_ray ray, t_cylinder cylinder)
//{
//	t_distance	distance;
//	t_xyz		cylinder_to_origin;
//	t_ray		local_ray;
//
//	double		a;
//	double		b;
//	double		c;
//	double		discriminant;
//
//	local_ray.origin = ray.origin;
//	cylinder.vector_orientation = normalize_vector(cylinder.vector_orientation);
//
//// cross product
//// is a measure of difference
////  0 = same direction
////  1 = at angle of 90 degrees
//// -1 = opposite direction
//	local_ray.direction = get_cross_product(ray.direction, cylinder.vector_orientation);
//
//	cylinder_to_origin = substract_vectors(ray.origin, cylinder.center);
//	// quadratic
//
//	a = get_dot_product(ray.origin, cylinder.center);
//	b = 2 * get_dot_product(local_ray.direction, get_cross_product(cylinder_to_origin, cylinder.center));
//	c = get_dot_product(get_cross_product(cylinder_to_origin, cylinder.center), get_cross_product(cylinder_to_origin, \
//	cylinder.center)) - pow(cylinder.diameter / 2, 2);
//	discriminant = pow(b, 2) - 4 * c * a;
//	if (discriminant < 0)
//		return (0); // return no hit
//	distance.t1 = (-b + sqrt(discriminant)) / (2 * a);
//	distance.t2 = (-b - sqrt(discriminant)) / (2 * a);
//	if (distance.t2 < 0)
//		return (0); // return no hit
////	distance.t1 = find_edges(cylinder, ray, ft_min_float(distance.t1, distance.t2));
//	return (distance.t1);
//}

//t_inter_point ft_cylinder_collision(t_ray ray, t_pack cylinder, int id)
//{
//	t_inter_point inter_point;
//	t_delta delta;
//	t_ray new_ray;
//	t_vect c_to_o;
//
////	inter_point.id = id;
//	new_ray.origin = ray.origin;
//	cylinder.rot = normalize(cylinder.rot);
//	new_ray.direction = cross(ray.direction, cylinder.rot);
//	c_to_o = sub(ray.origin, cylinder.pos);
//	delta.a = dot(new_ray.direction, new_ray.direction);
//	delta.b = 2 * dot(new_ray.direction, cross(c_to_o, cylinder.rot));
//delta.c = dot(cross(c_to_o, cylinder.rot), cross(c_to_o, cylinder.rot)) - pow(cylinder.diameter / 2, 2);
//	delta.delta = pow(delta.b, 2) - 4 * delta.c * delta.a;
//	if (delta.delta < 0)
////		return (inter_point);
//	inter_point.t1 = (-delta.b - sqrt(delta.delta)) / (2 * delta.a);
//	inter_point.t2 = (-delta.b + sqrt(delta.delta)) / (2 * delta.a);
//	if (inter_point.t2 < 0)
//		return (inter_point);
//	inter_point.t = (inter_point.t1 > 0 ? inter_point.t1 : inter_point.t2);
//	return (ft_find_edges(cylinder, ray, inter_point));
//}