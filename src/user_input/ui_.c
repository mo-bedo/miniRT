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
	ft_putstr("\e[1;1H\e[2J");
	ft_putstr("Goodbye, hope you had fun!\n");
	mlx_destroy_window(mlx->mlx, mlx->window);
	exit(EXIT_SUCCESS);
}

static void	rotate_camera(t_mlx *mlx, int keycode)
{
	float	rotation_speed;
	float	angle;
	t_xyz	orientation;

	rotation_speed = PI / ROTATION_SPEED;
	if (keycode == LEFT || keycode == LEFT_LINUX
		|| keycode == UP || keycode == UP_LINUX)
		angle = -rotation_speed;
	if (keycode == RIGHT || keycode == RIGHT_LINUX
		|| keycode == DOWN || keycode == DOWN_LINUX)
		angle = rotation_speed;
	if (keycode == LEFT || keycode == LEFT_LINUX
		|| keycode == RIGHT || keycode == RIGHT_LINUX)
		initialize_vector(&orientation, 0, 1, 0);
	if (keycode == DOWN || keycode == DOWN_LINUX
		|| keycode == UP || keycode == UP_LINUX)
		initialize_vector(&orientation, 1, 0, 0);
	mlx->camera.orientation = rotate_vector_by_angle(mlx->camera.orientation,
			orientation, angle);
	ray_trace(mlx);
}

static void	catch_action(t_mlx *mlx, int type, int keycode)
{
	if (keycode == DIAMETER || keycode == DIAMETER_LINUX)
		ft_putstr("Adjust diameter with up/down keys\n");
	else if (keycode == SCALE || keycode == SCALE_LINUX)
		ft_putstr("Adjust scale with up/down keys\n");
	else if (keycode == TRANSLATE || keycode == TRANSLATE_LINUX)
		ft_putstr("Translate object with left/right/up/down/-/+ keys\n");
	else if ((keycode == ROTATE || keycode == ROTATE_LINUX)
		&& (type == PLANE || type == SPHERE))
		ft_putstr("Rotation is only possible with a cylinder or cone\n");
	else if ((keycode == HEIGHT || keycode == HEIGHT_LINUX)
		&& (type == PLANE || type == SPHERE))
		ft_putstr("Adjusting height is only possible with a cylinder or \
			 cone\n");
	else if ((keycode == ROTATE || keycode == ROTATE_LINUX)
		&& (type == CYLINDER || type == CONE))
		ft_putstr("Adjust orientation with left/right/up/down keys\n");
	else if ((keycode == HEIGHT || keycode == HEIGHT_LINUX)
		&& (type == CYLINDER || type == CONE))
		ft_putstr("Adjust height with up/down keys\n");
	else if (keycode != CLOSER && keycode != CLOSER_LINUX
		&& keycode != FURTHER && keycode != FURTHER_LINUX
		&& keycode != ESC && keycode != ESC_LINUX
		&& keycode != UP && keycode != UP_LINUX
		&& keycode != DOWN && keycode != DOWN_LINUX
		&& keycode != LEFT && keycode != LEFT_LINUX
		&& keycode != RIGHT && keycode != RIGHT_LINUX)
		ft_putstr("Invalid action\n");
	if (keycode == TRANSLATE || keycode == TRANSLATE_LINUX
		|| keycode == DIAMETER || keycode == DIAMETER_LINUX
		|| keycode == SCALE || keycode == SCALE_LINUX
		|| ((type == CYLINDER || type == CONE)
			&& (keycode == HEIGHT || keycode == HEIGHT_LINUX
				|| keycode == ROTATE || keycode == ROTATE_LINUX)))
		mlx->selected_action = keycode;
}

static int	key_hook(int keycode, t_mlx *mlx)
{
	int		id;

	id = mlx->selected_object;
	if (id < 0 && (keycode == LEFT || keycode == LEFT_LINUX
			|| keycode == RIGHT || keycode == RIGHT_LINUX
			|| keycode == DOWN || keycode == DOWN_LINUX
			|| keycode == UP || keycode == UP_LINUX))
		rotate_camera(mlx, keycode);
	if (id >= 0)
	{
		catch_action(mlx, mlx->object[id].type, keycode);
		adjust_object(mlx, id, keycode);
	}
	if (keycode == ESC || keycode == ESC_LINUX)
		close_window(mlx);
	return (0);
}

void	user_input(t_mlx *mlx)
{
	if (mlx->object_count <= 0)
		ft_putstr("There are no objects in the scene\n");
	else
		ft_putstr("Click on an object to select it\n");
	mlx_hook(mlx->window, 17, 0, close_window, mlx);
	mlx_mouse_hook(mlx->window, mouse_hook, mlx);
	mlx_key_hook(mlx->window, key_hook, mlx);
}
