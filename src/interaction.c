/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interaction.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/28 17:56:46 by mweitenb      ########   odam.nl         */
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

// static void	move_arrows(int keycode, t_mlx *mlx)
// {
// 	int	move_speed;

// 	move_speed = 25;
// 	if (keycode == LEFT)
// 		mlx->c.center_x = mlx->c.center_x + move_speed * mlx->c.size_of_pixel;
// 	if (keycode == RIGHT)
// 		mlx->c.center_x = mlx->c.center_x - move_speed * mlx->c.size_of_pixel;
// 	if (keycode == DOWN)
// 		mlx->c.center_y = mlx->c.center_y - move_speed * mlx->c.size_of_pixel;
// 	if (keycode == UP)
// 		mlx->c.center_y = mlx->c.center_y + move_speed * mlx->c.size_of_pixel;
// }

int	key_hook(int keycode, t_mlx *mlx)
{
	// if (keycode == SPACEBAR)
	// 	mlx->display_menu *= -1;
	// else
	// 	mlx->display_menu = -1;
	// move_arrows(keycode, mlx);
	// if (keycode == TAB)
	// 	mlx->colors.color_counter += 1;
	// if (keycode == PLUS && mlx->max_iterations < 100)
	// 	mlx->max_iterations += 5;
	// if (keycode == MINUS && mlx->max_iterations > 6)
	// 	mlx->max_iterations -= 5;
	// if (keycode == ONE)
	// 	mlx->fractol_name = 1;
	// if (keycode == TWO)
	// 	mlx->fractol_name = 2;
	// if (keycode == THREE)
	// 	mlx->fractol_name = 3;
	// if (keycode == FOUR)
	// 	mlx->fractol_name = 4;
	// if (keycode == ZERO || (keycode >= ONE && keycode <= FOUR))
	// 	init_data(mlx);
	if (keycode == ESC)
		close_window(mlx);
	// ray_trace(mlx);
	return (0);
}
