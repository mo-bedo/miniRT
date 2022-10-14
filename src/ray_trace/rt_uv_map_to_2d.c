/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_uv_map_to_2d.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 17:47:10 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "main.h"
#include "utils/u_.h"

static t_uv	map_plane_to_2d(t_xyz intersect)
{
	t_uv	uv;

	uv.u = intersect.x + WINDOW_WIDTH;
	uv.v = intersect.z + WINDOW_HEIGHT;
	return (uv);
}

// www.raytracerchallenge.com/bonus/texture-mapping.html
// compute the azimuthal angle (0 < azimuthal_angle <= 2π)
// compute the polar angle (0 <= polar_angle <= π)
// 0 <= uv.u < 1
// Subtract uv.u from 1, so it increases counterclockwise viewed from above.
// Subtract uv.v from 1, so 0 is at the south pole of the sphere
static t_uv	map_sphere_to_2d(t_object object)
{
	t_uv	uv;
	t_xyz	radius_vector;
	float	azimuthal_angle;
	float	polar_angle;

	radius_vector = substract_vectors(object.center, object.intersect);
	azimuthal_angle = atan2(radius_vector.x, radius_vector.z) + PI;
	polar_angle = acos(radius_vector.y / object.radius);
	uv.u = 1 - (azimuthal_angle / (2 * PI));
	uv.v = 1 - polar_angle / PI;
	return (uv);
}

// irisa.fr/prive/kadi/Cours_LR2V/Cours/RayTracing_Texturing.pdf
// sphere
// acos( z / r) / PI
// acos (x / (rsin (PI s))) / 2 PI
// 
// cylinder
// (acos (object.intersect.x / r ) - theta_a) / (theta_b - theta_a)
// acos (object.intersect.z - za)/(zb - za)

static t_uv	map_cylinder_to_2d(t_object object)
{
	t_uv	uv;
	t_xyz	radius_vector;
	float	azimuthal_angle;

	radius_vector = substract_vectors(object.center, object.intersect);
	azimuthal_angle = atan2(radius_vector.x, radius_vector.z) + PI;
	uv.u = 1 - (azimuthal_angle / (2 * PI));
	uv.v = radius_vector.y + object.height;
	while (uv.v > object.height)
		uv.v -= object.height;
	uv.v /= object.height;
	return (uv);
}

t_uv	map_to_2d(t_object object)
{
	t_uv	uv;

	uv.u = 0;
	uv.v = 0;
	if (object.type == PLANE)
		return (map_plane_to_2d(object.intersect));
	if (object.type == SPHERE)
		return (map_sphere_to_2d(object));
	if (object.type == CYLINDER)
		return (map_cylinder_to_2d(object));
	return (uv);
}
