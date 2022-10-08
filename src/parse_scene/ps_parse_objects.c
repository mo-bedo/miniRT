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
#include "ray_trace/rt_.h"

#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

#include "parse_scene/ps_utils.h"
#include "parse_scene/ps_.h"


int	ft_strlcpy(char *dst, char *src, int size)
{
	int	i;

	i = ft_strlen(src);
	if (!size)
		return (i);
	while (*src && --size)
		*dst++ = *src++;
	*dst = 0;
	return (i);
}

void	parse_ppm_data(t_map *map, char *line)
{
	if (ft_strncmp(line, "P3", 2) != 0)
		error_message_and_exit("Please provide P3 PPM file");
	// skip first line (P3)
	line += 3;
	map->width = ft_atoi(line);
	DEBUG_INT(map->width);
	while (*line && !ft_is_space(*line))
		line += 1;
	while (*line && ft_is_space(*line))
		line += 1;
	map->height = ft_atoi(line);
	while (*line && !ft_is_space(*line))
		line += 1;
	while (*line && ft_is_space(*line))
		line += 1;
	DEBUG_INT(map->height);
	// malloc space for map
	int k = 0;
	map->map = (t_xyz **)ft_calloc(map->height, sizeof(t_xyz**));
	while (k < map->height)
	{
		map->map[k] = (t_xyz *)ft_calloc(map->width, sizeof(t_xyz*));
		++k;
	}
	// skip third line (255)
	while (*line && !ft_is_space(*line))
		line += 1;
	while (*line && ft_is_space(*line))
		line += 1;
	// fill map
	int x = 0;
	while (x < map->height)
	{
		DEBUG_INT(x);
		// DEBUG_STR(line);
		int y = 0;
		while (y < map->width)
		{
			DEBUG_INT(y);
			while (*line && ft_is_space(*line) || *line == '\n')
				line += 1;
			DEBUG_STR("x");
			map->map[x][y].x = ft_atof(line);
			while (*line && !ft_is_space(*line))
				line += 1;
			while (*line && ft_is_space(*line) || *line == '\n')
				line += 1;
			DEBUG_STR("y");
			map->map[x][y].y = ft_atof(line);
			while (*line && !ft_is_space(*line))
				line += 1;
			while (*line && ft_is_space(*line) || *line == '\n')
				line += 1;
			DEBUG_STR("z");
			map->map[x][y].z = ft_atof(line);
			while (*line && !ft_is_space(*line))
				line += 1;
			while (*line && ft_is_space(*line) || *line == '\n')
				line += 1;
			DEBUG_DOUBLE(map->map[x][y].x);
			DEBUG_DOUBLE(map->map[x][y].y);
			DEBUG_DOUBLE(map->map[x][y].z);
			// if (y > 663)
			// 	DEBUG_STR(line);
			++y;
		}
		DEBUG_STR(line);
		++x;
	}
}

// void	read_entire_file(char **line, int fd)
// {
// 	char	buffer;
// 	int		return_value;

// 	*line[0] = 0;
// 	buffer = 0;
// 	return_value = 1;
// 	while (return_value)
// 	{
// 		return_value = read(fd, &buffer, 1);
// 		*line = add_buffer_to_line(*line, buffer);
// 	}
// }

int	get_length_of_file(char *path)
{
	char	buffer;
	int		i = 0;
	int		return_value;

	int fd = open(path, O_RDONLY);
	buffer = 0;
	return_value = 1;
	while (return_value)
	{
		return_value = read(fd, &buffer, 1);
		++i;
	}
	return (i);
}

void	parse_ppm(t_map *map, char *input)
{
	int		ppm_file;
	char	*path;
	char	*line;

	int i = 0;
	while (!ft_is_space(input[i]))
		++i;
	path = ft_calloc(++i, sizeof(char));
	ft_strlcpy(path, input, i);
	if (has_no_valid_extension(path, ".ppm"))
	{
		free(path);
		error_message_and_exit("Please provide a valid ppm file");
	}
	DEBUG_STR(path);
	int length = get_length_of_file(path);
	ppm_file = open(path, O_RDONLY);
	free(path);
	if (ppm_file < 0)
		error_message_and_exit("File does not exist");
	DEBUG_INT(length);
	line = (char *)ft_calloc(sizeof(char), length);
	// read(ppm_file, line, length);
	// read_entire_file(&line, ppm_file);
	// DEBUG_STR(line);
	parse_ppm_data(map, line);
	free(line);
}

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
	else
		mlx->object[i].color = parse_xyz(&line, MIN_COLOR, MAX_COLOR);
	mlx->object[i].specular = parse_float(&line, MIN_SPECULAR, MAX_SPECULAR);
	mlx->object[i].reflective = parse_float(&line, MIN_REFLECTIVE, MAX_REFLECTIVE);
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
	// if (ft_strncmp(line, "maps", 4) == 0)
	// {
	// 	parse_ppm(&mlx->object[i].texture_map, line);
	// 	while (*line && !ft_is_space(*line))
	// 		line += 1;
	// }
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
