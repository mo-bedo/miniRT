/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_adjust_object.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 15:42:09 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "user_input/ui_.h"
#include "ray_trace/rt_.h"
#include "mlx.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

#include <stdlib.h>

static void	catch_action(t_mlx *mlx, int type, int keycode)
{
	if (keycode == DIAMETER)
		ft_putstr("Adjust diameter with up/down keys\n");
	if (keycode == SCALE)
		ft_putstr("Adjust scale with up/down keys\n");
	if (keycode == ROTATE && (type == PLANE || type == SPHERE))
		ft_putstr("Rotation is only possible with a sphere or a cone\n");
	if (keycode == HEIGHT && (type == PLANE || type == SPHERE))
		ft_putstr("Adjusting height is only possible with a sphere or a cone\n");
	if (keycode == ROTATE && (type == CYLINDER || type == CONE))
		ft_putstr("Adjust orientation with left/right/up/down keys\n");
	if (keycode == HEIGHT && (type == CYLINDER || type == CONE))
		ft_putstr("Adjust height with up/down keys\n");
	if (keycode == DIAMETER || keycode == SCALE
		|| ((type == CYLINDER || type == CONE)
			&& (keycode == ROTATE || keycode == HEIGHT || keycode == ROTATE)))
		mlx->selected_action = keycode;
}

static void	adjust_radius(t_mlx *mlx, int type, int id, int keycode)
{
	float	adjustment_scale;

	adjustment_scale = 0.2;
	if (mlx->selected_action == DIAMETER
		|| (mlx->selected_action == SCALE && type == SPHERE))
	{
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
}

static void	adjust_height(t_mlx *mlx, int id, int keycode)
{
	float	adjustment_scale;

	adjustment_scale = 0.2;
	if (mlx->selected_action == HEIGHT)
	{
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
}

static void	adjust_scale(t_mlx *mlx, int id, int keycode)
{
	float	adjustment_scale;
	float	min_size;

	adjustment_scale = 1.2;
	min_size = 0.1;
	if (mlx->selected_action == SCALE)
	{
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
}

void	adjust_object(t_mlx *mlx, int id, int keycode)
{
	DEBUG_INT(keycode);
	catch_action(mlx, mlx->object[id].type, keycode);
	adjust_radius(mlx, mlx->object[id].type, id, keycode);
	if (mlx->object[id].type == CYLINDER || mlx->object[id].type == CONE)
	{
		adjust_height(mlx, id, keycode);
		adjust_scale(mlx, id, keycode);
		if (mlx->selected_action == ROTATE)
		{
			if (keycode == LEFT)
			{
				// if (mlx->object[id].orientation.z >= 0)
					// mlx->object[id].orientation.z -= 0.4;
				// else
					mlx->object[id].orientation.x -= 0.4;
				normalize_vector(&mlx->object[id].orientation);
				ray_trace(mlx);
			}
			if (keycode == RIGHT)
			{
				mlx->object[id].orientation.x += 0.4;
				normalize_vector(&mlx->object[id].orientation);
				ray_trace(mlx);
			}
			if (keycode == UP)
			{
				if (mlx->object[id].orientation.z >= 0)
					mlx->object[id].orientation.y -= 0.4;
				else
					mlx->object[id].orientation.y += 0.4;
				normalize_vector(&mlx->object[id].orientation);
				ray_trace(mlx);
			}
			if (keycode == DOWN)
			{
				if (mlx->object[id].orientation.z >= 0)
					mlx->object[id].orientation.y += 0.4;
				else
					mlx->object[id].orientation.y -= 0.4;
				normalize_vector(&mlx->object[id].orientation);
				ray_trace(mlx);
			}
		}
	}
}
