/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:42:20 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/10 16:26:38 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace/rt_.h"
#include "intersection/i_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

static void	transfer_plane(t_closest_object *closest_object, t_objects o,
	t_ray ray, float max_distance)
{
	int					i;
	double				t;

	i = 0;
	while (i < o.pl_count)
	{
		t = get_intersection_ray_plane(ray, o.pl[i]);
		if (t < closest_object->t && RAY_T_MIN < t && t < max_distance)
		{
			closest_object->t = t;
			closest_object->object = PLANE;
			closest_object->center = o.pl[i].center;
			closest_object->vector_orientation = o.pl[i].vector_orientation;
			closest_object->color = o.pl[i].color;
			closest_object->specular = o.pl[i].specular;
			closest_object->reflective = o.pl[i].reflective;
		}
		i++;
	}
}

static void	transfer_sphere(t_closest_object *closest_object, t_objects o,
	t_ray ray, float max_distance)
{
	int					i;
	double				t;

	i = 0;
	while (i < o.sp_count)
	{
		t = get_intersection_ray_sphere(ray, o.sp[i]);
		if (t < closest_object->t && RAY_T_MIN < t && t < max_distance)
		{
			closest_object->t = t;
			closest_object->object = SPHERE;
			closest_object->center = o.sp[i].center;
			closest_object->radius = o.sp[i].radius;
			closest_object->color = o.sp[i].color;
			closest_object->specular = o.sp[i].specular;
			closest_object->reflective = o.sp[i].reflective;
		}
		i++;
	}
}

static void	transfer_cylinder(t_closest_object *closest_object, t_objects o,
	t_ray ray, float max_distance)
{
	int					i;
	double				t;

	i = 0;
	while (i < o.cy_count)
	{
		t = get_intersection_ray_cylinder(closest_object, ray, o.cy[i]);
		if (t <= closest_object->t && RAY_T_MIN < t && t < max_distance)
		{
	
			closest_object->t = t;
			closest_object->object = CYLINDER;
			closest_object->center = o.cy[i].center;
			closest_object->vector_orientation = o.cy[i].vector_orientation;
			closest_object->radius = o.cy[i].radius;
			closest_object->height = o.cy[i].height;
			closest_object->color = o.cy[i].color;
			closest_object->specular = o.cy[i].specular;
			closest_object->reflective = o.cy[i].reflective;
		}
		i++;
	}
}

// float	get_triangle_intersection(t_ray ray)	;


// static void	transfer_triangle(t_closest_object *closest_object, t_objects o,
// 	t_ray ray, float max_distance)
// {
// 	float t;

// 	t = get_triangle_intersection(ray);
// 	if (t < closest_object->t && RAY_T_MIN < t && t < max_distance )
// 	{
// 		closest_object->t = t;
// 		closest_object->object = 25;
		
// 		closest_object->vector_orientation.x = 0;
// 		closest_object->vector_orientation.y = 0;
// 		closest_object->vector_orientation.z = -1;
		
		
// 		closest_object->color.x = 0;
// 		closest_object->color.y = 255;
// 		closest_object->color.z = 0;
// 			closest_object->specular = 200;
// 			closest_object->reflective = 25;
// 	}
// }

static void	compute_normal(t_closest_object *object)
{
	if (!object->object)
		return ;
	if (object->object == SPHERE)
		object->normal = substract_vectors(object->position, object->center);
	else if (object->object == PLANE || object->object == 25)
		object->normal = object->vector_orientation;
	// else if (object->object == SPHERE) 
		// object->normal = get_cylinder_normal(object);	
	object->normal = normalize_vector(object->normal);
}

// Find the closest intersection between a ray and objects in the scene.
t_closest_object	get_closest_intersection(t_objects o, t_ray ray,
	float max_distance)
{
	t_closest_object	closest_object;

	closest_object.t = RAY_T_MAX;
	closest_object.object = NONE;
	transfer_plane(&closest_object, o, ray, max_distance);
	transfer_sphere(&closest_object, o, ray, max_distance);
	transfer_cylinder(&closest_object, o, ray, max_distance);
	// transfer_triangle(&closest_object, o, ray, max_distance);
	closest_object.position = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	compute_normal(&closest_object);
	return (closest_object);
}
