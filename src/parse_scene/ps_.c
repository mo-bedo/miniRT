/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:58:22 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parse_scene/ps_parse_line.h"
#include "parse_scene/ps_utils.h"
#include "utils/u_vector_math.h"
#include "utils/u_.h"
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

static bool	has_no_valid_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".rt", 4) != 0)
		return (true);
	return (false);
}

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

static int	get_next_line(char **line, int fd)
{
	char	buffer;
	int		return_value;

	*line[0] = 0;
	buffer = 0;
	return_value = 1;
	while (return_value && buffer != '\n')
	{
		return_value = read(fd, &buffer, 1);
		*line = add_buffer_to_line(*line, buffer);
	}
	if (buffer == '\n')
		*line = add_buffer_to_line(*line, buffer);
	return (return_value);
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
	// else if (ft_strncmp(line, "L", 1) == 0)
		// l++;
	else
		total_objects++;
	if (a > 1 || l > 1)
		error_message_and_exit("Scene declares multiple lights");
	if (c > 1)
		error_message_and_exit("Scene declares multiple cameras");
	if (total_objects > MAX_OBJECTS)
		error_message_and_exit("Too many objects in scene");
}

void	parse_scene(t_mlx	*mlx, int argc, char *input)
{
	int		rt_file;
	int		there_is_a_new_line;
	char	*line;

	if (argc != 2 || has_no_valid_extension(input))
		error_message_and_exit("Please provide a scene description file");
	rt_file = open(input, O_RDONLY);
	if (rt_file < 0)
		error_message_and_exit("File does not exist");
	while (1)
	{
		line = (char *)ft_calloc(sizeof(char), 1);
		there_is_a_new_line = get_next_line(&line, rt_file);
		check_if_capital_elements_are_declared_multiple_times(line);
		parse_line(mlx, line);
		free(line);
		if (!there_is_a_new_line)
			return ;
	}
}
