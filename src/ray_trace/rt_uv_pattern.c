/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_uv_pattern.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 18:26:30 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "main.h"
#include "ray_trace/rt_uv_map_to_2d.h"
#include "parse_scene/ps_utils.h"
#include "utils/u_.h"

static t_xyz	checkers_pattern_at(t_uv uv, t_object object)
{
	t_xyz	white;
	int		tiles;

	initialize_vector(&white, 255, 255, 255);
	tiles = 4;
	uv.u *= tiles;
	uv.v *= tiles;
	if (object.type == SPHERE || object.type == CYLINDER || object.type == CONE)
	{
		if (!is_cap(object.normal, object.orientation))
		{
			uv.u *= tiles;
			if (object.type == SPHERE)
				uv.v *= tiles / 2;
			else
				uv.v *= tiles;
		}
	}
	if (((int)uv.u + (int)uv.v) % 2)
		return (white);
	return (object.color);
}

static t_xyz	image_color_at(t_uv uv, t_object object)
{
	int	x;
	int	y;

	x = (int)((uv.u) * (object.texture_map.width - 1));
	y = (int)((uv.v) * (object.texture_map.height - 1));
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

static t_xyz	bump_map_at(t_uv uv, t_object object)
{
	int	x;
	int	y;

	x = (int)((uv.u) * (object.bump_map.width - 1));
	y = (int)((uv.v) * (object.bump_map.height - 1));
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
		return (checkers_pattern_at(uv, object));
	if (pattern == TEXTURE)
		return (image_color_at(uv, object));
	if (pattern == BUMP_MAP)
		return (bump_map_at(uv, object));
	initialize_vector(&empty, 0, 0, 0);
	return (empty);
}
