/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_adjust_object.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/07 14:13:34 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "user_input/ui_.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"

static void	adjust_radius(t_mlx *mlx, int id, int keycode)
{
	if (keycode == DOWN && mlx->object[id].radius > ADJUSTMENT_SIZE)
	{
		mlx->object[id].radius -= ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
	if (keycode == UP)
	{
		mlx->object[id].radius += ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
}

static void	adjust_height(t_mlx *mlx, int id, int keycode)
{
	if (keycode == DOWN && mlx->object[id].height > ADJUSTMENT_SIZE)
	{
		mlx->object[id].height -= ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
	if (keycode == UP)
	{
		mlx->object[id].height += ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
}

static void	adjust_scale(t_mlx *mlx, int id, int keycode)
{
	if (keycode == DOWN
		&& mlx->object[id].radius > MIN_OBJECT_SIZE
		&& mlx->object[id].height > MIN_OBJECT_SIZE)
	{
		mlx->object[id].radius /= ADJUSTMENT_SCALE;
		mlx->object[id].height /= ADJUSTMENT_SCALE;
		ray_trace(mlx);
	}
	if (keycode == UP)
	{
		mlx->object[id].radius *= ADJUSTMENT_SCALE;
		mlx->object[id].height *= ADJUSTMENT_SCALE;
		ray_trace(mlx);
	}
}

static void	rotate_object(t_mlx *mlx, int id, int keycode)
{
	float	rotation_speed;
	float	angle;
	t_xyz	orientation;

	rotation_speed = PI / ROTATION_SPEED;
	if (keycode == LEFT || keycode == UP)
		angle = -rotation_speed;
	if (keycode == RIGHT || keycode == DOWN)
		angle = rotation_speed;
	if (keycode == LEFT || keycode == RIGHT)
		initialize_vector(&orientation, 0, 1, 0);
	if (keycode == DOWN || keycode == UP)
		initialize_vector(&orientation, 0, 0, 1);
	if (keycode == LEFT || keycode == RIGHT || keycode == DOWN || keycode == UP)
		mlx->object[id].orientation = rotate_vector_by_angle(
				mlx->object[id].orientation, orientation, angle);
	ray_trace(mlx);
}

void	adjust_object(t_mlx *mlx, int id, int keycode)
{
	if (mlx->selected_action == DIAMETER
		|| (mlx->selected_action == SCALE && mlx->object[id].type == SPHERE))
		adjust_radius(mlx, id, keycode);
	if (mlx->object[id].type == CYLINDER || mlx->object[id].type == CONE)
	{
		if (mlx->selected_action == HEIGHT)
			adjust_height(mlx, id, keycode);
		if (mlx->selected_action == SCALE)
			adjust_scale(mlx, id, keycode);
		if (mlx->selected_action == ROTATE)
			rotate_object(mlx, id, keycode);
	}
}
