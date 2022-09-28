/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/28 13:03:07 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/parse_scene_utils.h"
#include "vector_math.h"
#include "utils.h"
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
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
	return (line);
}

static void	check_if_capital_elements_are_declared_multiple_times(char *line)
{
	static int	a = 0;
	static int	c = 0;
	static int	l = 0;
	static int	total_objects = 0;

	if (ft_strncmp(line, "A", 1) == 0)
		a++;
	else if (ft_strncmp(line, "C", 1) == 0)
		c++;
	else if (ft_strncmp(line, "L", 1) == 0)
		l++;
	else
		total_objects++;
	if (a > 1 || c > 1 || l > 1)
		error_message_and_exit("Scene file declares multiple elements that are defined by a capital letter");	
	if (total_objects > MAX_OBJECTS)
		error_message_and_exit("Too many objects in scene");
}

void	parse_line(t_mlx	*mlx, char *line)
{
	if (ft_strncmp(line, "A", 1) == 0)
	{
		line++;
		mlx->a.lighting_ratio = parse_float(&line, MIN_LIGHTING_RATIO, MAX_LIGHTING_RATIO);
		mlx->a.rgb = parse_rgb(&line);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
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
		field_of_view = parse_int(&line, 0, 180); // / 2;
		mlx->camera.forward = normalize_vector(substract_vectors(vector_orientation, upguide));
		mlx->camera.right = normalize_vector(get_cross_product(mlx->camera.forward, upguide));
		mlx->camera.up = get_cross_product(mlx->camera.right, mlx->camera.forward);
		mlx->camera.height = tan(field_of_view);
		mlx->camera.width = mlx->camera.height * mlx->aspect_ratio;
	}
	else if (ft_strncmp(line, "L", 1) == 0)
	{
		line++;
		mlx->l.xyz = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->l.brightness = parse_float(&line, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	}
	else if (ft_strncmp(line, "sp", 2) == 0)
	{
		static int sp_count = 0;
		line += 2;
		mlx->o.sp[sp_count].centre = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->o.sp[sp_count].radius = parse_float(&line, MIN_DIAMETER, MAX_DIAMETER) / (float)2;
		mlx->o.sp[sp_count].rgb = parse_rgb(&line);
		mlx->o.sp_count = ++sp_count;
	}
	else if (ft_strncmp(line, "pl", 2) == 0)
	{
		static int pl_count = 0;
		line += 2;
		mlx->o.pl[pl_count].xyz = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->o.pl[pl_count].vector_orientation = parse_xyz(&line, MIN_3D, MAX_3D);
		mlx->o.pl[pl_count].rgb = parse_rgb(&line);
		mlx->o.pl_count = ++pl_count;
	}
	else if (ft_strncmp(line, "cy", 2) == 0)
	{
		static int cy_count = 0;

		line += 2;
		mlx->o.cy[cy_count].xyz = parse_xyz(&line, MIN_XYZ, MAX_XYZ);
		mlx->o.cy[cy_count].vector_orientation = parse_xyz(&line, MIN_3D, MAX_3D);
		mlx->o.cy[cy_count].diameter = parse_float(&line, MIN_DIAMETER, MAX_DIAMETER);
		mlx->o.cy[cy_count].height = parse_float(&line, MIN_CY_HEIGHT, MAX_CY_HEIGHT);
		mlx->o.cy[cy_count].rgb = parse_rgb(&line);
		mlx->o.cy_count = ++cy_count;
	}
	else
		error_message_and_exit("unknown type identifier");
}


// BUG		: als scene.rt eindigt op \n -> neverending loop
// TO DO: check of bestand echt bestaat, anders foutmeldingr
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
			check_if_capital_elements_are_declared_multiple_times(line);
			parse_line(mlx, line);
		}
		free(line);
	}
}
