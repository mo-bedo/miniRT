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

t_xyz	**allocate_map(int width, int height)
{
	t_xyz	**map;
	int		i;

	i = 0;
	map = (t_xyz **)ft_calloc(width, sizeof(t_xyz**));
	// HOEZO MOET HEIGHT ZOVEEL GROTER ZIJN?
	while (i < width)
		map[i++] = (t_xyz *)ft_calloc(height * 10, sizeof(t_xyz*));
	return (map);
}

void	parse_map_data(t_map *map, char *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
			map->map[x][y++] = parse_xyz(&data, MIN_COLOR, MAX_COLOR);
		++x;
	}
}

void	parse_ppm_data(t_map *map, char *data)
{
	int	color_scale;

	if (ft_strncmp(data, "P3", 2) != 0)
		error_message_and_exit("PPM: Please provide P3 file");
	data += 3;
	map->width = parse_int(&data, MIN_PPM_SIZE, MAX_PPM_SIZE);
	map->height = parse_int(&data, MIN_PPM_SIZE, MAX_PPM_SIZE);
	map->map = allocate_map(map->width, map->height);
	color_scale = parse_int(&data, MIN_PPM_SIZE, MAX_PPM_SIZE);
	if (color_scale != MAX_COLOR)
		error_message_and_exit("PPM: Max color scale should be 255");
	parse_map_data(map, data);
}

char	*get_path(char *input)
{
	char	*path;
	int		i;

	i = 0;
	while (!ft_is_space(input[i]))
		++i;
	path = ft_calloc(++i, sizeof(char));
	ft_strlcpy(path, input, i);
	if (has_valid_extension(path, ".ppm"))
		return (path);
	free(path);
	error_message_and_exit("Please provide a valid ppm file");
	return (NULL);
}

void	parse_map(t_map *map, char *input)
{
	int		ppm_file;
	int		file_length;
	char	*path;
	char	*map_data;

	path = get_path(input);
	file_length = get_length_of_file(path);
	ppm_file = open(path, O_RDONLY);
	free(path);
	if (ppm_file < 0)
		error_message_and_exit("File does not exist");
	map_data = (char *)ft_calloc(sizeof(char), file_length);
	if (read(ppm_file, map_data, file_length) != -1);
		parse_ppm_data(map, map_data);
	free(map_data);
}
