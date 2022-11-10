/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_lighting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/09 20:16:29 by mweitenb      ########   odam.nl         */
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

void	compute_lighting(t_object *object, t_mlx *mlx)
{
	t_ray	r;
	t_xyz	intensity;
	int		i;

	initialize_vector(&intensity, 0, 0, 0);
	i = -1;
	while (++i < mlx->light_count)
	{
		r.origin = object->intersect;
		r.direction = subtract_vectors(mlx->light[i].origin, object->intersect);
		if (light_is_blocked_by_another_object(*mlx, r))
			continue ;
		intensity = add_vectors(intensity, compute_diffuse_reflection(
					object->normal, r, mlx->light[i].color));
	}
	object->color.x *= (mlx->ambient_light.color.x + intensity.x);
	object->color.y *= (mlx->ambient_light.color.y + intensity.y);
	object->color.z *= (mlx->ambient_light.color.z + intensity.z);
}
