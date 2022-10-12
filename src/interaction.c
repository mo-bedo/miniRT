/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:54:51 by mweitenb          #+#    #+#             */
/*   Updated: 2022/10/12 11:03:45 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "interaction.h"
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

// int	mouse_hook(int keycode, int x, int y, t_mlx *mlx)
// {
// 	t_xyz	direction;
// 	// t_ray	ray;

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

int	mouse_hook_linux(int keycode, int x, int y, t_mlx *mlx)
{
	t_xyz	direction;
	t_ray	ray;
	int		prev_id;
	t_xyz	selection_color;

	initialize_vector(&selection_color, 100, 100, 100);
	if (keycode == MOUSE_CLICK)
	{
		direction = convert_2d_canvas_to_3d_coordinates(mlx->camera,
				x - (WINDOW_WIDTH / 2), y - (WINDOW_HEIGHT / 2));
		ray = compute_ray(*mlx, mlx->camera.center, direction);
		prev_id = mlx->selected_object;
		if (mlx->selected_object >= 0)
			mlx->object[prev_id].color = substract_vectors(
					mlx->object[prev_id].color, selection_color);
		if (ray.object.type != NONE)
		{
			mlx->selected_object = ray.object.id;
			mlx->object[ray.object.id].color = add_vectors(
					mlx->object[ray.object.id].color, selection_color);
		}
		else
			mlx->selected_object = -1;
		ray_trace(mlx);
	}
	return (0);
}

static void	catch_action(t_mlx *mlx, int type, int keycode)
{
	if(keycode == DIAMETER)
		ft_putstr("Adjust diameter with up/down keys\n");
	if(keycode == SCALE)
		ft_putstr("Adjust scale with up/down keys\n");
	if (keycode == ROTATE && (type == PLANE || type == SPHERE))
		ft_putstr("Rotation is only possible with a sphere or a cone\n");
	if (keycode == HEIGHT && (type == PLANE || type == SPHERE))
		ft_putstr("Adjustint the height is only possible with a sphere or a cone\n");
	if(keycode == ROTATE && (type == CYLINDER || type == CONE))
		ft_putstr("Adjust orientation with left/right/up/down keys\n");
	if(keycode == HEIGHT && (type == CYLINDER || type == CONE))
		ft_putstr("Adjust height with up/down keys\n");
	if (keycode == DIAMETER || keycode == SCALE || 
		((type == CYLINDER || type == CONE)
			&& (keycode == ROTATE || keycode == HEIGHT || keycode == ROTATE)))
		mlx->selected_action = keycode;
}

static void rotate_camera(t_mlx *mlx, int keycode)
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
	ray_trace(mlx);
}

static void adjust_radius(t_mlx *mlx, int type, int id, int keycode)
{
	float	adjustment_scale;

	adjustment_scale = 0.2;
	if (mlx->selected_action == DIAMETER
		|| (mlx->selected_action == SCALE && type == SPHERE))
	{
		if (keycode == DOWN && type > adjustment_scale)
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

static void adjust_height(t_mlx *mlx, int id, int keycode)
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

static void adjust_scale(t_mlx *mlx, int id, int keycode)
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

int	key_hook(int keycode, t_mlx *mlx)
{
	int		id;

	id = mlx->selected_object;
	if (id < 0)
		rotate_camera(mlx, keycode);
	if (id >= 0)
	{
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
					mlx->object[id].orientation = normalize_vector(mlx->object[id].orientation);
					ray_trace(mlx);
				}
				if (keycode == RIGHT)
				{
					mlx->object[id].orientation.x += 0.4;
					mlx->object[id].orientation = normalize_vector(mlx->object[id].orientation);
					ray_trace(mlx);
				}
				if (keycode == UP)
				{
					if (mlx->object[id].orientation.z >= 0)
						mlx->object[id].orientation.y -= 0.4;
					else
						mlx->object[id].orientation.y += 0.4;
					mlx->object[id].orientation = normalize_vector(mlx->object[id].orientation);
					ray_trace(mlx);
				}
				if (keycode == DOWN)
				{
					if (mlx->object[id].orientation.z >= 0)
						mlx->object[id].orientation.y += 0.4;
					else
						mlx->object[id].orientation.y -= 0.4;
					mlx->object[id].orientation = normalize_vector(mlx->object[id].orientation);
					ray_trace(mlx);
				}
			}
		}
	}
	// DEBUG_INT(keycode);
	if (keycode == ESC)
		close_window(mlx);
	return (0);
}

void	interaction(t_mlx *mlx)
{
	mlx_hook(mlx->window, 17, 0, close_window, mlx);
	// mlx_mouse_hook(mlx->window, mouse_hook, mlx);
	mlx_mouse_hook(mlx->window, mouse_hook_linux, mlx);
	mlx_key_hook(mlx->window, key_hook, mlx);
}
