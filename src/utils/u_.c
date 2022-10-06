/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:44:02 by mweitenb      ########   odam.nl         */
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
		write(1, s++, 1);
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

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		ptr[n] = c;
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (0);
	return (ft_memset(ret, 0, count * size));
}

void	initialize_empty_vector(t_xyz *vector)
{
	vector->x = 0;
	vector->y = 0;
	vector->z = 0;
}
