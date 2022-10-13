/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 16:27:08 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "user_input/ui_.h"
#include "user_input/ui_adjust_object.h"
#include "ray_trace/rt_.h"
#include "mlx.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

#include <stdlib.h>

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	exit(EXIT_SUCCESS);
}

static int	mouse_hook(int keycode, int x, int y, t_mlx *mlx)
{
	t_ray	ray;
	int		prev_id;
	t_xyz	selection_color;

	initialize_vector(&selection_color, 100, 100, 100);
	if (keycode != MOUSE_CLICK)
		return (0);
	ray = compute_ray(*mlx, mlx->camera.center,
			convert_2d_canvas_to_3d_coordinates(mlx->camera,
				x - (WINDOW_WIDTH / 2), y - (WINDOW_HEIGHT / 2)));
	prev_id = mlx->selected_object;
	if (mlx->selected_object >= 0)
		mlx->object[prev_id].color = substract_vectors(
				mlx->object[prev_id].color, selection_color);
	if (ray.object.type != NONE)
	{
		ft_putstr("\e[1;1H\e[2J");
		ft_putstr("Press the following keys to select an action\n");
		ft_putstr("D\t: Adjust the diameter\n");
		if (ray.object.type == CYLINDER || ray.object.type == CONE)
			ft_putstr("H\t: Adjust the height\n");
		if (ray.object.type == CYLINDER || ray.object.type == CONE)
			ft_putstr("R\t: Rotate the object\n");
		ft_putstr("S\t: Scale the object\n");
		mlx->selected_object = ray.object.id;
		mlx->object[ray.object.id].color = add_vectors(
				mlx->object[ray.object.id].color, selection_color);
	}
	else
	{
		mlx->selected_object = -1;
		ft_putstr("\e[1;1H\e[2J");
		ft_putstr("Rotate camera with up/down/left/right keys\n");
		ft_putstr("Or click on an object to select it\n");
	}
	ray_trace(mlx);
	return (1);
}

static void	rotate_camera(t_mlx *mlx, int keycode)
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
	if (keycode == LEFT || keycode == RIGHT
		|| keycode == DOWN || keycode == UP)
		ray_trace(mlx);
}

static int	key_hook(int keycode, t_mlx *mlx)
{
	int		id;

	id = mlx->selected_object;
	if (id < 0)
		rotate_camera(mlx, keycode);
	if (id >= 0)
		adjust_object(mlx, id, keycode);
	if (keycode == ESC)
		close_window(mlx);
	return (0);
}

void	user_input(t_mlx *mlx)
{
	ft_putstr("Rotate camera with up/down/left/right keys\n");
	ft_putstr("Or click on an object to select it\n");
	mlx_hook(mlx->window, 17, 0, close_window, mlx);
	mlx_mouse_hook(mlx->window, mouse_hook, mlx);
	mlx_key_hook(mlx->window, key_hook, mlx);
}
