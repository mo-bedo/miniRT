/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_identify_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/11 13:23:24 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

bool	ft_is_digit(int c)
{
	if (c && c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	ft_is_space(char c)
{
	if (c && (c == ' ' || c == '\f' || c == '\n'
			|| c == '\r' || c == '\t' || c == '\v'))
		return (true);
	return (false);
}
