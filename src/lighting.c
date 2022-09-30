/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 15:20:06 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "main.h"
#include "ray_trace.h"
#include "intersection/i_.h"
#include "utils/utils.h"
#include "utils/vector_math.h"

// computes how ray would reflect from surface
//   = 2 * the direction of the normal
// 	   * the dot product of the direction of the normal and the lightray
//     - the direction of the lightray
t_xyz	compute_reflected_ray(t_xyz ray_direction, t_xyz normal)
{
	return (substract_vectors(multiply_vector(normal,
				2 * get_dot_product(ray_direction, normal)),
			ray_direction));
}

// the fraction of diffuse light that is reflected
//  	= dot product of the direction of the normal and the lightray /
// 				length of normal * length of lightray
// If this value is negative we can end up with a light source that 
// makes a surface darker... In that case, we need to treat it as if it was 0.
static double	compute_diffuse_reflection(t_xyz normal, t_ray light_ray)
{
	double	denominator;
	double	divisor;

	denominator = get_dot_product(normal, light_ray.direction);
	if (denominator <= 0)
		return (0);
	divisor = LENGTH_NORMAL * get_vector_length(light_ray.direction);
	return (denominator / divisor);
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
double	compute_specular_reflection(t_xyz normal, t_ray light_ray,
	t_xyz view, int specular)
{
	double	denominator;
	double	divisor;
	t_xyz	reflection;

	if (specular != -1)
		return (0);
	reflection = compute_reflected_ray(light_ray.direction, normal);
	denominator = get_dot_product(reflection, view);
	if (denominator <= 0)
		return (0);
	divisor = get_vector_length(reflection) * get_vector_length(view);
	return (pow(denominator / divisor, specular));
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
	if (!blocker.object)
	{
		intensity += mlx->point_light.brightness * compute_diffuse_reflection(
				normal, light_ray);
		intensity += mlx->point_light.brightness * compute_specular_reflection(
				normal, light_ray, view, object.specular);
	}
	return (intensity);
}
