/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:42:20 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/12 12:44:29 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace/rt_.h"
#include "ray_trace/rt_uv_pattern.h"
#include "intersection/i_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

# define BUMP_SCALE 30

// sebastiandang.github.io/docs/cse168/RayTracing.pdf
static void	compute_normal(t_object *object)
{
	if (!object->type)
		return;
	if (object->type == SPHERE)
		object->normal = substract_vectors(object->intersect, object->center);
	else if (object->type == PLANE)
		object->normal = object->orientation;
	if (object->type != NONE && object->bump)
	{
		t_xyz bump = get_uv_pattern(BUMP_MAP, *object);
		object->normal.x += BUMP_SCALE * bump.x;
		object->normal.y += BUMP_SCALE * bump.x;
		object->normal.z += BUMP_SCALE * bump.x;
	}
	object->normal = normalize_vector(object->normal);
}

// Find the closest intersection between a ray and objects in the scene.
t_object get_closest_intersection(t_mlx mlx, t_ray ray,
								  float max_distance)
{
	t_object closest_object;
	int i;
	double t;

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
			t = get_intersection_ray_cylinder(ray, &mlx.object[i]);
		if (t < closest_object.t && RAY_T_MIN < t && t < max_distance)
		{
			closest_object = mlx.object[i];
			closest_object.t = t;
			closest_object.id = i;
		}
		i++;
	}
	closest_object.intersect = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	compute_normal(&closest_object);
	return (closest_object);
}
