/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:26:51 by mweitenb      ########   odam.nl         */
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
		return (0);
	return (ft_memset(ret, 0, count * size));
}

t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera, int x, int y)
{
	t_xyz	vector;
	t_xyz	orientation;

	initialize_vector(&vector, x, y, camera.canvas_distance);
	initialize_vector(&orientation, 0, 0, 1);
	return (rotate_vector(vector, camera.orientation, orientation));
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
