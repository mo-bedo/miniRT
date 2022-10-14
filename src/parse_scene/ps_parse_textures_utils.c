/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_parse_textures_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:20:34 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "main.h"
#include "parse_scene/ps_.h"
#include "parse_scene/ps_utils.h"
#include "utils/u_.h"

// HOEZO MOET HEIGHT ZOVEEL GROTER ZIJN???
t_xyz	**allocate_map(int width, int height)
{
	t_xyz	**map;
	int		i;

	i = 0;
	map = (t_xyz **)ft_calloc(width, sizeof(t_xyz **));
	while (i < width)
		map[i++] = (t_xyz *)ft_calloc(height * 10, sizeof(t_xyz *));
	return (map);
}

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

int	get_length_of_file(char *path)
{
	char	buffer;
	int		i;
	int		return_value;
	int		fd;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_message_and_exit("File does not exist");
	buffer = 0;
	return_value = 1;
	while (return_value)
	{
		return_value = read(fd, &buffer, 1);
		++i;
	}
	return (i);
}
