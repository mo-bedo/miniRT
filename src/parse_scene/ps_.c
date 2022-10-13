/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 13:47:46 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/ps_parse_objects.h"
#include "parse_scene/ps_utils.h"
#include "utils/u_vector_math.h"
#include "utils/u_.h"
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

static void	check_if_capital_elements_are_declared_multiple_times(char *line)
{
	static int	a = 0;
	static int	c = 0;
	static int	l = 0;

	if (str_is_equal(line, "A", 1))
		a++;
	else if (str_is_equal(line, "C", 1))
		c++;
	// else if (str_is_equal(line, "L", 1))
		// l++;
	if (a > 1 || l > 1)
		error_message_and_exit("Scene declares multiple lights");
	if (c > 1)
		error_message_and_exit("Scene declares multiple cameras");
}

static void	parse_lights(t_mlx *mlx, char *line)
{
	static int	i = 0;
	double		brightness;
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
	t_xyz	std_camera_orientation;
	t_xyz	orientation;
	float	field_of_view;

	line++;
	mlx->camera.center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	orientation = parse_orientation(&line);
	field_of_view = parse_float(&line, MIN_FOV, MAX_FOV) / 2 * (3.14 / 180);
	mlx->camera.canvas_distance = 1.0 / tan(field_of_view / 2);
	std_camera_orientation.x = 0;
	std_camera_orientation.y = 0;
	std_camera_orientation.z = 1;
	mlx->camera.rotation_angles = get_angle_over_the_axes(
			std_camera_orientation, orientation);
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
	else if (str_is_equal(line, "A", 1) || str_is_equal(line, "L", 1))
		parse_lights(mlx, line);
	else if (str_is_equal(line, "C", 1))
		parse_camera(mlx, line);
	else if (str_is_equal(line, "pl", 2) || str_is_equal(line, "sp", 2)
		|| str_is_equal(line, "cy", 2))
		parse_objects(mlx, line);
	else
		error_message_and_exit("Unknown type identifier");
}

void	parse_scene(t_mlx *mlx, int argc, char *input)
{
	int		rt_file;
	int		there_is_a_new_line;
	char	*line;

	if (argc != 2 || !has_valid_extension(input, ".rt"))
		error_message_and_exit("Please provide a scene description file");
	rt_file = open(input, O_RDONLY);
	if (rt_file < 0)
		error_message_and_exit(
			"File does not exist or user doesn't have read rights");
	while (1)
	{
		line = (char *)ft_calloc(sizeof(char), 1);
		there_is_a_new_line = get_next_line(&line, rt_file);
		check_if_capital_elements_are_declared_multiple_times(line);
		parse_line(mlx, line);
		free(line);
		if (!there_is_a_new_line)
			return ;
	}
}
