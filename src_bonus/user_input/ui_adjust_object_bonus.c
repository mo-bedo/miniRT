/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_adjust_object_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/11 18:15:40 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"
#include "user_input/ui_bonus.h"
#include "ray_trace/rt_bonus.h"
#include "utils/u_bonus.h"

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

static void	adjust_height_scale(t_mlx *mlx, int id, int keycode)
{
	if (mlx->selected_action == HEIGHT
		&& keycode == DOWN && mlx->object[id].height > ADJUSTMENT_SIZE)
	{
		mlx->object[id].height -= ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
	if (mlx->selected_action == HEIGHT && keycode == UP)
	{
		mlx->object[id].height += ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
	if (mlx->selected_action == SCALE && keycode == DOWN
		&& mlx->object[id].radius > MIN_OBJECT_SIZE
		&& mlx->object[id].height > MIN_OBJECT_SIZE)
	{
		mlx->object[id].radius /= ADJUSTMENT_SCALE;
		mlx->object[id].height /= ADJUSTMENT_SCALE;
		ray_trace(mlx);
	}
	if (mlx->selected_action == SCALE && keycode == UP)
	{
		mlx->object[id].radius *= ADJUSTMENT_SCALE;
		mlx->object[id].height *= ADJUSTMENT_SCALE;
		ray_trace(mlx);
	}
}

static void	rotate_object(t_mlx *mlx, int id, int keycode)
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

static void	translate_object(t_mlx *mlx, int id, int keycode)
{
	if (keycode == LEFT)
			mlx->object[id].center.x -= 1;
	if (keycode == RIGHT)
			mlx->object[id].center.x += 1;
	if (keycode == DOWN)
			mlx->object[id].center.y -= 1;
	if (keycode == UP)
			mlx->object[id].center.y += 1;
	if (keycode == CLOSER)
			mlx->object[id].center.z -= 1;
	if (keycode == FURTHER)
			mlx->object[id].center.z += 1;
	ray_trace(mlx);
}

void	adjust_object(t_mlx *mlx, int id, int keycode)
{
	if (mlx->selected_action == TRANSLATE)
		translate_object(mlx, id, keycode);
	if (mlx->selected_action == DIAMETER
		|| (mlx->selected_action == SCALE && mlx->object[id].type == SPHERE))
		adjust_radius(mlx, id, keycode);
	if (mlx->object[id].type == CYLINDER)
	{
		if (mlx->selected_action == HEIGHT || mlx->selected_action == SCALE)
			adjust_height_scale(mlx, id, keycode);
		if (mlx->selected_action == ROTATE)
			rotate_object(mlx, id, keycode);
	}
}
