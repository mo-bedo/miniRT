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
#include "parse_scene/ps_utils.h"
#include "utils/u_vector_math.h"
#include "utils/u_.h"
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

void	parse_plane(t_mlx *mlx, char *line)
{
	static int	i = 0;

	line += 2;
	mlx->o.pl[i].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->o.pl[i].vector_orientation = parse_vector_orientation(&line);
	mlx->o.pl[i].checkerboard = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->o.pl[i].checkerboard = true;
		line += 12;
	}
	else
		mlx->o.pl[i].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->o.pl[i].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->o.pl[i].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
	DEBUG_FLOAT(mlx->o.pl[i].specular);
	mlx->o.pl_count = ++i;
}

void	parse_sphere(t_mlx *mlx, char *line)
{
	static int	i = 0;

	line += 2;
	mlx->o.sp[i].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->o.sp[i].radius = parse_float(&line, MIN_DIAMETER, MAX_DIAMETER) / 2;
	mlx->o.sp[i].checkerboard = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->o.sp[i].checkerboard = true;
		line += 12;
	}
	else
		mlx->o.sp[i].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->o.sp[i].specular = 0;
	mlx->o.sp[i].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->o.sp[i].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
	mlx->o.sp_count = ++i;
}

void	parse_cylinder(t_mlx *mlx, char *line)
{
	static int	i = 0;

	line += 2;
	mlx->o.cy[i].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->o.cy[i].vector_orientation = parse_vector_orientation(&line);
	mlx->o.cy[i].radius = parse_float(&line, MIN_DIAMETER, MAX_DIAMETER) / 2;
	mlx->o.cy[i].height = parse_float(&line, MIN_CY_HEIGHT, MAX_CY_HEIGHT);
	mlx->o.cy[i].checkerboard = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->o.cy[i].checkerboard = true;
		line += 12;
	}
	else
		mlx->o.cy[i].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->o.cy[i].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->o.cy[i].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
	mlx->o.cy_count = ++i;
}
