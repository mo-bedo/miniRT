/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_parse_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/30 15:47:13 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/ps_utils.h"
#include "utils/u_vector_math.h"
#include "utils/u_.h"
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

static void	parse_lights(t_mlx *mlx, char *line)
{
	if (ft_strncmp(line, "A", 1) == 0)
	{
		line++;
		mlx->ambient_light.lighting_ratio = parse_float(&line,
				MIN_LIGHTING_RATIO, MAX_LIGHTING_RATIO);
		mlx->ambient_light.color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	}
	else if (ft_strncmp(line, "L", 1) == 0)
	{
		line++;
		mlx->light.origin = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->light.brightness = parse_float(&line,
				MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	}
}


// t_xyz get_rotation_angles(t_camera camera, t_xyz vector_orientation)
// {
// 	t_xyz	rotation_angles;

// 	rotation_angles.x = calc;
// 	rotation_angles.y = 0; //atan(vector_orientation.x / vector_orientation.z);
// 	rotation_angles.z = 0; //90 * (vector_orientation.z - camera.center.z);;
// 	// DEBUG_DOUBLE(vector_orientation.y);
// 	// DEBUG_DOUBLE(vector_orientation.z);
// 	return (rotation_angles);
// }


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
	vector_orientation = parse_xyz(&line, MIN_3D, MAX_3D);
	field_of_view = parse_float(&line, MIN_FOV, MAX_FOV) / 2;
	field_of_view  = field_of_view  * (3.14 / 180);
	// mlx->camera.aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	mlx->camera.canvas_distance = 1.0 / tan(field_of_view / 2);
	std_camera_orientation.x = 0;
	std_camera_orientation.y = 0;
	std_camera_orientation.z = 1;
	mlx->camera.rotation_angles = get_angle_over_the_axes(std_camera_orientation, vector_orientation);
	// DEBUG_DOUBLE(vector_orientation.y);
	// DEBUG_DOUBLE(vector_orientation.z);
	// DEBUG_FLOAT(mlx->camera.rotation_angles.x);
	// DEBUG_FLOAT(mlx->camera.rotation_angles.y);
	// DEBUG_FLOAT(mlx->camera.rotation_angles.z);
	// DEBUG_FLOAT(mlx->camera.field_of_view / 2);
	// DEBUG_FLOAT(tan(mlx->camera.field_of_view / 2));
	// DEBUG_FLOAT(mlx->camera.canvas_distance);
}

static void	parse_2d_objects(t_mlx *mlx, char *line)
{
	static int	pl_count = 0;

	line += 2;
	mlx->o.pl[pl_count].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->o.pl[pl_count].vector_orientation = parse_xyz(&line,
			MIN_3D, MAX_3D);
	mlx->o.pl[pl_count].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->o.pl[pl_count].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->o.pl[pl_count].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
	mlx->o.pl_count = ++pl_count;
}

static void	parse_3d_objects(t_mlx *mlx, char *line)
{
	static int	cy_count = 0;
	static int	sp_count = 0;

	if (ft_strncmp(line, "sp", 2) == 0)
	{
		line += 2;
		mlx->o.sp[sp_count].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->o.sp[sp_count].radius = parse_float(&line,
				MIN_DIAMETER, MAX_DIAMETER) / (float)2;
		mlx->o.sp[sp_count].radius_squared = pow(mlx->o.sp[sp_count].radius, 2);
		mlx->o.sp[sp_count].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
		mlx->o.sp[sp_count].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
		mlx->o.sp[sp_count].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
		mlx->o.sp_count = ++sp_count;
	}
	if (ft_strncmp(line, "cy", 2) == 0)
	{
		line += 2;
		mlx->o.cy[cy_count].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->o.cy[cy_count].vector_orientation = parse_xyz(&line,
				MIN_3D, MAX_3D);
		mlx->o.cy[cy_count].radius = parse_float(&line,
				MIN_DIAMETER, MAX_DIAMETER) / (float)2;
		mlx->o.cy[cy_count].height = parse_float(&line,
				MIN_CY_HEIGHT, MAX_CY_HEIGHT);
		mlx->o.cy[cy_count].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
		mlx->o.cy[cy_count].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
		mlx->o.cy[cy_count].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
		mlx->o.cy_count = ++cy_count;
	}
}

void	parse_line(t_mlx *mlx, char *line)
{
	// DEBUG_STR(line);
	if (ft_strncmp(line, "#", 1) == 0 || ft_strncmp(line, "\n", 1) == 0
		|| !line[0])
		return ;
	else if (ft_strncmp(line, "A", 1) == 0 || ft_strncmp(line, "L", 1) == 0)
		parse_lights(mlx, line);
	else if (ft_strncmp(line, "C", 1) == 0)
		parse_camera(mlx, line);
	else if (ft_strncmp(line, "pl", 2) == 0)
		parse_2d_objects(mlx, line);
	else if (ft_strncmp(line, "sp", 2) == 0 || ft_strncmp(line, "cy", 2) == 0)
		parse_3d_objects(mlx, line);
	else
		error_message_and_exit("Unknown type identifier");
}
