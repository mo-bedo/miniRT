/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interaction.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/29 19:13:23 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "interaction.h"
#include "ray_trace.h"
#include "mlx.h"
#include "utils/utils.h"

// static void	scale_diameter(t_mlx *mlx, double scale)
// {
	// mlx->o.sp[0].radius = mlx->o.sp[0].radius * scale;
// }

int	mouse_hook(int keycode, int x, int y, t_mlx *mlx)
{
	// mlx->display_menu = -1;
	mlx_mouse_get_pos(mlx->window, &x, &y);
	if (keycode == MOUSE_CLICK)
	{
		// select object
		DEBUG_INT(x);
		DEBUG_INT(y);
	}
	// scrolling rezises object’s unique properties: 
	// diameter for a sphere and the width and height for a cylinder
	// if (keycode == SCROLL_UP)
		// scale_diameter(mlx, 0.90);
	// if (keycode == SCROLL_DOWN)
		// scale_diameter(mlx, 1.10);
	// ray_trace(mlx);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	// if (keycode == SPACEBAR)
	// 	mlx->display_menu *= -1;
	// else
	// 	mlx->display_menu = -1;
	// if (keycode == TAB)
	// 	mlx->colors.color_counter += 1;
	if (keycode == ESC)
		close_window(mlx);
	// ray_trace(mlx);
	return (0);
}
