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
t_uv	map_sphere_to_2d(t_object object)
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

// CHECKERS
t_xyz	checkers_pattern_at(t_uv uv, int type)
{
	t_xyz	black;
	t_xyz	white;
	int		tiles;

	initialize_black_color(&black);
	initialize_white_color(&white);
	tiles = 2;
	uv.u *= tiles;
	uv.v *= tiles;
	if (type == SPHERE)
	{
		uv.u *= tiles * 10;
		uv.v *= tiles * 5;
	}
	if (((int)uv.u + (int)uv.v) % 2)
		return (white);
	return (black);
}

t_xyz	image_color_at(t_uv uv, t_object object)
{
	int x = (int)uv.u * (int)object.texture_map.width / (int)(WINDOW_WIDTH - 1);
	int y = (int)uv.v * (int)object.texture_map.height / (int)(WINDOW_HEIGHT - 1);
	// DEBUG_INT((int)uv.u);
	// DEBUG_INT((int)uv.v);
	// DEBUG_INT((int)object.texture_map.width);
	// DEBUG_INT((int)object.texture_map.height);
	// DEBUG_INT(x);
	// DEBUG_INT(y);
	return (object.texture_map.map[x][y]);
}

t_xyz	get_uv_pattern(int pattern, t_object object)
{
	t_uv	uv;
	t_xyz	empty;

	uv.u = 0;
	uv.v = 0;
	if (object.type == PLANE)
		uv = map_plane_to_2d(object.position);
	if (object.type == SPHERE)
		uv = map_sphere_to_2d(object);

	if (pattern == CHECKERS)
		return (checkers_pattern_at(uv, object.type));
	// if (pattern == IMAGE)
		// return(image_color_at(uv, object));
	// if (pattern == BUMP_MAP)
		// 
	initialize_black_color(&empty);
	return (empty);
}
