/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interaction.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 21:07:02 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

#include <math.h>

# define PI 3.14f

t_uv	map_plane_to_2d(t_xyz position)
{
	t_uv	uv;

	uv.u = position.x + WINDOW_WIDTH;
	uv.v = position.z + WINDOW_HEIGHT;
	return (uv);
}

// www.raytracerchallenge.com/bonus/texture-mapping.html
t_uv	map_sphere_to_2d(t_closest_object object)
{
	t_uv	uv;
	t_xyz	radius_vector;
	float	theta;
	float	phi;
	float	raw_u;

	radius_vector = substract_vectors(object.center, object.position);

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

t_xyz	uv_checkers_pattern_at(t_uv	uv, int tiles_width, int tiles_height)
{
	t_xyz	black;
	t_xyz	white;

	initialize_black_color(&black);
	initialize_white_color(&white);
	uv.u *= tiles_width;
	uv.v *= tiles_height;
	if (((int)uv.u + (int)uv.v) % 2)
		return (white);
	return (black);
}

t_xyz	get_checkers_color(t_closest_object object)
{
	t_uv	uv;

	uv.u = 0;
	uv.v = 0;
	if (object.object_id == PLANE)
		return (uv_checkers_pattern_at(map_plane_to_2d(object.position), 2, 2));
	if (object.object_id == SPHERE)
		return (uv_checkers_pattern_at(map_sphere_to_2d(object), 20, 10));
	return (uv_checkers_pattern_at(uv, 2, 2));
}
