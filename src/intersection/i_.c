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

static void	compute_normal(t_object *object)
{
	if (!object->type)
		return ;
	if (object->type == SPHERE)
		object->normal = substract_vectors(object->position, object->center);
	else if (object->type == PLANE)
		object->normal = object->vector_orientation;
	object->normal = normalize_vector(object->normal);
}

// Find the closest intersection between a ray and objects in the scene.
t_object	get_closest_intersection(t_mlx mlx, t_ray ray,
	float max_distance)
{
	t_object	closest_object;
	int			i;
	double		t;

	t = 0;
	i = 0;
	closest_object.t = RAY_T_MAX;
	closest_object.type = NONE;
	while (i < mlx.object_count)
	{
		if (mlx.object[i].type == PLANE)
			t = get_intersection_ray_plane(ray, mlx.object[i]);
		else if (mlx.object[i].type == SPHERE)
			t = get_intersection_ray_sphere(ray, mlx.object[i]);
		else if (mlx.object[i].type == CYLINDER)
			t = get_intersection_ray_cylinder(ray, mlx.object[i]);
		if (t < closest_object.t && RAY_T_MIN < t && t < max_distance)
		{
			closest_object = mlx.object[i];
			closest_object.t = t;
			// DEBUG_DOUBLE(t);
		}
		i++;
	}
	closest_object.position = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	compute_normal(&closest_object);
	return (closest_object);
}
