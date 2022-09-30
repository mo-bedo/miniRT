/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 15:31:34 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace.h"
#include "lighting.h"
#include "intersection/i_.h"
#include "intersection/i_cylinder.h"
#include "pixel_put.h"
#include "utils/utils.h"
#include "utils/vector_math.h"

// void	tranfer_object_values(t_closest_object *object, )
// {
	
// }

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
	// closest_object.plane = NULL;
	// closest_object.sphere = NULL;
	i = 0;
	while (i < mlx->o.pl_count)
	{
		t = get_intersection_ray_plane(ray, mlx->o.pl[i]);
		if (t < closest_object.t && min_distance < t && t < max_distance)
		{
			closest_object.t = t;
			closest_object.object = PLANE;
			// closest_object.plane = &mlx->o.pl[i];
			closest_object.center = mlx->o.pl[i].center;
			closest_object.vector_orientation = mlx->o.pl[i].vector_orientation;
			// closest_object.radius = mlx->o.pl[i].radius;
			// closest_object.height = mlx->o.pl[i].height;
			closest_object.color = mlx->o.pl[i].color;
			closest_object.specular = mlx->o.pl[i].specular;
			closest_object.reflective = mlx->o.pl[i].reflective;
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
			// closest_object.sphere = &mlx->o.sp[i];
			closest_object.center = mlx->o.sp[i].center;
			closest_object.radius = mlx->o.sp[i].radius;
			// closest_object.height = mlx->o.sp[i].height;
			closest_object.color = mlx->o.sp[i].color;
			closest_object.specular = mlx->o.sp[i].specular;
			closest_object.reflective = mlx->o.sp[i].reflective;
		}
		i++;
	}
	i = 0;
	while (i < mlx->o.cy_count)
	{
		t = get_intersection_ray_cylinder(ray, mlx->o.cy[i]);
		if (t < closest_object.t && min_distance < t && t < max_distance)
		{
			closest_object.t = t;
			closest_object.object = CYLINDER;
			// closest_object.sphere = &mlx->o.cy[i];
			closest_object.center = mlx->o.cy[i].center;
			closest_object.vector_orientation = mlx->o.cy[i].vector_orientation;
			closest_object.radius = mlx->o.cy[i].radius;
			closest_object.height = mlx->o.cy[i].height;
			closest_object.color = mlx->o.cy[i].color;
			closest_object.specular = mlx->o.cy[i].specular;
			closest_object.reflective = mlx->o.cy[i].reflective;
		}
		i++;
	}


	closest_object.position = add_vectors(ray.origin,
			multiply_vector(ray.direction, closest_object.t));
	return (closest_object);
}
