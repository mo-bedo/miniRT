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
#include "parse_scene/ps_utils.h"
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
	int x = (int)((uv.u) * (object.texture_map.width - 1));
	int y = (int)((uv.v) * (object.texture_map.height - 1));
	if (object.type == PLANE)
	{
		x = (int)(uv.u * PLANE_MAP_SCALE);
		y = (int)(uv.v * PLANE_MAP_SCALE);
		if (x < 0)
			x *= -1;
		while (x >= (int)object.texture_map.width)
			x -= (int)object.texture_map.width;
		if (y < 0)
			y *= -1;
		while (y >= (int)object.texture_map.height)
			y -= (int)object.texture_map.height;
	}
	return (object.texture_map.map[y][x]);
}

t_xyz	bump_map_at(t_uv uv, t_object object)
{
	int x = (int)((uv.u) * (object.bump_map.width - 1));
	int y = (int)((uv.v) * (object.bump_map.height - 1));
	if (object.type == PLANE)
	{
		x = (int)(uv.u * PLANE_MAP_SCALE);
		y = (int)(uv.v * PLANE_MAP_SCALE);
		if (x < 0)
			x *= -1;
		while (x >= (int)object.bump_map.width)
			x -= (int)object.bump_map.width;
		if (y < 0)
			y *= -1;
		while (y >= (int)object.bump_map.height)
			y -= (int)object.bump_map.height;
	}
	return (divide_vector(object.bump_map.map[y][x], (float)MAX_COLOR));
}

t_xyz	get_uv_pattern(int pattern, t_object object)
{
	t_uv	uv;
	t_xyz	empty;

	uv = map_to_2d(object);
	if (pattern == CHECKERS)
		return (checkers_pattern_at(uv, object.type));
	if (pattern == TEXTURE)
		return(image_color_at(uv, object));
	if (pattern == BUMP_MAP)
		return(bump_map_at(uv, object));	
	initialize_black_color(&empty);
	return (empty);
}
