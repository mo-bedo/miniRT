/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interaction.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 21:07:02 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "interaction.h"
#include "ray_trace/rt_.h"
#include "mlx.h"
#include "utils/u_.h"

#include <stdlib.h>

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	exit(EXIT_SUCCESS);
}

// int	mouse_hook(int keycode, int x, int y, t_mlx *mlx)
// {
// 	t_xyz	direction;
// 	t_ray	ray;

// 	mlx_mouse_get_pos(mlx->window, &x, &y);
// 	if (keycode == MOUSE_CLICK)
// 	{
// 		DEBUG_INT(x - (WINDOW_WIDTH / 2));
// 		DEBUG_INT(y - (WINDOW_HEIGHT / 2));
// 		direction = convert_2d_canvas_to_3d_coordinates(mlx->camera,
// 				x - (WINDOW_WIDTH / 2), y - (WINDOW_HEIGHT / 2));
// 		ray = compute_ray(mlx->o, mlx->camera.center, direction);
// 		if (ray.object.object != NONE)
// 		{
// 			DEBUG_INT(ray.object.object);
// 		}
// 		else
// 			ft_putstr("Select an object\n");
// 	}
// 	// ray_trace(mlx);
// 	return (0);
// }

int	key_hook(int keycode, t_mlx *mlx)
{
	double	rotation_speed;

	rotation_speed = 0.20;
	if (keycode == LEFT)
		mlx->camera.rotation_angles.y -= rotation_speed;
	if (keycode == RIGHT)
		mlx->camera.rotation_angles.y += rotation_speed;
	if (keycode == DOWN)
		mlx->camera.rotation_angles.x += rotation_speed;
	if (keycode == UP)
		mlx->camera.rotation_angles.x -= rotation_speed;
	DEBUG_INT(keycode);
	if (keycode == ESC)
		close_window(mlx);
	ray_trace(mlx);
	return (0);
}

void	interaction(t_mlx *mlx)
{
	mlx_hook(mlx->window, 17, 0, close_window, mlx);
	// mlx_mouse_hook(mlx->window, mouse_hook, mlx);
	mlx_key_hook(mlx->window, key_hook, mlx);
}
