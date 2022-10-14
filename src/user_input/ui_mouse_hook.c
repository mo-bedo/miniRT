/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui_mouse_hook.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 19:54:51 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 20:31:29 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "user_input/ui_.h"
#include "user_input/ui_adjust_object.h"
#include "ray_trace/rt_.h"
#include "intersection/i_.h"
#include "mlx.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

#include <stdlib.h>

static t_object	get_selected_object(t_mlx *mlx, int x, int y)
{
	t_ray	ray;
	int		adj_x;
	int		adj_y;

	adj_x = x - HALF_WINDOW_WIDTH;
	adj_y = HALF_WINDOW_HEIGHT - y;
	ray.origin = mlx->camera.center;
	ray.direction = convert_2d_canvas_to_3d_coordinates(mlx->camera, adj_x, adj_y);
	ray.object = get_closest_intersection(*mlx, ray, RAY_T_MAX);
	adj_y +=1;
	return (ray.object);
}

static void	restore_colors_deselected_object(t_mlx *mlx, t_xyz color)
{
	int			prev_id;
	t_object	*deselected_obj;

	prev_id = mlx->selected_object;
	deselected_obj = &mlx->object[prev_id];
	if (mlx->selected_object >= 0)
		deselected_obj->color = substract_vectors(deselected_obj->color, color);
}

static void	adjust_colors_selected_object(t_mlx *mlx,
	t_object selected, t_xyz color)
{
	int	id;

	ft_putstr("\e[1;1H\e[2J");
	ft_putstr("Press the following keys to select an action\n");
	ft_putstr("D\t: Adjust the diameter\n");
	ft_putstr("S\t: Scale the object\n");
	if (selected.type == CYLINDER || selected.type == CONE)
	{
		ft_putstr("H\t: Adjust the height\n");
		ft_putstr("R\t: Rotate the object\n");
	}
	id = selected.id;
	mlx->selected_object = selected.id;
	mlx->object[id].color = add_vectors(mlx->object[id].color, color);
}

int	mouse_hook(int keycode, int x, int y, t_mlx *mlx)
{
	t_object	selected;
	t_xyz		selection_color;

	initialize_vector(&selection_color, 100, 100, 100);
	if (keycode == MOUSE_CLICK)
	{
		selected = get_selected_object(mlx, x, y);
		restore_colors_deselected_object(mlx, selection_color);
		if (selected.type != NONE && selected.type != PLANE)
			adjust_colors_selected_object(mlx, selected, selection_color);
		else
		{
			mlx->selected_object = -1;
			ft_putstr("\e[1;1H\e[2J");
			ft_putstr("Rotate camera with up/down/left/right keys\n");
			ft_putstr("Or click on an object to select it\n");
		}
		ray_trace(mlx);
	}
	return (0);
}
