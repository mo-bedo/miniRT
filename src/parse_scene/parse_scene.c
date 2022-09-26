/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:39:26 by mweitenb          #+#    #+#             */
/*   Updated: 2022/09/23 18:10:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/parse_scene_utils.h"
#include "utils.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static char	*add_buffer_to_line(char *old, char buffer)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (old[len])
		len++;
	new = (char *)ft_calloc(sizeof(char), (len + 2));
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	new[i++] = buffer;
	new[i] = 0;
	free(old);
	return (new);
}

static char	*get_next_line(int fd)
{
	char	buffer;
	char	*line;

	line = (char *)ft_calloc(sizeof(char), 1);
	line[0] = 0;
	while (read(fd, &buffer, 1) && buffer != '\n')
		line = add_buffer_to_line(line, buffer);
	// if (buffer == '\n')
		// line = add_buffer_to_line(line, '\n');
	return (line);
}

static void	check_if_capital_elements_are_declared_multiple_times(char *input)
{
	static int	a = 0;
	static int	c = 0;
	static int	l = 0;
	static int	total_objects = 0;

	if (ft_strncmp(input, "A", 1) == 0)
		a++;
	else if (ft_strncmp(input, "C", 1) == 0)
		c++;
	else if (ft_strncmp(input, "L", 1) == 0)
		l++;
	else
		total_objects++;
	if (a > 1 || c > 1 || l > 1)
		error_message_and_exit("Scene file declares multiple elements that are defined by a capital letter");	
	if (total_objects > MAX_OBJECTS)
		error_message_and_exit("Too many objects in scene");	
}

void	parse_line(t_mlx	*mlx, char *input)
{
	if (ft_strncmp(input, "A", 1) == 0)
	{
		input++;
		mlx->d.a.lighting_ratio = parse_float(&input, MIN_LiGHTING_RATIO, MAX_LiGHTING_RATIO);
		mlx->d.a.rgb = parse_rgb(&input);
	}
	else if (ft_strncmp(input, "C", 1) == 0)
	{
		input++;
		mlx->d.c.xyz = parse_xyz(&input, MIN_XYZ, MAX_XYZ);
		mlx->d.c.vector_orientation = parse_xyz(&input, MIN_3D, MAX_3D);
		mlx->d.c.field_of_view = parse_int(&input, 0, 180);
	}
	else if (ft_strncmp(input, "L", 1) == 0)
	{
		input++;
		mlx->d.l.xyz = parse_xyz(&input, MIN_XYZ, MAX_XYZ);
		mlx->d.l.brightness = parse_float(&input, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	}
	else if (ft_strncmp(input, "sp", 2) == 0)
	{
		static int sp_count = 0;
		input += 2;
		mlx->d.o.sp[sp_count].centre = parse_xyz(&input, MIN_XYZ, MAX_XYZ);
		mlx->d.o.sp[sp_count].radius = parse_float(&input, MIN_DIAMETER, MAX_DIAMETER) / (float)2; // check if this works
		mlx->d.o.sp[sp_count].rgb = parse_rgb(&input);
		mlx->d.o.sp_count = sp_count++;
	}
	else if (ft_strncmp(input, "pl", 2) == 0)
	{
		static int pl_count = 0;
		input += 2;
		mlx->d.o.pl[pl_count].xyz = parse_xyz(&input, MIN_XYZ, MAX_XYZ);
		mlx->d.o.pl[pl_count].vector_orientation = parse_xyz(&input, MIN_3D, MAX_3D);
		mlx->d.o.pl[pl_count].rgb = parse_rgb(&input);
		mlx->d.o.pl_count = pl_count++;
	}
	else if (ft_strncmp(input, "cy", 2) == 0)
	{
		static int cy_count = 0;
		input += 2;
		mlx->d.o.cy[cy_count].xyz = parse_xyz(&input, MIN_XYZ, MAX_XYZ);
		mlx->d.o.cy[cy_count].vector_orientation = parse_xyz(&input, MIN_3D, MAX_3D);
		mlx->d.o.cy[cy_count].diameter = parse_float(&input, MIN_DIAMETER, MAX_DIAMETER);
		mlx->d.o.cy[cy_count].height = parse_float(&input, MIN_CY_HEIGHT, MAX_CY_HEIGHT);
		mlx->d.o.cy[cy_count].rgb = parse_rgb(&input);
		mlx->d.o.cy_count = cy_count++;
	}
	else
		error_message_and_exit("unknown type identifier");
}


// BUG		: als scene.rt eindigt op \n -> neverending loop
void	parse_scene(t_mlx	*mlx, char *input)
{
	int		rt_file = open(input, O_RDONLY);
	char	*line;

	while (1)
	{
		line = get_next_line(rt_file);
		if (!line || !line[0])
		{
			free(line);
			return ;
		}
		if (ft_strncmp(line, "\n", 1) != 0)
		{
			check_if_capital_elements_are_declared_multiple_times(input);
			parse_line(mlx, line);
		}
		free(line);
	}
}
