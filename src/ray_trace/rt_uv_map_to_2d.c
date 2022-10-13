/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_uv_map_to_2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:54:51 by mweitenb          #+#    #+#             */
/*   Updated: 2022/10/13 13:32:25 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

#include <math.h>

# define PI 3.14f

t_uv	map_plane_to_2d(t_xyz intersect)
{
	t_uv	uv;

	uv.u = intersect.x + WINDOW_WIDTH;
	uv.v = intersect.z + WINDOW_HEIGHT;
	return (uv);
}

// www.raytracerchallenge.com/bonus/texture-mapping.html
t_uv	map_sphere_to_2d(t_object object)
{
	t_uv	uv;
	t_xyz	radius_vector;
	float	theta;
	float	phi;
	float	raw_u;

	radius_vector = substract_vectors(object.center, object.intersect);

	// compute the azimuthal angle
	// -π < theta <= π
	// angle increases clockwise as viewed from above,
	// which is opposite of what we want, but we'll fix it later.
	theta = atan2(radius_vector.x, radius_vector.z);

	// compute the polar angle
	// 0 <= phi <= π
	phi = acos(radius_vector.y / object.radius);

	// -0.5 < raw_u <= 0.5
	raw_u = theta / (2 * PI);

	// 0 <= u < 1
	// here's also where we fix the direction of u. Subtract it from 1,
	// so that it increases counterclockwise as viewed from above.
	uv.u = 1 - (raw_u + 0.5);

	// we want v to be 0 at the south pole of the sphere,
	// and 1 at the north pole, so we have to "flip it over"
	// by subtracting it from 1.
	uv.v = 1 - phi / PI;
	return (uv);
}

t_uv	map_to_2d(t_object object)
{
	t_uv	uv;

	uv.u = 0;
	uv.v = 0;
	if (object.type == PLANE)
		return(map_plane_to_2d(object.intersect));
	if (object.type == SPHERE)
		return(map_sphere_to_2d(object));
	return (uv);
}
