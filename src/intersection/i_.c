/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_bonus.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/09 20:36:01 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ray_trace/rt_bonus.h"
#include "ray_trace/rt_uv_pattern_bonus.h"
#include "intersection/i_bonus.h"
#include "utils/u_bonus.h"

// To get the normal we need to calculate the point on the axis with the same 
// height as the intersect(axis_intersect).  
// Then it's just normal = intersect - axis_intersect
// 					tip, theta		theta = atan(radius / heigth)
// 					   /|
//  tip_to_intersect  / | 			tip_to_intersect = ||tip - intersect||
// 					 /  | axis_to_intersect	
// 					/___|
// 			intersect	 ?(axis_intersect)
// We get there by calculating the lenght of the axis up to the point at the 
// same height as the intersect (axis_to_intersect) by using 
// cos(theta) = axis_to_intersect / tip_to_intersect,
// Since we know theta and tip_to_intersect we can get axis_to_intersect.
// axis_to_intersect = cos(theta) * tip_to_intersect
static void	compute_cone_normal(t_object *c)
{
	float	theta;
	t_xyz	tip;
	float	tip_to_intersect;
	float	axis_to_intersect;
	t_xyz	axis_intersect;

	theta = atanf(c->radius / c->height);
	if (c->is_cap)
		c->normal = c->orientation;
	else
	{
		tip = add_vectors(c->center, get_negative_vector(
					multiply_vector(c->orientation, c->height * 2)));
		tip_to_intersect = get_vector_length(
				subtract_vectors(c->intersect, tip));
		axis_to_intersect = tip_to_intersect * cosf(theta);
		axis_intersect = add_vectors(tip,
				multiply_vector(c->orientation, axis_to_intersect));
		c->normal = subtract_vectors(c->intersect, axis_intersect);
	}
}

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
	t_xyz	bump;

	if (!object->type)
		return ;
	if (object->type == SPHERE)
		object->normal = subtract_vectors(object->intersect, object->center);
	else if (object->type == PLANE)
		object->normal = object->orientation;
	else if (object->type == CYLINDER)
		compute_cylinder_normal(object);
	else if (object->type == CONE)
		compute_cone_normal(object);
	if (object->type != NONE && object->bump)
	{
		bump = get_uv_pattern(BUMP_MAP, *object);
		object->normal.x += bump.x;
		object->normal.y += bump.y;
		object->normal.z += bump.z;
	}
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
	if (mlx->object[i].type == CONE)
		return (get_intersection_ray_cone(ray, &mlx->object[i]));
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
