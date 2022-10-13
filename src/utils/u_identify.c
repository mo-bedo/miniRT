/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_identify.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:25:03 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

int	ft_is_digit(int c)
{
	if (c && c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_space(char c)
{
	if (c && (c == ' ' || c == '\f' || c == '\n'
			|| c == '\r' || c == '\t' || c == '\v'))
		return (1);
	return (0);
}
