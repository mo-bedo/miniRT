/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 19:18:11 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace.h"
#include "lighting.h"
#include "intersection/i_.h"
#include "pixel_put.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

static void	transfer_plane(t_closest_object *closest_object, t_plane plane, double t)
{
	closest_object->t = t;
	closest_object->object = PLANE;
	closest_object->center = plane.center;
	closest_object->vector_orientation = plane.vector_orientation;
	closest_object->color = plane.color;
	closest_object->specular = plane.specular;
	closest_object->reflective = plane.reflective;
}

static void	transfer_sphere(t_closest_object *closest_object, t_sphere sphere, double t)
{
	closest_object->t = t;
	closest_object->object = SPHERE;
	closest_object->center = sphere.center;
	closest_object->radius = sphere.radius;
	closest_object->color = sphere.color;
	closest_object->specular = sphere.specular;
	closest_object->reflective = sphere.reflective;
}

static void	transfer_cylinder(t_closest_object *closest_object, t_cylinder cylinder, double t)
{
	closest_object->t = t;
	closest_object->object = CYLINDER;
	closest_object->center = cylinder.center;
	closest_object->vector_orientation = cylinder.vector_orientation;
	closest_object->radius = cylinder.radius;
	closest_object->height = cylinder.height;
	closest_object->color = cylinder.color;
	closest_object->specular = cylinder.specular;
	closest_object->reflective = cylinder.reflective;
}

static void	compute_normal(t_closest_object *object)
{
	if (!object->object)
		return ;
	if (object->object == SPHERE)
		object->normal = substract_vectors(object->position, object->center);
	else if (object->object == PLANE)
		object->normal = object->vector_orientation;
	object->normal = normalize_vector(object->normal);
}

// Find the closest intersection between a ray and objects in the scene.
t_closest_object	get_closest_intersection(t_objects o, t_ray ray,
	float min_distance, float max_distance)
{
	int					i;
	double				t;
	t_closest_object	closest_object;

	closest_object.t = RAY_T_MAX;
	closest_object.object = NONE;

	i = 0;
	while (i < o.pl_count)
	{
		t = get_intersection_ray_plane(ray, o.pl[i]);
		if (t < closest_object.t && min_distance < t && t < max_distance)
			transfer_plane(&closest_object, o.pl[i], t);
		i++;
	}
	i = 0;
	while (i < o.sp_count)
	{
		t = get_intersection_ray_sphere(ray, o.sp[i]);
		if (t < closest_object.t && min_distance < t && t < max_distance)
			transfer_sphere(&closest_object, o.sp[i], t);
		i++;
	}
	// i = 0;
	// while (i < o.cy_count)
	// {
	// 	t = get_intersection_ray_cylinder(ray, o.cy[i]);
	// 	if (t < closest_object.t && min_distance < t && t < max_distance)
	// 		transfer_cylinder(&closest_object, o.cy[i], t);
	// 	i++;
	// }
	closest_object.position = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	compute_normal(&closest_object);
	return (closest_object);
}
