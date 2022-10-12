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
#include "utils/u_vector_math.h"

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

t_xyz	parse_orientation(char **str)
{
	t_xyz	xyz;

	xyz.x = parse_float(str, MIN_3D, MAX_3D);
	xyz.y = parse_float(str, MIN_3D, MAX_3D);
	xyz.z = parse_float(str, MIN_3D, MAX_3D);
	if (xyz.x == 0 && xyz.y == 0 && xyz.z == 0)
		error_message_and_exit("Orientation vector cannot be 0,0,0");
	if (xyz.x == 1 && xyz.y == 1 && xyz.z == 1)
		error_message_and_exit("Orientation vector cannot be 1,1,1");
	return (xyz);
}

bool	has_valid_extension(char *filename, char *valid_ext)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || !str_is_equal(ext, valid_ext, ft_strlen(valid_ext)))
		return (false);
	return (true);
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

int	get_length_of_file(char *path)
{
	char	buffer;
	int		i = 0;
	int		return_value;

	int fd = open(path, O_RDONLY);
	if (fd < 0)
		error_message_and_exit("File does not exist");
	buffer = 0;
	return_value = 1;
	while (return_value)
	{
		return_value = read(fd, &buffer, 1);
		// DEBUG_INT(i);
		++i;
	}
	return (i);
}

t_xyz	get_angle_over_the_axes(t_xyz vector1, t_xyz vector2)
{
	t_xyz	angles;
	t_xyz	v1;
	t_xyz	v2;

	v1 = vector1;
	v1.x = 0;
	v2 = vector2;
	v2.x = 0;
	angles.x = get_angle_between_vectors(v1, v2);
	if ((v2.z >= 0 && v1.y < v2.y) || (v2.z < 0 && v1.y > v2.y))
		angles.x *= -1;
	v1 = vector1;
	v1.y = 0;
	v2 = vector2;
	v2.y = 0;
	angles.y = get_angle_between_vectors(v1, v2);
	if ((v2.z >= 0 && v1.x > v2.x) || (v2.z < 0 && v1.x < v2.x))
		angles.y *= -1;
	angles.z = 0;
	if (v2.z < 0)
	{
		angles.y -= (180 * (3.14 / 180));
		angles.z -= -180 * (3.14 / 180);
	}
	return (angles);
}