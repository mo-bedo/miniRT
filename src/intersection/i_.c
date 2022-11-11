/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/11 17:04:39 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ray_trace/rt_.h"
#include "ray_trace/rt_uv_pattern.h"
#include "intersection/i_.h"
#include "utils/u_.h"

// intersect is on the SIDE of the cylinder. We can use dot product to
// find the point 'pt' on the center line of the cylinder, so that the vector 
// (intersect - pt) is orthogonal to the cylinder's orientation.
// t = dot((intersect - cy.bottom_center), cy.orientiation); 
// pt = cy.bottom_center + t * cy.orientiation;
// surface_normal = normalize(hit_pt - pt)));
static void	compute_cylinder_normal(t_object *c)
{
	float	t;
	t_xyz	point_t;

	if (c->is_cap)
	{
		if (c->orientation.z < 0)
			c->normal = c->orientation;
		else
			c->normal = multiply_vector(c->orientation, -1);
	}
	else
	{
		t = get_dot_product(
				subtract_vectors(c->intersect, c->center), c->orientation);
		point_t = add_vectors(c->center, multiply_vector(c->orientation, t));
		c->normal = subtract_vectors(c->intersect, point_t);
	}
}

// sebastiandang.github.io/docs/cse168/RayTracing.pdf
static void	compute_normal(t_object *object)
{
	if (!object->type)
		return ;
	if (object->type == SPHERE)
		object->normal = subtract_vectors(object->intersect, object->center);
	else if (object->type == PLANE)
		object->normal = object->orientation;
	else if (object->type == CYLINDER)
		compute_cylinder_normal(object);
	normalize_vector(&object->normal);
}

static float	get_distance_to_intersection(t_mlx *mlx, int i, t_ray ray)
{
	if (mlx->object[i].type == PLANE)
		return (get_intersection_ray_plane(ray, mlx->object[i]));
	if (mlx->object[i].type == SPHERE)
		return (get_intersection_ray_sphere(ray, &mlx->object[i]));
	if (mlx->object[i].type == CYLINDER)
		return (get_intersection_ray_cylinder(ray, &mlx->object[i]));
	return (RAY_T_MAX);
}

// Find the closest intersection between a ray and objects in the scene.
t_object	get_closest_intersection(t_mlx mlx, t_ray ray, float max_distance)
{
	t_object	closest_object;
	int			i;
	float		t;

	t = RAY_T_MAX;
	i = 0;
	closest_object.t = RAY_T_MAX;
	closest_object.type = NONE;
	closest_object.id = -1;
	while (i < mlx.object_count)
	{
		t = get_distance_to_intersection(&mlx, i, ray);
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
