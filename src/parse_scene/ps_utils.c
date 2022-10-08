/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 14:42:25 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/28 14:42:25 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "parse_scene/ps_utils.h"
#include "utils/u_.h"

void	error_message_and_exit(char *message)
{
	ft_putstr("\nError\n");
	ft_putstr(message);
	ft_putstr("\n\n");
	exit(EXIT_FAILURE);
}

static void	skip_chars_of_parsed_number(char **str)
{
	while (**str && ft_is_space(**str))
		*str += 1;
	while (**str && **str == '-')
		*str += 1;
	while (**str && ft_is_digit(**str))
		*str += 1;
	if (**str == '.')
	{
		*str += 1;
		while (**str && ft_is_digit(**str))
			*str += 1;
	}
	if (**str && **str == ',')
		*str += 1;
	if (**str && !ft_is_space(**str) && !ft_is_digit(**str) && **str != '-')
		error_message_and_exit("Input error");
	while (**str && ft_is_space(**str))
		*str += 1;
}

int	parse_int(char **str, int min, int max)
{
	int	number;

	number = ft_atoi(*str);
	// DEBUG_INT(number);
	if (number < min || number > max)
		error_message_and_exit("Integer value input error");
	skip_chars_of_parsed_number(str);
	return (number);
}

float	parse_float(char **str, int min, int max)
{
	float	number;

	number = ft_atof(*str);
	if (number < min || number > max)
		error_message_and_exit("Float value input error");
	skip_chars_of_parsed_number(str);
	// DEBUG_FLOAT(number);
	return (number);
}

t_xyz	parse_xyz(char **str, int min, int max)
{
	t_xyz	xyz;

	xyz.x = parse_float(str, min, max);
	xyz.y = parse_float(str, min, max);
	xyz.z = parse_float(str, min, max);
	return (xyz);
}

t_xyz	parse_vector_orientation(char **str)
{
	t_xyz	xyz;

	xyz.x = parse_float(str, MIN_3D, MAX_3D);
	xyz.y = parse_float(str, MIN_3D, MAX_3D);
	xyz.z = parse_float(str, MIN_3D, MAX_3D);
	if (xyz.x == 0 && xyz.y == 0 && xyz.z == 0)
		error_message_and_exit("Orientation vector cannot be 0,0,0");
	return (xyz);
}

bool	has_no_valid_extension(char *filename, char *valid_ext)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, valid_ext, ft_strlen(valid_ext)) != 0)
		return (true);
	return (false);
}

char	*add_buffer_to_line(char *old, char buffer)
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

int	get_next_line(char **line, int fd)
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
