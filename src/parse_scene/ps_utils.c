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
}

int	parse_int(char **str, int min, int max)
{
	int	number;

	number = ft_atoi(*str);
	if (number < min || number > max)
		error_message_and_exit("Integer input error");
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
