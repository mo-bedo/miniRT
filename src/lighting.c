/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:40:36 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "main.h"
#include "ray_trace.h"
#include "intersection/i_.h"
#include "utils/utils.h"
#include "utils/vector_math.h"

// Computes the reflection of v1 respect to v2.
t_xyz	get_reflection_of_vector_1_towards_vector_2(t_xyz v1, t_xyz v2)
{
	return (substract_vectors(multiply_vector(
				v2, 2 * get_dot_product(v1, v2)), v1));
}

// formule uitleggen
double	compute_diffuse_reflection(t_xyz normal,
	t_ray light_ray, float brightness)
{
	double	normal_dot_product_light;
	double	intensity;

	intensity = 0;
	normal_dot_product_light = get_dot_product(normal, light_ray.direction);
	if (normal_dot_product_light > 0)
		intensity = brightness * normal_dot_product_light \
			/ (LENGTH_NORMAL * get_vector_length(light_ray.direction));
	return (intensity);
}

// formule uitleggen
double	compute_specular_reflection(t_xyz normal, t_ray light_ray,
	float brightness, t_xyz view, int specular)
{
	double	intensity;
	double	length_v;
	double	r_dot_v;
	t_xyz	vec_r;

	intensity = 0;
	if (specular != -1)
	{
		length_v = get_vector_length(view);
		vec_r = get_reflection_of_vector_1_towards_vector_2(
				light_ray.direction, normal);
		r_dot_v = get_dot_product(vec_r, view);
		if (r_dot_v > 0)
			intensity = brightness * pow(r_dot_v \
				/ (get_vector_length(vec_r) * length_v), specular);
	}
	return (intensity);
}

// hoezo is max_distance 1.0?
double	compute_lighting(t_mlx *mlx, t_xyz normal,
	t_xyz view, t_closest_object object)
{
	t_ray				light_ray;
	double				intensity;
	float				max_distance;
	t_closest_object	blocker;

	intensity = mlx->ambient_light.lighting_ratio;
	light_ray.origin = object.position;
	light_ray.direction = substract_vectors
		(mlx->point_light.origin, object.position);
	max_distance = 1.0;
	blocker = get_closest_intersection(mlx, light_ray, RAY_T_MIN, max_distance);
//	if (blocker.object == SPHERE)
	if (!blocker.object)
	{
		intensity += compute_diffuse_reflection(normal, light_ray,
				mlx->point_light.brightness);
		if (object.object == SPHERE)
			intensity += compute_specular_reflection(normal, light_ray,
					mlx->point_light.brightness, view, object.sphere->specular);
		if (object.object == PLANE)
			intensity += compute_specular_reflection(normal, light_ray,
					mlx->point_light.brightness, view, object.plane->specular);
	}
	return (intensity);
}
