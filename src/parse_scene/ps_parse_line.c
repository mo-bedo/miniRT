/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_parse_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 14:12:15 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/ps_utils.h"
#include "utils/vector_math.h"
#include "utils/utils.h"
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
		mlx->ambient_light.rgb = parse_rgb(&line);
	}
	else if (ft_strncmp(line, "L", 1) == 0)
	{
		line++;
		mlx->point_light.xyz = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->point_light.brightness = parse_float(&line,
				MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	}
}

static void	parse_camera(t_mlx *mlx, char *line)
{
	t_xyz	vector_orientation;
	int		field_of_view;
	t_xyz	upguide;

	line++;
	upguide.x = 0.0;
	upguide.y = 1.0;
	upguide.z = 0.0;
	mlx->camera.origin_point = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	vector_orientation = parse_xyz(&line, MIN_3D, MAX_3D);
	field_of_view = parse_int(&line, 0, 180) / 2;
	// mlx->camera.forward = normalize_vector(
			// substract_vectors(vector_orientation, upguide));
	// mlx->camera.right = normalize_vector(
			// get_cross_product(mlx->camera.forward, upguide));
	// mlx->camera.up = get_cross_product(mlx->camera.right, mlx->camera.forward);
	// mlx->camera.height = atan(field_of_view);
	mlx->camera.width = mlx->camera.height * mlx->aspect_ratio;
}

static void	parse_2d_objects(t_mlx *mlx, char *line)
{
	static int	pl_count = 0;

	line += 2;
	mlx->o.pl[pl_count].xyz = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->o.pl[pl_count].vector_orientation = parse_xyz(&line,
			MIN_3D, MAX_3D);
	mlx->o.pl[pl_count].rgb = parse_rgb(&line);
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
		mlx->o.sp[sp_count].rgb = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
		mlx->o.sp_count = ++sp_count;
	}
	if (ft_strncmp(line, "cy", 2) == 0)
	{
		line += 2;
		mlx->o.cy[cy_count].xyz = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->o.cy[cy_count].vector_orientation = parse_xyz(&line,
				MIN_3D, MAX_3D);
		mlx->o.cy[cy_count].diameter = parse_float(&line,
				MIN_DIAMETER, MAX_DIAMETER);
		mlx->o.cy[cy_count].height = parse_float(&line,
				MIN_CY_HEIGHT, MAX_CY_HEIGHT);
		mlx->o.cy[cy_count].rgb = parse_rgb(&line);
		mlx->o.cy_count = ++cy_count;
	}
}

void	parse_line(t_mlx *mlx, char *line)
{
	if (ft_strncmp(line, "A", 1) == 0 || ft_strncmp(line, "L", 1) == 0)
		parse_lights(mlx, line);
	else if (ft_strncmp(line, "C", 1) == 0)
		parse_camera(mlx, line);
	else if (ft_strncmp(line, "pl", 2) == 0)
		parse_2d_objects(mlx, line);
	else if (ft_strncmp(line, "sp", 2) == 0 || ft_strncmp(line, "cy", 2) == 0)
		parse_3d_objects(mlx, line);
	else
		error_message_and_exit("unknown type identifier");
}
