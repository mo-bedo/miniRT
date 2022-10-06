/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:07:27 by mweitenb      ########   odam.nl         */
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
			closest_object->object_id = PLANE;
			closest_object->center = o.pl[i].center;
			closest_object->vector_orientation = o.pl[i].vector_orientation;
			closest_object->color = o.pl[i].color;
			closest_object->checkerboard = o.pl[i].checkerboard;
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
			closest_object->object_id = SPHERE;
			closest_object->center = o.sp[i].center;
			closest_object->radius = o.sp[i].radius;
			closest_object->color = o.sp[i].color;
			closest_object->checkerboard = o.sp[i].checkerboard;
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
		t = get_intersection_ray_cylinder(ray, o.cy[i]);
		if (t < closest_object->t && RAY_T_MIN < t && t < max_distance)
		{
			closest_object->t = t;
			closest_object->object_id = CYLINDER;
			closest_object->center = o.cy[i].center;
			closest_object->vector_orientation = o.cy[i].vector_orientation;
			closest_object->radius = o.cy[i].radius;
			closest_object->height = o.cy[i].height;
			closest_object->color = o.cy[i].color;
			closest_object->checkerboard = o.cy[i].checkerboard;
			closest_object->specular = o.cy[i].specular;
			closest_object->reflective = o.cy[i].reflective;
		}
		i++;
	}
}

static void	compute_normal(t_closest_object *object)
{
	if (!object->object_id)
		return ;
	if (object->object_id == SPHERE)
		object->normal = substract_vectors(object->position, object->center);
	else if (object->object_id == PLANE)
		object->normal = object->vector_orientation;
	object->normal = normalize_vector(object->normal);
}

// Find the closest intersection between a ray and objects in the scene.
t_closest_object	get_closest_intersection(t_objects o, t_ray ray,
	float max_distance)
{
	t_closest_object	closest_object;

	closest_object.t = RAY_T_MAX;
	closest_object.object_id = NONE;
	transfer_plane(&closest_object, o, ray, max_distance);
	transfer_sphere(&closest_object, o, ray, max_distance);
	transfer_cylinder(&closest_object, o, ray, max_distance);
	closest_object.position = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	compute_normal(&closest_object);
	return (closest_object);
}
