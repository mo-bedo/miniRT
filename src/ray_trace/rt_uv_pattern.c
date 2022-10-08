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
#include "ray_trace/rt_uv_map_to_2d.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

#include <math.h>

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
	// wereldbol moet kwartslag draaien (en is nog ook te groot?)
	int x = (int)((uv.u / 2) * (object.texture_map.width - 1));
	int y = (int)((1 - uv.v) * (object.texture_map.height - 1));
	// DEBUG_INT(x);
	// DEBUG_INT(y);
	// DEBUG_FLOAT(object.texture_map.map[x][y].x);
	// DEBUG_FLOAT(uv.u * object.texture_map.width / (WINDOW_WIDTH - 1));
	// DEBUG_FLOAT(uv.u * object.texture_map.width / (WINDOW_HEIGHT - 1);
	return (object.texture_map.map[x][y]);
}

t_xyz	get_uv_pattern(int pattern, t_object object)
{
	t_uv	uv;
	t_xyz	empty;

	uv = map_to_2d(object);
	// DEBUG_FLOAT(uv.u);
	// DEBUG_FLOAT(uv.v);
	// DEBUG_INT((int)uv.u);
	// DEBUG_INT((int)uv.v);

	if (pattern == CHECKERS)
		return (checkers_pattern_at(uv, object.type));
	if (pattern == IMAGE)
		return(image_color_at(uv, object));
	// if (pattern == BUMP_MAP)
		// 
	initialize_black_color(&empty);
	return (empty);
}
