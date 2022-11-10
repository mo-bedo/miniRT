// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   rt_uv_pattern.c                                    :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
// /*   Updated: 2022/11/07 18:22:55 by mweitenb      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include <math.h>
// #include <stdlib.h>

// #include "main.h"
// #include "ray_trace/rt_uv_map_to_2d.h"
// #include "parse_scene/ps_utils.h"
// #include "utils/u_.h"

// static t_xyz	checkers_pattern_at(t_uv uv, t_object object)
// {
// 	t_xyz	white;

// 	initialize_vector(&white, 255, 255, 255);
// 	if (object.type == PLANE)
// 	{
// 		uv.u *= TILE_SIZE_PLANE;
// 		uv.v *= TILE_SIZE_PLANE;
// 	}
// 	else
// 	{
// 		uv.u *= TILE_SIZE;
// 		uv.v *= TILE_SIZE;
// 		if (object.type == SPHERE)
// 			uv.v /= 2;
// 	}
// 	if (((int)uv.u + (int)uv.v) % 2)
// 		return (white);
// 	return (object.color);
// }

// static t_xy	translate_to_flat_surface(t_uv uv, t_map map)
// {
// 	t_xy	xy;

// 	xy.x = (int)(uv.u * PLANE_MAP_SCALE);
// 	xy.y = (int)(uv.v * PLANE_MAP_SCALE);
// 	if (xy.x < 0)
// 		xy.x *= -1;
// 	while (xy.x >= (int)map.width)
// 		xy.x -= (int)map.width;
// 	if (xy.y < 0)
// 		xy.y *= -1;
// 	while (xy.y >= (int)map.height)
// 		xy.y -= (int)map.height;
// 	return (xy);
// }

// static t_xyz	image_color_at(t_uv uv, t_object object)
// {
// 	t_xy	xy;

// 	if (object.is_cap)
// 		xy = translate_to_flat_surface(uv, object.texture_map);
// 	else
// 	{
// 		xy.x = (int)((uv.u) * (object.texture_map.width - 1));
// 		xy.y = (int)((uv.v) * (object.texture_map.height - 1));
// 	}
// 	return (object.texture_map.map[xy.y][xy.x]);
// }

// // devide vector by 255 so we get a value between 0 and 1
// // substract 0.5 so we get a value between -0.5 and 0.5
// static t_xyz	bump_map_at(t_uv uv, t_object object)
// {
// 	t_xy	xy;
// 	t_xyz	bump;

// 	if (object.is_cap)
// 		xy = translate_to_flat_surface(uv, object.bump_map);
// 	else
// 	{
// 		xy.x = (int)((uv.u) * (object.bump_map.width - 1));
// 		xy.y = (int)((uv.v) * (object.bump_map.height - 1));
// 	}
// 	bump = divide_vector(object.bump_map.map[xy.y][xy.x], (float)MAX_COLOR);
// 	bump.x -= 0.5;
// 	bump.y -= 0.5;
// 	bump.z -= 0.5;
// 	return (bump);
// }

// t_xyz	get_uv_pattern(int pattern, t_object object)
// {
// 	t_uv	uv;
// 	t_xyz	empty;

// 	uv = map_to_2d(object);
// 	if (pattern == CHECKERS)
// 		return (checkers_pattern_at(uv, object));
// 	if (pattern == TEXTURE)
// 		return (image_color_at(uv, object));
// 	if (pattern == BUMP_MAP)
// 		return (bump_map_at(uv, object));
// 	initialize_vector(&empty, 0, 0, 0);
// 	return (empty);
// }
