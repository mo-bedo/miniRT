/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/21 18:51:20 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "main.h"
#include "utils.h"
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

int	check_if_ratio(char *str)
{
	// DEBUG_STR(str);
	while (is_space(*str))
		str++;
	if (str[1] == '.')
	{
		if (str[0] == '0' && ft_char_to_digit(str[2]) != -1)
			return (ft_char_to_digit(str[2]));
		if (str[0] == '1' && str[2] == '0')
			return (10);
	}
	error_message_and_exit("ratio input error");
	return (0);
}

int	check_correct_rgb_values(char *str)
{
	int	number;

	while (is_space(*str))
		str++;
	number = ft_atoi(str);
	if (number < 0 || number > 255)
		error_message_and_exit("rgb input error");
	// DEBUG_INT(number);
	return (number);
}

int	chars_until_next_value(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',')
		error_message_and_exit("rgb or xyz input error");
	return (i + 1);
}

// static int	create_color(int transparancy, int red, int green, int blue)
// {
// 	return (transparancy << 24 | red << 16 | green << 8 | blue);
// }

// mogelijk optie om rgb meteen naar 1 int te parsen (zie functie create_color hierboven)
// dan kan de struct t_rgb weg.
t_rgb	parse_rgb(char *str)
{
	t_rgb	rgb;

	// DEBUG_STR(str);
	while (is_space(*str))
		str++;
	rgb.red = check_correct_rgb_values(str);
	str += chars_until_next_value(str);
	rgb.green = check_correct_rgb_values(str);
	str += chars_until_next_value(str);
	rgb.blue = check_correct_rgb_values(str);
	while (ft_isdigit(*str))
		str++;
	if ((*str && *str != '\n'))
		error_message_and_exit("rgb input error");
	return (rgb);
}


void	check_if_capital_elements_are_declared_multiple_times(char *input)
{
	static int	a = 0;
	static int	c = 0;
	static int	l = 0;

	if (ft_strncmp(input, "A", 1) == 0)
		a++;
	if (ft_strncmp(input, "C", 1) == 0)
		c++;
	if (ft_strncmp(input, "L", 1) == 0)
		l++;
	if (a > 1 || c > 1 || l > 1)
		error_message_and_exit("Scene file declares multiple elements that are defined by a capital letter");	
}

void	parse_input(t_mlx	*mlx, char *input)
{
	// DEBUG_STR(input);
	if (!input[0])
		exit(EXIT_SUCCESS);
	if (ft_strncmp(input, "\n", 1) == 0)
		return ;
	else if (ft_strncmp(input, "A", 1) == 0)
	{
		check_if_capital_elements_are_declared_multiple_times(input);
		input++;
		mlx->d.a.lighting_ratio = check_if_ratio(input);
		DEBUG_INT(mlx->d.a.lighting_ratio);
		while (*input != '.')
			input++;
		input += 2;
		mlx->d.a.rgb = parse_rgb(input);
		DEBUG_INT(mlx->d.a.rgb.red);
		DEBUG_INT(mlx->d.a.rgb.green);
		DEBUG_INT(mlx->d.a.rgb.blue);
	}
	else if (ft_strncmp(input, "C", 1) == 0)
	{
		check_if_capital_elements_are_declared_multiple_times(input);
		input++;
		// mlx->d.c.xyz = parse_xyz(input);
	}
	else if (ft_strncmp(input, "L", 1) == 0)
	{
		check_if_capital_elements_are_declared_multiple_times(input);
		input++;
	}
	else if (ft_strncmp(input, "pl", 2) == 0)
	{
		input++;
	}
	else if (ft_strncmp(input, "sp", 2) == 0)
	{
		input++;
	}
	else if (ft_strncmp(input, "cy", 2) == 0)
	{
		input++;
	}
	else
		error_message_and_exit("unknown type identifier");
}
