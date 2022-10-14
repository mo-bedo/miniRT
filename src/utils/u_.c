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
#include "utils/u_rotate_vector.h"

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

void	initialize_vector(t_xyz *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera, int x, int y)
{
	t_xyz	vector;

	vector.x = x;
	vector.y = y;
	vector.z = camera.canvas_distance;
	return (rotate_vector(vector, camera.rotation_angles));
}
