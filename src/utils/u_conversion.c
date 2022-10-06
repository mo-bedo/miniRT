/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_conversion.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/28 15:05:46 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/u_.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int	ft_char_to_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	return (-1);
}

static int	get_polarity_and_skip_to_start_no(const char **str)
{
	int	polarity;

	polarity = 1;
	while (ft_is_space(**str))
		*str += 1;
	if (**str == '-')
		polarity *= -1;
	if (**str == '+' || **str == '-')
		*str += 1;
	return (polarity);
}

int	ft_atoi(const char *str)
{
	int		polarity;
	long	nbr;

	nbr = 0;
	polarity = get_polarity_and_skip_to_start_no(&str);
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str++ - '0';
	}
	nbr *= polarity;
	return ((int)nbr);
}

float	ft_atof(const char *str)
{
	int		polarity;
	double	nbr;
	double	i;

	nbr = 0;
	i = 0;
	polarity = get_polarity_and_skip_to_start_no(&str);
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str++ - '0';
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			i++;
			nbr += (double)((*str - '0') / pow(10, i));
			str++;
		}
	}
	nbr *= polarity;
	return ((float)nbr);
}
