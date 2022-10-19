/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_adjust_object.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:13:54 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "user_input/ui_.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"

static void	adjust_radius(t_mlx *mlx, int id, int keycode)
{
	float	adjustment_scale;

	adjustment_scale = 0.2;
	if (keycode == DOWN && mlx->object[id].radius > adjustment_scale)
	{
		mlx->object[id].radius -= adjustment_scale;
		ray_trace(mlx);
	}
	if (keycode == UP)
	{
		mlx->object[id].radius += adjustment_scale;
		ray_trace(mlx);
	}
}

static void	adjust_height(t_mlx *mlx, int id, int keycode)
{
	float	adjustment_scale;

	adjustment_scale = 0.2;
	if (keycode == DOWN && mlx->object[id].height > adjustment_scale)
	{
		mlx->object[id].height -= adjustment_scale;
		ray_trace(mlx);
	}
	if (keycode == UP)
	{
		mlx->object[id].height += adjustment_scale;
		ray_trace(mlx);
	}
}

static void	adjust_scale(t_mlx *mlx, int id, int keycode)
{
	float	adjustment_scale;
	float	min_size;

	adjustment_scale = 1.2;
	min_size = 0.1;
	if (keycode == DOWN
		&& mlx->object[id].radius > min_size
		&& mlx->object[id].height > min_size)
	{
		mlx->object[id].radius /= adjustment_scale;
		mlx->object[id].height /= adjustment_scale;
		ray_trace(mlx);
	}
	if (keycode == UP)
	{
		mlx->object[id].radius *= adjustment_scale;
		mlx->object[id].height *= adjustment_scale;
		ray_trace(mlx);
	}
}

static void	rotate_object(t_mlx *mlx, int id, int keycode)
{
	float	rotation_speed;
	float	angle;
	t_xyz	orientation;

	rotation_speed = PI / 6;
	if (keycode == LEFT || keycode == UP)
		angle = -rotation_speed;
	if (keycode == RIGHT || keycode == DOWN)
		angle = rotation_speed;
	if (keycode == LEFT || keycode == RIGHT)
		initialize_vector(&orientation, 0, 1, 0);
	if (keycode == DOWN || keycode == UP)
		initialize_vector(&orientation, 0, 0, 1);
	mlx->object[id].orientation = rotate_vector_by_angle(
			mlx->object[id].orientation, orientation, angle);
	// DEBUG_STR("");
	// DEBUG_DOUBLE(mlx->object[id].orientation.x);
	// DEBUG_DOUBLE(mlx->object[id].orientation.y);
	// DEBUG_DOUBLE(mlx->object[id].orientation.z);
	// DEBUG_DOUBLE(mlx->object[id].normal.x);
	// DEBUG_DOUBLE(mlx->object[id].normal.y);
	// DEBUG_DOUBLE(mlx->object[id].normal.z);
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
