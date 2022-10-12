/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:42:20 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/12 11:47:02 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace/rt_.h"
#include "ray_trace/rt_uv_pattern.h"
#include "intersection/i_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"


// p' = p + d(p)n(p)
// where: 
// 		d(p) = the offset returned by the displacement texture at p 
// 		n(p) = the surface normal at p
// static t_xyz	compute_bump_normal(t_object *object)
// {
// 	{
// 		t_xyz bump = get_uv_pattern(BUMP_MAP, *object);
		
		
// 		DEBUG_DOUBLE(bump.x);
// 		DEBUG_DOUBLE(bump.y);
// 		DEBUG_DOUBLE(bump.z);
// 		// // t_xyz temp = 
// 		object->normal.x -= bump.x;
// 		object->normal.y -= bump.y;
// 		object->normal.z -= bump.z;
// 	}
// }

static void	compute_normal(t_object *object)
{
	if (!object->type)
		return ;
	if (object->type == SPHERE)
		object->normal = substract_vectors(object->position, object->center);
	else if (object->type == PLANE)
		object->normal = object->vector_orientation;
	else if (object->type == CYLINDER)
		get_cylinder_normal(object);
	if (object->type != NONE && object->bump)
	{
		// t_xyz bump = get_uv_pattern(BUMP_MAP, *object);
		// object->normal.x = bump.x * 2;
	}
	object->normal = normalize_vector(object->normal);
	// if (object->bump)
		// compute_bump_normal(object);
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
		}
		i++;
	}
	closest_object.position = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	compute_normal(&closest_object);
	return (closest_object);
}
