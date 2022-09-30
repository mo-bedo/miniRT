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
#include "utils/utils.h"
#include "utils/vector_math.h"

// void	tranfer_object_values(t_closest_object *object, )
// {
// }

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
// dit kan later nog opgeschoont worden, nu teveel herhaling
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
		{
			closest_object.t = t;
			closest_object.object = PLANE;
			closest_object.center = o.pl[i].center;
			closest_object.vector_orientation = o.pl[i].vector_orientation;
			// closest_object.radius = o.pl[i].radius;
			// closest_object.height = o.pl[i].height;
			closest_object.color = o.pl[i].color;
			closest_object.specular = o.pl[i].specular;
			closest_object.reflective = o.pl[i].reflective;
		}
		i++;
	}
	i = 0;
	while (i < o.sp_count)
	{
		t = get_intersection_ray_sphere(ray, o.sp[i]);
		if (t < closest_object.t && min_distance < t && t < max_distance)
		{
			closest_object.t = t;
			closest_object.object = SPHERE;
			closest_object.center = o.sp[i].center;
			closest_object.radius = o.sp[i].radius;
			// closest_object.height = o.sp[i].height;
			closest_object.color = o.sp[i].color;
			closest_object.specular = o.sp[i].specular;
			closest_object.reflective = o.sp[i].reflective;
		}
		i++;
	}
	i = 0;
	while (i < o.cy_count)
	{
		t = get_intersection_ray_sphere(ray, o.sp[i]);
		if (t < closest_object.t && min_distance < t && t < max_distance)
		{
			closest_object.t = t;
			closest_object.object = CYLINDER;
			closest_object.center = o.cy[i].center;
			closest_object.vector_orientation = o.cy[i].vector_orientation;
			closest_object.radius = o.cy[i].radius;
			closest_object.height = o.cy[i].height;
			closest_object.color = o.cy[i].color;
			closest_object.specular = o.cy[i].specular;
			closest_object.reflective = o.cy[i].reflective;
		}
		i++;
	}
	closest_object.position = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	compute_normal(&closest_object);
	return (closest_object);
}
