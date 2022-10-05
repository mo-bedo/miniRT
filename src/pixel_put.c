/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel_put.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:15:34 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "utils/u_.h"

// Clamps a color to the canonical color range.
static int	create_color(int transparancy, int red, int green, int blue)
{
	return (transparancy << 24 | red << 16 | green << 8 | blue);
}

static int	clamp_color(t_xyz rgb)
{
	int	r;
	int	g;
	int	b;

	r = (int)ft_min_float(255, ft_max_float(0, rgb.x));
	g = (int)ft_min_float(255, ft_max_float(0, rgb.y));
	b = (int)ft_min_float(255, ft_max_float(0, rgb.z));
	return (create_color(1, r, g, b));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, t_xyz color)
{
	char	*dst;
	int		offset;

	x = WINDOW_WIDTH / 2 + x;
	y = WINDOW_HEIGHT / 2 - y - 1;
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = &img->addr[offset];
	*(unsigned int *)dst = clamp_color(color);
}
