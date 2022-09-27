/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/21 18:04:28 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	while (*s)
		write(1, s++, 1);
}

void	error_message_and_exit(char *message)
{
	ft_putstr("\nError\n");
	ft_putstr(message);
	ft_putstr("\n\n");
	exit(EXIT_FAILURE);
}

int	ft_isdigit(int c)
{
	if (c && c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_char_to_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	return (-1);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		polarity;
	long	nbr;

	polarity = 1;
	nbr = 0;
	while (is_space(*str))
		str++;
	if (*str == '-')
		polarity *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str++ - '0';
	}
	nbr *= polarity;
	return ((int)nbr);
}

// mag memset?
void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (0);
	return (memset(ret, 0, count * size));
}