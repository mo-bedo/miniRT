/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:33:52 by mweitenb      ########   odam.nl         */
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

// Find the closest intersection between a ray and objects in the scene.
// dit kan later nog opgeschoont worden, nu teveel herhaling
t_closest_object	get_closest_intersection(t_mlx *mlx, t_ray ray,
	float min_distance, float max_distance)
{
	int					i;
	float				t;
	t_closest_object	closest_object;

	closest_object.t = RAY_T_MAX;
	closest_object.object = 0;
	closest_object.plane = NULL;
	closest_object.sphere = NULL;
	i = 0;
	while (i < mlx->o.pl_count)
	{
		t = get_intersection_ray_plane(ray, mlx->o.pl[i]);
		if (t < closest_object.t && min_distance < t && t < max_distance)
		{
			closest_object.t = t;
			closest_object.object = PLANE;
			closest_object.plane = &mlx->o.pl[i];
		}
		i++;
	}
	i = 0;
	while (i < mlx->o.sp_count)
	{
		t = get_intersection_ray_sphere(ray, mlx->o.sp[i]);
		if (t < closest_object.t && min_distance < t && t < max_distance)
		{
			closest_object.t = t;
			closest_object.object = SPHERE;
			closest_object.sphere = &mlx->o.sp[i];
		}
		i++;
	}
	closest_object.position = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	return (closest_object);
}
