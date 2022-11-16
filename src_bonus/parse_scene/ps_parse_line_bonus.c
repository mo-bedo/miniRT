/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_parse_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/16 18:46:42 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "main_bonus.h"
#include "parse_scene/ps_parse_objects_bonus.h"
#include "parse_scene/ps_utils_bonus.h"
#include "utils/u_bonus.h"

// 					C
// 
// 
//	A				B
// 	A  = camera.center
//  B  = point (0,0) on canvas
// 	BC  = height of canvas / 2
// 	BC = distance to canvas
// 	The angle CAB is the field of view / 2
// 	The distance to the canvas = BC / tan(CAB)
static void	parse_camera(t_mlx *mlx, char *line)
{
	float	field_of_view;

	line++;
	mlx->camera.center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->camera.orientation = parse_orientation(&line);
	field_of_view = parse_float(&line, MIN_FOV, MAX_FOV) / 2 * (PI / 180);
	mlx->camera.canvas_distance = 1.0 / tanf(field_of_view / 2) * WINDOW_HEIGHT;
}

static void	parse_lights(t_mlx *mlx, char *line)
{
	static int	i = 0;
	float		brightness;
	t_xyz		color;

	if (str_is_equal(line, "A", 1))
	{
		line++;
		brightness = parse_float(&line, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
		color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
		mlx->ambient_light.color.x = color.x / MAX_COLOR * brightness;
		mlx->ambient_light.color.y = color.y / MAX_COLOR * brightness;
		mlx->ambient_light.color.z = color.z / MAX_COLOR * brightness;
	}
	else if (str_is_equal(line, "L", 1))
	{
		line++;
		mlx->light[i].origin = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		brightness = parse_float(&line, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
		color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
		mlx->light[i].color.x = color.x / MAX_COLOR * brightness;
		mlx->light[i].color.y = color.y / MAX_COLOR * brightness;
		mlx->light[i].color.z = color.z / MAX_COLOR * brightness;
		mlx->light_count = ++i;
	}
}

void	parse_line(t_mlx *mlx, char *line)
{
	if (str_is_equal(line, "#", 1) || str_is_equal(line, "\n", 1) || !line[0])
		return ;
	else if (str_is_equal(line, "B", 1))
	{
		line += 1;
		mlx->background_color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	}
	else if (str_is_equal(line, "C", 1))
		parse_camera(mlx, line);
	else if (str_is_equal(line, "A", 1) || str_is_equal(line, "L", 1))
		parse_lights(mlx, line);
	else if (str_is_equal(line, "pl", 2) || str_is_equal(line, "sp", 2)
		|| str_is_equal(line, "cy", 2) || str_is_equal(line, "co", 2))
		parse_objects(mlx, line);
	else
		error_message_and_exit("Unknown type identifier");
}
