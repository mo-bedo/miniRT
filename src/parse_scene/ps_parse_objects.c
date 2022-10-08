/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_parse_objects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:38:33 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/ps_parse_map.h"
#include "parse_scene/ps_utils.h"
#include "utils/u_vector_math.h"
#include "utils/u_.h"
#include "ray_trace/rt_.h"

#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

#include "parse_scene/ps_utils.h"
#include "parse_scene/ps_.h"

void	parse_plane(t_mlx *mlx, char *line)
{
	int	i;

	i = mlx->object_count;
	line += 2;
	mlx->object[i].type = PLANE;
	mlx->object[i].t = RAY_T_MAX;
	mlx->object[i].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->object[i].vector_orientation = parse_vector_orientation(&line);
	mlx->object[i].checkerboard = false;
	mlx->object[i].image = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->object[i].checkerboard = true;
		line += 12;
	}
	else if (ft_strncmp(line, "image", 5) == 0)
	{
		mlx->object[i].image = true;
		line += 5;
	}
	else
		mlx->object[i].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->object[i].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->object[i].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
	if (ft_strncmp(line, "maps", 4) == 0)
	{
		parse_map(&mlx->object[i].texture_map, line);
		while (*line && !ft_is_space(*line))
			line += 1;
	}
	mlx->object_count += 1;
}

void	parse_sphere(t_mlx *mlx, char *line)
{
	int	i;

	i = mlx->object_count;
	line += 2;
	mlx->object[i].type = SPHERE;
	mlx->object[i].t = RAY_T_MAX;
	mlx->object[i].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->object[i].radius = parse_float(&line, MIN_DIAMETER, MAX_DIAMETER) / 2;
	mlx->object[i].checkerboard = false;
	mlx->object[i].image = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->object[i].checkerboard = true;
		line += 12;
	}
	else if (ft_strncmp(line, "image", 5) == 0)
	{
		mlx->object[i].image = true;
		line += 5;
	}
	else
		mlx->object[i].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->object[i].specular = 0;
	mlx->object[i].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->object[i].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
	if (ft_strncmp(line, "maps", 4) == 0)
	{
		parse_map(&mlx->object[i].texture_map, line);
		while (*line && !ft_is_space(*line))
			line += 1;
	}
	mlx->object_count += 1;
}

void	parse_cylinder(t_mlx *mlx, char *line)
{
	int	i;

	i = mlx->object_count;
	line += 2;
	mlx->object[i].type = PLANE;
	mlx->object[i].t = RAY_T_MAX;
	mlx->object[i].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->object[i].vector_orientation = parse_vector_orientation(&line);
	mlx->object[i].radius = parse_float(&line, MIN_DIAMETER, MAX_DIAMETER) / 2;
	mlx->object[i].height = parse_float(&line, MIN_CY_HEIGHT, MAX_CY_HEIGHT);
	mlx->object[i].checkerboard = false;
	mlx->object[i].image = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->object[i].checkerboard = true;
		line += 12;
	}
	else
		mlx->object[i].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->object[i].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->object[i].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
	mlx->object_count += 1;
}
