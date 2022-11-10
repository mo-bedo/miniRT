/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/09 19:01:26 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "utils/u_.h"

void	ft_putstr(char *s)
{
	int	return_value;

	if (!s)
		return ;
	while (*s)
		return_value = write(1, s++, 1);
	return_value++;
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
		error_message_and_exit("Malloc failure in ft_calloc");
	return (ft_memset(ret, 0, count * size));
}

void	initialize_quaternion(t_wxyz *q, float w, t_xyz vector)
{
	q->w = w;
	q->x = vector.x;
	q->y = vector.y;
	q->z = vector.z;
}

t_wxyz	multiply_quaternion(t_wxyz q1, t_wxyz q2)
{
	t_wxyz	result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w - q1.y * q2.z + q1.z * q2.y;
	result.y = q1.w * q2.y + q1.x * q2.z + q1.y * q2.w - q1.z * q2.x;
	result.z = q1.w * q2.z - q1.x * q2.y + q1.y * q2.x + q1.z * q2.w;
	return (result);
}
