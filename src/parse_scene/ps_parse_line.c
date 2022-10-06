/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_parse_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:37:37 by mweitenb      ########   odam.nl         */
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

static void	parse_lights(t_mlx *mlx, char *line)
{
	static int	i = 0;
	double		brightness;
	t_xyz		color;

	if (ft_strncmp(line, "A", 1) == 0)
	{
		line++;
		brightness = parse_float(&line, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
		color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
		mlx->ambient_light.color.x = color.x / MAX_COLOR * brightness;
		mlx->ambient_light.color.y = color.y / MAX_COLOR * brightness;
		mlx->ambient_light.color.z = color.z / MAX_COLOR * brightness;
	}
	else if (ft_strncmp(line, "L", 1) == 0)
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

t_xyz	get_angle_over_the_axes(t_xyz vector1, t_xyz vector2)
{
	t_xyz	angles;
	t_xyz	v1;
	t_xyz	v2;

	v1 = vector1;
	v1.x = 0;
	v2 = vector2;
	v2.x = 0;
		angles.x = get_angle_between_vectors(v1, v2);
	if ((v2.z >= 0 && v1.y < v2.y) || (v2.z < 0 && v1.y > v2.y))
		angles.x *= -1;
	v1 = vector1;
	v1.y = 0;
	v2 = vector2;
	v2.y = 0;
		angles.y = get_angle_between_vectors(v1, v2);
	if ((v2.z >= 0 && v1.x > v2.x) || (v2.z < 0 && v1.x < v2.x))
		angles.y *= -1;
	angles.z = 0;
	if (v2.z < 0)
	{
		angles.y -= (180 * (3.14 / 180));
		angles.z -= -180 * (3.14 / 180);
	}
	return (angles);
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
	t_xyz	vector_orientation;
	float	field_of_view;

	line++;
	mlx->camera.center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	vector_orientation = parse_vector_orientation(&line);
	field_of_view = parse_float(&line, MIN_FOV, MAX_FOV) / 2 * (3.14 / 180);
	mlx->camera.canvas_distance = 1.0 / tan(field_of_view / 2);
	std_camera_orientation.x = 0;
	std_camera_orientation.y = 0;
	std_camera_orientation.z = 1;
	mlx->camera.rotation_angles = get_angle_over_the_axes(
			std_camera_orientation, vector_orientation);
}

void	parse_line(t_mlx *mlx, char *line)
{
	if (ft_strncmp(line, "#", 1) == 0 || ft_strncmp(line, "\n", 1) == 0
		|| !line[0])
		return ;
	else if (ft_strncmp(line, "B", 1) == 0)
	{
			line += 1;
			mlx->background_color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	}
	else if (ft_strncmp(line, "A", 1) == 0 || ft_strncmp(line, "L", 1) == 0)
		parse_lights(mlx, line);
	else if (ft_strncmp(line, "C", 1) == 0)
		parse_camera(mlx, line);
	else if (ft_strncmp(line, "pl", 2) == 0)
		parse_plane(mlx, line);
	else if (ft_strncmp(line, "sp", 2) == 0)
		parse_sphere(mlx, line);
	else if (ft_strncmp(line, "cy", 2) == 0)
		parse_cylinder(mlx, line);
	else
		error_message_and_exit("Unknown type identifier");
}
