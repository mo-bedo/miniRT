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
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"
#include "utils/matrices.h"
#include "utils/u_invert_matrix.h"




// moet convert zodat cylinder orientation over de z as gaat. 
float	get_intersection_ray_cylinder(t_closest_object *o, t_ray ray, t_cylinder cylinder)
{
	float		a;
	float		b;
	float		c;
	float		det;

	// make z_axis transform matrix so cylinder is evenwijdig aan de z-axis	
	double		angle_z;
	t_xyz		z_axis_vector;
	t_matrix4	z_axis_matrix;
	t_matrix4	revert_axis;
	z_axis_matrix = set_matrix_to_identity(z_axis_matrix);
	z_axis_vector.x = 0;
	z_axis_vector.y = 0;
	z_axis_vector.z = 1;

	angle_z = get_angle_between_vectors(z_axis_vector, cylinder.vector_orientation);
	z_axis_matrix = set_rotation_matrix_z_axis(z_axis_matrix, angle_z);
	revert_axis = invert_matrix(z_axis_matrix);
	ray.direction = apply_matrix4_to_vector(z_axis_matrix, ray.direction);
	cylinder.vector_orientation = apply_matrix4_to_vector(z_axis_matrix, cylinder.vector_orientation);
	
	




	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
	b = 2 * (ray.origin.x * ray.direction.x + ray.origin.y * ray.direction.y
		- ray.direction.x * cylinder.center.x - ray.direction.y * cylinder.center.y);
	c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y + cylinder.center.x * cylinder.center.x
		+ cylinder.center.y * cylinder.center.y - cylinder.radius * cylinder.radius - 2 * (ray.origin.x * cylinder.center.x
			+ ray.origin.y * cylinder.center.y);
	det = b * b - 4 * a * c;

	if (det >= 0)
	{
		det = sqrt(det);
		float t1, t2;
		t1 = (-b + det) / (2 * a);
		t2 = (-b - det) / (2 * a);
		if (t1 < t2)
			return t1;
		else
			return t2;
	}
	return (RAY_T_MAX);
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

// t_inter_point ft_cylinder_collision(t_ray ray, t_pack cylinder, int id)

// float	get_intersection_ray_cylinder(t_closest_object *closest_object, t_ray ray, t_cylinder cylinder)
// {
//     t_ray new_ray;
// 	t_xyz cylinder_rot;
	
	
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	discriminant;
// 	t_xyz	c_to_o;

//     // t_inter_point inter_point;
//     // t_delta delta;
//     // t_vect c_to_o;

//     // inter_point.hit = FALSE;
//     // inter_point.id = id;
   
//     new_ray.origin = ray.origin;
	
	
   
//     cylinder_rot = normalize_vector(cylinder.vector_orientation);
//     new_ray.direction = cross(ray.direction, cylinder_rot);
//     c_to_o = substract_vectors(ray.origin, cylinder.center);
//     a = get_dot_product(new_ray.direction, new_ray.direction);
//     b = 2 * get_dot_product(new_ray.direction, cross(c_to_o, cylinder_rot));
//     c = get_dot_product(cross(c_to_o, cylinder_rot), cross(c_to_o, cylinder_rot)) - pow(cylinder.radius, 2);
//     discriminant = pow(b, 2) - 4 * c * a;
//     if (discriminant < 0)
//         return (RAY_T_MAX);
// 	float	t1;
// 	float	t2;
// 	float	t;
// 	t1 = (-b - sqrt(discriminant)) / (2 * a);
//     t2 = (-b + sqrt(discriminant)) / (2 * a);
//     if (t2 > 0 || t1 > 0)
//     	t = ft_min_float(t1, t2);
// 	else
//         return (RAY_T_MAX);
	
// 	// find_caps(cylinder, ray);
	
//     return (t);
// }


// float	get_intersection_ray_cylinder(t_closest_object *closest_object, t_ray ray, t_cylinder cylinder)
// {
// 	t_matrix4	to_world;
// 	t_matrix4	to_local;
// 	t_ray		bck_ray;
// 	t_cylinder	local_cyl;

// 	t_xyz	translate;
// 	t_xyz	rotate;
// 	t_xyz	scale;


// 	translate.x = 1 ;
// 	translate.y = 1;
// 	translate.z = 1;

// 	rotate.x = 0;
// 	rotate.y = 0;
// 	rotate.z = 0;

// 	scale.x = 1;
// 	scale.y = 1;
// 	scale.z = 1;

// 	// to_world = create_transform_matrix(translate, rotate, scale);
// 	// to_local = invert_matrix(to_world);

// 	to_local = create_transform_matrix(translate, rotate, scale);
// 	to_world = invert_matrix(to_local);



// 	//transform ray to local by applying matrix to_local to ray
// 	bck_ray.direction = apply_matrix4_to_vector(to_local, ray.direction);
// 	bck_ray.origin = apply_matrix4_to_vector(to_local, ray.origin);
	
// 	t_xyz v = normalize_vector( bck_ray.direction);

// 	t_xyz p = bck_ray.origin;

// 	// float a = pow(v.x, 2.0) + pow(v.y, 2.0);
// 	// float b = 2.0 * (p.x * v.x + p.y * v.y);
// 	// float c = pow(p.x, 2.0) + pow(p.y, 2.0) - 1.0;
	
// 	float a = pow(v.x, 2.0) + pow(v.y, 2.0);
// 	float b = 2.0 * (p.x * v.x + p.y * v.y);
// 	float c = pow(p.x, 2.0) + pow(p.y, 2.0) - 1.0;

// 	double	num_sqrt = sqrtf(pow(b, 2.0) - 4 * a * c);


	

// 	t_xyz poi0;
// 	t_xyz poi1;
// 	t_xyz poi2;
// 	t_xyz poi3;

// 	float	t[4];
// 	bool	t1, t2, t3, t4;
// 	if (num_sqrt > 0.0)
// 	{
// 		printf("basic interset\n");
		
// 		// There was an intersection.
// 		// Compute the values for t.
// 		t[0] = (-b + num_sqrt) / (2 * a);
// 		t[1] = (-b - num_sqrt) / (2 * a);
		
// 		// Compute the points of intersection.
// 		poi0 = add_vectors(bck_ray.origin, multiply_vector(v, t[0]));
// 		poi1 = add_vectors(bck_ray.origin, multiply_vector(v, t[1]));
		
// 		// Check if any of these are valid.
// 		if ((t[0] > 0.0) && (fabs(poi0.z) < 1.0))
// 		{
// 			t1 = true;
// 		}
// 		else
// 		{
// 			t1 = false;
// 			t[0] = RAY_T_MAX;
// 		}
		
// 		if ((t[1] > 0.0) && (fabs(poi1.z) < 1.0))
// 		{
// 			t2 = true;
// 		}
// 		else
// 		{
// 			t2 = false;
// 			t[1] = RAY_T_MAX;
// 		}
// 	}
// 	else
// 	{
// 		t1 = false;
// 		t2 = false;
// 		t[0] = RAY_T_MAX;
// 		t[1] = RAY_T_MAX;
// 	}


// 	// test end caps

// 	if (close_enough(v.x, 0.0))			// dan is de cap gelijk aan de ray dus geen intersect
// 	{
// 		t3 = false;
// 		t4 = false;
// 		t[2] = RAY_T_MAX;
// 		t[3] = RAY_T_MAX;
// 	}
// 	else		// intersect met cap
// 	{
// 		t[2] = (bck_ray.origin.z - 1.0) / -v.z;		// dit is een plane op -1 z
// 		t[3] = (bck_ray.origin.z + 1.0) / -v.z;		// en 1 op +1 z. dit kan alleen omdat we met een unit cylinder werken in local

// 		// comput intersect
// 		poi2 = add_vectors(bck_ray.origin, multiply_vector(v, t[2]));
// 		poi3 = add_vectors(bck_ray.origin, multiply_vector(v, t[3]));

// 								// test x^2 + y2 , dus of hij de cirkel raakt
// 		if ((t[2] > 0.0) && ((sqrtf(pow(poi2.x, 2.0)) + sqrtf(pow(poi2.y, 2.0))) < 1.0 ))
// 		{
// 			t3 = true;
// 		}
// 		else
// 		{
// 			t3 = false;
// 			t[2] = RAY_T_MAX;
// 		}
		
// 		if ((t[3] > 0.0) && ((sqrtf(pow(poi3.x, 2.0)) + sqrtf(pow(poi3.y, 2.0))) < 1.0 ))
// 		{
// 			t4 = true;
// 		}
// 		else
// 		{
// 			t4 = false;
// 			t[3] = RAY_T_MAX;
// 		}
// 	}

// 	// geen intersect dan stop
// 	if (!t1 && !t2 && !t3 && !t4)
// 	{
// 		return (RAY_T_MAX);
// 	}
	
	

// 	float 	temp_cyl = ft_min_float(t[0], t[1]);
// 	float	temp_cap = ft_min_float(t[2], t[3]);

// 	t_xyz	valid_poi;
// 	float	valid_t;

// 	// als ray cylinder raakt krijg je andere normal dan wanneer hij de cap raakt.
// 	//  https://youtu.be/UTz7ytMJ2yk?t=2642
// 	if (temp_cyl < temp_cap)
// 	{
		
// 		if (t[0] < t[1])
// 		{
// 			valid_t = t[0];
// 			valid_poi = poi0;
// 		}	
// 		else
// 		{
// 			valid_t = t[1];	
// 			valid_poi = poi1;
// 		}
		
// 		t_xyz intersect_point = apply_matrix4_to_vector(to_world, valid_poi);
			
// 		// bereken cylinder normal
// 		t_xyz 	original_normal;
// 		t_xyz 	new_normal;
// 		t_xyz	local_origin;
// 		local_origin.x = 0;
// 		local_origin.y = 0;
// 		local_origin.z = 0;
// 		t_xyz	world_origin = apply_matrix4_to_vector(to_world, local_origin);
		
// 		original_normal.x = valid_poi.x;
// 		original_normal.y = valid_poi.y;
// 		original_normal.z = 0;
		
// 		new_normal = substract_vectors(apply_matrix4_to_vector(to_world, original_normal), world_origin);
// 		new_normal = normalize_vector(new_normal);


// 		if (valid_t < closest_object->t && RAY_T_MIN < valid_t && valid_t < RAY_T_MAX)
// 		{
// 			closest_object->normal = new_normal;
// 		}
// 		return (valid_t);
// 	}
// 	else
// 	{
// 		// bereken cap normal
			
// 		if (t[2] < t[3])
// 		{
// 			valid_t = t[2];
// 			valid_poi = poi2;
// 		}	
// 		else
// 		{
// 			valid_t = t[3];	
// 			valid_poi = poi3;
// 		}


// 		if (!close_enough(v.z, 0.0))
// 		{
			
// 			// kijken of we in de disk/cap zitten
// 			if (sqrtf(pow(valid_poi.x, 2.0) + pow(valid_poi.y, 2.0)) < 1.0)
// 			{
				
// 				t_xyz intersect_point = apply_matrix4_to_vector(to_world, valid_poi);

// 				t_xyz 	local_origin;
// 				t_xyz 	normal_vector;
// 				t_xyz	global_origin;
// 				t_xyz	local_normal;
				
// 				local_origin.x = 0;
// 				local_origin.y = 0;
// 				local_origin.z = 0;
// 				normal_vector.x = 0;
// 				normal_vector.y = 0;
// 				normal_vector.z = valid_poi.z;
// 				global_origin = apply_matrix4_to_vector(to_world, local_origin);
// 				local_normal = substract_vectors(apply_matrix4_to_vector(to_world, normal_vector), global_origin);
// 				local_normal = normalize_vector(local_normal);
				
// 				if (valid_t < closest_object->t && RAY_T_MIN < valid_t && valid_t < RAY_T_MAX)
// 				{
// 					closest_object->normal = local_normal;
// 				}
// 				return (valid_t);
// 			}
// 			else
// 				return (RAY_T_MAX);
// 		}
// 		else
// 			return (RAY_T_MAX);
// 	}	
// 	return (RAY_T_MAX);		
// }
