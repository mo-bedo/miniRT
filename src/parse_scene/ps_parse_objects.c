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
	static int	pl_count = 0;

	line += 2;
	mlx->o.pl[pl_count].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->o.pl[pl_count].vector_orientation = parse_vector_orientation(&line);
	mlx->o.pl[pl_count].checkerboard = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->o.pl[pl_count].checkerboard = true;
		line += 12;
	}
	else
		mlx->o.pl[pl_count].color = parse_xyz(&line,
				MIN_COLOR, MAX_COLOR);
	mlx->o.pl[pl_count].specular = parse_float(&line,
			MIN_SPECULAR, MAX_SPECULAR);
	mlx->o.pl[pl_count].reflective = parse_float(&line,
			MIN_REFLECTIVE, MAX_REFLECTIVE);
	mlx->o.pl_count = ++pl_count;
}

void	parse_sphere(t_mlx *mlx, char *line)
{
	static int	sp_count = 0;

	line += 2;
	mlx->o.sp[sp_count].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->o.sp[sp_count].radius = parse_float(&line,
			MIN_DIAMETER, MAX_DIAMETER) / (float)2;
	mlx->o.sp[sp_count].checkerboard = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->o.sp[sp_count].checkerboard = true;
		line += 12;
	}
	else
		mlx->o.sp[sp_count].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->o.sp[sp_count].specular = parse_float(&line,
			MIN_SPECULAR, MAX_SPECULAR);
	mlx->o.sp[sp_count].reflective = parse_float(&line,
			MIN_REFLECTIVE, MAX_REFLECTIVE);
	mlx->o.sp_count = ++sp_count;
}

void	parse_cylinder(t_mlx *mlx, char *line)
{
	static int	cy_count = 0;

	line += 2;
	mlx->o.cy[cy_count].center = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
	mlx->o.cy[cy_count].vector_orientation = parse_vector_orientation(&line);
	mlx->o.cy[cy_count].radius = parse_float(&line,
			MIN_DIAMETER, MAX_DIAMETER) / (float)2;
	mlx->o.cy[cy_count].height = parse_float(&line,
			MIN_CY_HEIGHT, MAX_CY_HEIGHT);
	mlx->o.cy[cy_count].checkerboard = false;
	if (ft_strncmp(line, "checkerboard", 12) == 0)
	{
		mlx->o.cy[cy_count].checkerboard = true;
		line += 12;
	}
	else
		mlx->o.cy[cy_count].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->o.cy[cy_count].specular = parse_float(&line,
			MIN_SPECULAR, MAX_SPECULAR);
	mlx->o.cy[cy_count].reflective = parse_float(&line,
			MIN_REFLECTIVE, MAX_REFLECTIVE);
	mlx->o.cy_count = ++cy_count;
}
