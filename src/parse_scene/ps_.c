/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:39:26 by mweitenb          #+#    #+#             */
/*   Updated: 2022/10/03 13:16:22 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/ps_parse_line.h"
#include "parse_scene/ps_utils.h"
#include "utils/vector_math.h"
#include "utils/utils.h"
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
	if (a > 1 || l > 1)
		error_message_and_exit("Scene declares multiple lights");
	if (c > 1)
		error_message_and_exit("Scene declares multiple cameras");
	if (total_objects > MAX_OBJECTS)
		error_message_and_exit("Too many objects in scene");
}

// BUG		: als scene.rt eindigt op \n -> neverending loop
void	parse_scene(t_mlx	*mlx, char *input)
{
	int		rt_file;
	char	*line;

	mlx->o.pl_count = 0;
	mlx->o.sp_count = 0;
	mlx->o.cy_count = 0;
	rt_file = open(input, O_RDONLY);
	if (rt_file < 0)
		error_message_and_exit("file does not exist");
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
