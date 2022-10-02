/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:09:28 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/02 16:39:47 by jbedaux          ###   ########.fr       */
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




// P = punt op ray waar hij cylinder raakt
// O = ray origin
// D = ray direction
// V = cylinder orient
// C = cap punt van cylinder (middelpunt van de 'cap' van de cylinder, in ons systeem )
// A = punt op de as van de cylinder ter hoogte van het punt P
// X = O - C			
// (MOET MISSCHIEN O - A zijn, maar dan weet ik niet hoe je aan A komt)

//		DINGEN DIE WE WETEN
// A = C + V * m		m is dus de afstand van het cap punt naar het aspunt ter hoogte van het ray-raakpunt
// (P - A) . V = 0		vector P.A staat loodrecht op vector V	
// 	de lengte van vector PA == r



// a   = D . D - (D . V)ˆ2
// b/2 = D . X - (D . V) * (X . V)
// c   = X . X - (X . V)^2 - r * r
// float	get_intersection_ray_cylinder(t_ray ray, t_cylinder obj)
// {

// 	float discriminant;
	
// 	obj.cap_center = obj.center;			
// 	t_xyz x = subtract_vectors(ray.origin, obj.cap_center);
		
// 	double a = get_dot_product(ray.direction, ray.direction) - pow(get_dot_product(ray.direction, obj.vector_orientation), 2);
// 	double b = get_dot_product(ray.direction, x) -      					// D . X - 
// 				 get_dot_product(ray.direction, obj.vector_orientation) *	// (D . V) *
// 	 			get_dot_product(x, obj.vector_orientation);					// (X . V)
// 	b *= 2;
// 	double c = get_dot_product(x, x) - pow(get_dot_product(x, obj.vector_orientation), 2) - obj.radius * obj.radius;
	
	



// 	discriminant = (b * b) - 4 * (c * a);

// 	if (fabs(discriminant) < RAY_T_MIN || discriminant < 0)
// 		return (-1);

// 	float t1 = (-b - sqrt(discriminant) / (2 * a));
// 	float t2 = (-b + sqrt(discriminant) / (2 * a));
// 	float t;

// 	if (t1 > t2)
// 		t = t2;
// 	else
// 		t = t1;

	

// 	if (t  > RAY_T_MIN && t <= RAY_T_MAX)
// 		return (t);
// 	return (-1);
// }


// static t_ray	transpose_ray(t_ray ray, t_xyz centre)
// {
// 	ray.origin = subtract_vectors(ray.origin, centre);
// 	return (ray);
// }

double	get_dot_y(t_xyz v1, t_xyz v2)
{
	return (v1.x * v2.x + v1.z * v2.z);
}

float	get_intersection_ray_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_distance	distance;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	// ray = transpose_ray(ray, cylinder.center);
	a = get_dot_y(ray.direction, ray.direction);
	b = 2 * get_dot_y(ray.origin, ray.direction);
	c = get_dot_y(ray.origin, ray.origin) - cylinder.radius * cylinder.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0 || a == 0)
		return (RAY_T_MAX);
	distance.t1 = (-b + sqrt(discriminant)) / (2 * a);
	distance.t2 = (-b - sqrt(discriminant)) / (2 * a);
	return (ft_min_float(distance.t1, distance.t2));
}



// ntersections with the curved surface are like the intersection with a cylinder, 
// but the Z-axis can be ignored. You might think of this as intersecting a 2D ray 
// in the X- Y plane with a unit circle. This leads to a quadratic equation, like that 
// for the cylinder and 0, 1, or 2 hit points. These hit points would be with an 'infinite'
//  cylinder extending along the Z-axis, so you should reject those with Z value greater 
// than 1 or less than −1.

//     BESTE TOT NU TOE
// float	get_intersection_ray_cylinder(t_ray ray, t_cylinder cylinder)
// {
// 	float		a;
// 	float		b;
// 	float		c;
// 	float		det;
	
	
	
// 	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
// 	b = 2 * (ray.origin.x * ray.direction.x + ray.origin.y * ray.direction.y
// 		- ray.direction.x * cylinder.center.x - ray.direction.y * cylinder.center.y);
// 	c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y + cylinder.center.x * cylinder.center.x
// 		+ cylinder.center.y * cylinder.center.y - cylinder.radius * cylinder.radius - 2 * (ray.origin.x * cylinder.center.x
// 			+ ray.origin.y * cylinder.center.y);
// 	det = b * b - 4 * a * c;
// 	if (det >= 0)
// 	{
// 		det = sqrt(det);
// 		float t1, t2;
// 		t1 = (-b + det) / (2 * a);
// 		t2 = (-b - det) / (2 * a);
// 		if (t1 < t2)
// 			return t1;
// 		else
// 		return t2;
// 	}
// 	return (-1);
// }




// float	get_intersection_ray_cylinder(t_ray ray, t_cylinder cylinder)
// {
// 	float discriminant;
// 	t_ray local;
// 	local = ray;
// 	local.direction = normalize_vector(ray.direction);
// 	//// TEST ALS CAMERA NIET OP 0,0,0 staat
// 	//// zou goed kunnen dat de cylinder op moet worden geschoven zodat hij loodrecht op de y-as staat
// //	local.origin.x = 0;
// //	local.origin.y = 0;
// //	local.origin.z = 0;

// 	float a = (local.direction.x * local.direction.x) + (local.direction.z * local.direction.z);
// 	float b = 2 * (local.direction.x * (local.origin.x - cylinder.center.x) +
// 				   local.direction.z * (local.origin.z - cylinder.center.z));
// 	float c = (local.origin.x - cylinder.center.x) * (local.origin.x - cylinder.center.x) + \
//             (local.origin.z - cylinder.center.z) * (local.origin.z - cylinder.center.z) -
// 			  (cylinder.radius * cylinder.radius);


// 	discriminant = (b * b) - 4 * (c * a);

// 	if (fabs(discriminant) < RAY_T_MIN || discriminant < 0)
// 		return (-1);

// 	float t1 = (-b - sqrt(discriminant) / (2 * a));
// 	float t2 = (-b + sqrt(discriminant) / (2 * a));
// 	float t;

// 	if (t1 > t2)
// 		t = t2;
// 	else
// 		t = t1;

// 	float r = local.origin.y + t * local.direction.y;

// 	if (r >= cylinder.center.y && r <= cylinder.center.y + cylinder.height)
// 		return (t);
// 	return (-1);
// }

// 	float Cylinder::intersect(Vector cam, Vector ray)
// 	{

// 		float a = (ray.x * ray.x) + (ray.z * ray.z);
// 		float b = 2*(ray.x*(cam.x-center.x) + ray.z*(cam.z-center.z));
// 		float c = (cam.x - center.x) * (cam.x - center.x) + \
// 			(cam.z - center.z) * (cam.z - center.z) - (radius*radius);

// 		float delta = b*b - 4*(a*c);
// 		if(fabs(delta) < 0.001) return -1.0;
// 		if(delta < 0.0) return -1.0;

// 		float t1 = (-b - sqrt(delta))/(2*a);
// 		float t2 = (-b + sqrt(delta))/(2*a);
// 		float t;

// 		if (t1>t2) t = t2;
// 		else t = t1;

// 		float r = cam.y + t*ray.y;

// 		if ((r >= center.y) and (r <= center.y + height))return t;
// 		else return -1;
// 	}
// }

// float	get_intersection_ray_cylinder(t_ray ray, t_cylinder cylinder)
// {
// 	t_distance	distance;
// 	t_xyz		cylinder_to_origin;
// 	t_ray		local_ray;

// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;

// 	local_ray.origin = ray.origin;
// 	cylinder.vector_orientation = normalize_vector(cylinder.vector_orientation);

// // cross product
// // is a measure of difference
// //  0 = same direction
// //  1 = at angle of 90 degrees
// // -1 = opposite direction
// 	local_ray.direction = get_cross_product(ray.direction, cylinder.vector_orientation);

// 	cylinder_to_origin = subtract_vectors(ray.origin, cylinder.center);
// 	// quadratic

// 	a = get_dot_product(ray.origin, cylinder.center);
// 	b = 2 * get_dot_product(local_ray.direction, get_cross_product(cylinder_to_origin, cylinder.center));
// 	c = get_dot_product(get_cross_product(cylinder_to_origin, cylinder.center), get_cross_product(cylinder_to_origin, \
// 	cylinder.center)) - pow(cylinder.radius, 2);
// 	discriminant = pow(b, 2) - 4 * c * a;
// 	if (discriminant < 0)
// 		return (0); // return no hit
// 	distance.t1 = (-b + sqrt(discriminant)) / (2 * a);
// 	distance.t2 = (-b - sqrt(discriminant)) / (2 * a);
// 	if (distance.t2 < 0)
// 		return (0); // return no hit
// //	distance.t1 = find_edges(cylinder, ray, ft_min_float(distance.t1, distance.t2));
// 	return (distance.t1);
// }

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