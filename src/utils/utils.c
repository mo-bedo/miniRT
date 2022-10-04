/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 16:07:28 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		if (!write(1, s++, 1))
			return ; 			// error msg?
	}
}

void	error_message_and_exit(char *message)
{
	ft_putstr("\nError\n");
	ft_putstr(message);
	ft_putstr("\n\n");
	exit(EXIT_FAILURE);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	exit(EXIT_SUCCESS);
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

// mag memset?
void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (0);
	return (memset(ret, 0, count * size));
}

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

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}

double	get_smallest_double(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_min_float(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_max_float(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}
