/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 20:59:24 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#include "main.h"
#include "user_input/ui_.h"
#include "user_input/ui_mouse_hook.h"
#include "user_input/ui_adjust_object.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"

static int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	exit(EXIT_SUCCESS);
}

static void	rotate_camera(t_mlx *mlx, int keycode)
{
	float	rotation_speed;
	float	angle;
	t_xyz	orientation;

	rotation_speed = PI / 4;
	if (keycode == LEFT || keycode == UP)
		angle = -rotation_speed;
	if (keycode == RIGHT || keycode == DOWN)
		angle = rotation_speed;
	if (keycode == LEFT || keycode == RIGHT)
		initialize_vector(&orientation, 0, 1, 0);
	if (keycode == DOWN || keycode == UP)
		initialize_vector(&orientation, 1, 0, 0);
	mlx->camera.orientation = rotate_vector_by_angle(mlx->camera.orientation,
				orientation, angle);
	ray_trace(mlx);
}

static void	catch_action(t_mlx *mlx, int type, int keycode)
{
	if (keycode == DIAMETER)
		ft_putstr("Adjust diameter with up/down keys\n");
	else if (keycode == SCALE)
		ft_putstr("Adjust scale with up/down keys\n");
	else if (keycode == ROTATE && (type == PLANE || type == SPHERE))
		ft_putstr("Rotation is only possible with a sphere or a cone\n");
	else if (keycode == HEIGHT && (type == PLANE || type == SPHERE))
		ft_putstr("Adjusting height is only possible with a sphere or a cone\n");
	else if (keycode == ROTATE && (type == CYLINDER || type == CONE))
		ft_putstr("Adjust orientation with left/right/up/down keys\n");
	else if (keycode == HEIGHT && (type == CYLINDER || type == CONE))
		ft_putstr("Adjust height with up/down keys\n");
	else if (keycode != UP && keycode != DOWN
		&& keycode != LEFT && keycode != RIGHT)
		ft_putstr("Invalid action\n");
	if (keycode == DIAMETER || keycode == SCALE
		|| ((type == CYLINDER || type == CONE)
			&& (keycode == ROTATE || keycode == HEIGHT || keycode == ROTATE)))
		mlx->selected_action = keycode;
}

static int	key_hook(int keycode, t_mlx *mlx)
{
	int		id;

	id = mlx->selected_object;
	if (id < 0 && (keycode == LEFT || keycode == RIGHT
		|| keycode == DOWN || keycode == UP))
		rotate_camera(mlx, keycode);
	if (id >= 0)
	{
		catch_action(mlx, mlx->object[id].type, keycode);
		adjust_object(mlx, id, keycode);
	}
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
