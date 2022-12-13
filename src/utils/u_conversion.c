/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_conversion_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 15:39:26 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/11 18:55:03 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <float.h>

#include "utils/u_bonus.h"
#include "parse_scene/ps_utils_bonus.h"

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
	float	nbr;
	float	i;

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
			nbr += (float)((*str++ - '0') / powf(10, i));
		}
	}
	if (i > 6 || nbr > FLT_MAX)
		error_message_and_exit("float overflow");
	nbr *= polarity;
	return ((float)nbr);
}

t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera, int x, int y)
{
	t_xyz	vector;
	t_xyz	orientation;

	initialize_vector(&vector, x, y, camera.canvas_distance);
	initialize_vector(&orientation, 0, 0, 1);
	if (camera.orientation.x == 0
		&& camera.orientation.y == 0
		&& camera.orientation.z == -1)
	{
		vector.z *= -1;
		camera.orientation.z *= -1;
	}
	return (rotate_vector(vector, camera.orientation, orientation));
}
