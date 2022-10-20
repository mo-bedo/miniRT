/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:42:20 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/16 15:29:42 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "main.h"
#include "ray_trace/rt_uv_pattern.h"
#include "intersection/i_.h"
#include "utils/u_.h"

static bool	light_is_blocked_by_another_object(t_mlx mlx, t_ray ray)
{
	t_object	object;

	object = get_closest_intersection(mlx, ray, LENGTH_NORMAL);
	return (object.type);
}

// computes how ray would reflect from surface
//   = 2 * the direction of the normal
// 	   * the dot product of the direction of the normal and the lightray
//     - the direction of the lightray
t_xyz	compute_reflected_ray(t_xyz ray_direction, t_xyz normal)
{
	return (subtract_vectors(multiply_vector(normal,
				2 * get_dot_product(ray_direction, normal)),
			ray_direction));
}

// the fraction of diffuse light that is reflected
//  	= dot product of the direction of the normal and the lightray /
// 				length of normal * length of lightray
// If this value is negative we can end up with a light source that 
// makes a surface darker... In that case, we need to treat it as if it was 0.
static t_xyz	compute_diffuse_reflection(t_xyz normal,
	t_ray light_ray, t_xyz color)
{
	float	denominator;
	float	divisor;
	t_xyz	intensity;
	float	diffuse_reflection;

	initialize_vector(&intensity, 0, 0, 0);
	denominator = get_dot_product(normal, light_ray.direction);
	if (denominator <= 0)
		return (intensity);
	divisor = LENGTH_NORMAL * get_vector_length(light_ray.direction);
	diffuse_reflection = denominator / divisor;
	intensity.x = color.x * diffuse_reflection;
	intensity.y = color.y * diffuse_reflection;
	intensity.z = color.z * diffuse_reflection;
	return (intensity);
}

// the fraction of specular light that is reflected
//  	= (dot product of the direction of R and view /
// 				length of R * length of view) ^ specular value
// where R = the reflected ray
//   = 2 * the direction of the normal
// 	   * the dot product of the direction of the normal and the lightray
//     - the direction of the lightray
// specular = -1 means that the object is matte and therefor no
// specular reflection should be computed
// if denominator is negative, we need to treat it as if it was 0 (just
// as with the diffuse reflection).
static t_xyz	compute_specular_reflection(t_ray light_ray,
	t_xyz view, t_object object, t_xyz color)
{
	float	denominator;
	float	divisor;
	t_xyz	reflection;
	float	specular_reflection;
	t_xyz	intensity;

	initialize_vector(&intensity, 0, 0, 0);
	if (object.specular == 0)
		return (intensity);
	reflection = compute_reflected_ray(light_ray.direction, object.normal);
	denominator = get_dot_product(reflection, view);
	if (denominator <= 0)
		return (intensity);
	divisor = get_vector_length(reflection) * get_vector_length(view);
	specular_reflection = pow(denominator / divisor, object.specular);
	intensity.x = color.x * specular_reflection;
	intensity.y = color.y * specular_reflection;
	intensity.z = color.z * specular_reflection;
	return (intensity);
}

void	compute_lighting(t_object *object, t_mlx *mlx, t_xyz view)
{
	t_ray	light_ray;
	t_xyz	intensity;
	int		i;

	initialize_vector(&intensity, 0, 0, 0);
	i = -1;
	while (++i < mlx->light_count)
	{
		light_ray.origin = object->intersect;
		light_ray.direction = subtract_vectors(mlx->light[i].origin, object->intersect);
		light_ray.origin = add_vectors(light_ray.origin, multiply_vector(light_ray.direction, 1.0001));		
		if (light_is_blocked_by_another_object(*mlx, light_ray))
			continue ;
		intensity = add_vectors(intensity, compute_diffuse_reflection(
					object->normal, light_ray, mlx->light[i].color));
		intensity = add_vectors(intensity, compute_specular_reflection(
					light_ray, view, *object, mlx->light[i].color));
	}
	if (object->checkerboard)
		object->color = get_uv_pattern(CHECKERS, *object);
	else if (object->texture)
		object->color = get_uv_pattern(TEXTURE, *object);
	object->color.x *= (mlx->ambient_light.color.x + intensity.x);
	object->color.y *= (mlx->ambient_light.color.y + intensity.y);
	object->color.z *= (mlx->ambient_light.color.z + intensity.z);
}
