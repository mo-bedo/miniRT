/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:11:23 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "main.h"
#include "parse_scene/ps_parse_line.h"
#include "utils/u_.h"

bool	has_valid_extension(char *filename, char *valid_ext)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || !str_is_equal(ext, valid_ext, ft_strlen(valid_ext)))
		return (false);
	return (true);
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

	if (str_is_equal(line, "A", 1))
		a++;
	else if (str_is_equal(line, "C", 1))
		c++;
	else if (str_is_equal(line, "L", 1))
		l++;
	if (a > 1 || l > 1)
		error_message_and_exit("Scene declares multiple lights");
	if (c > 1)
		error_message_and_exit("Scene declares multiple cameras");
}

void	parse_scene(t_mlx *mlx, int argc, char *input)
{
	int		rt_file;
	int		there_is_a_new_line;
	char	*line;

	if (argc != 2 || !has_valid_extension(input, ".rt"))
		error_message_and_exit("Please provide a scene description file");
	rt_file = open(input, O_RDONLY);
	if (rt_file < 0)
		error_message_and_exit(
			"File does not exist or the user doesn't have reading rights");
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
