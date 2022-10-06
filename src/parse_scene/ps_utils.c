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

#include "parse_scene/ps_utils.h"
#include "utils/u_.h"
#include <stdlib.h>

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
	while (**str && ft_is_space(**str))
		*str += 1;
}

float	parse_float(char **str, int min, int max)
{
	float	number;

	number = ft_atof(*str);
	if (number < min || number > max)
		error_message_and_exit("Float value input error");
	skip_chars_of_parsed_number(str);
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
