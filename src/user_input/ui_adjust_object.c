#include "main.h"
#include "user_input/ui_.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"

static void	adjust_radius(t_mlx *mlx, int id, int keycode)
{
	if ((keycode == DOWN || keycode == DOWN_LINUX)
		&& mlx->object[id].radius > ADJUSTMENT_SIZE)
	{
		mlx->object[id].radius -= ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
	if (keycode == UP || keycode == UP_LINUX)
	{
		mlx->object[id].radius += ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
}

static void	adjust_height_scale(t_mlx *mlx, int id, int keycode)
{
	if (mlx->object[id].height > ADJUSTMENT_SIZE
		&& ((mlx->selected_action == HEIGHT && keycode == DOWN)
			|| (mlx->selected_action == HEIGHT_LINUX && keycode == DOWN_LINUX)))
	{
		mlx->object[id].height -= ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
	if ((mlx->selected_action == HEIGHT && keycode == UP)
		|| (mlx->selected_action == HEIGHT_LINUX && keycode == UP_LINUX))
	{
		mlx->object[id].height += ADJUSTMENT_SIZE;
		ray_trace(mlx);
	}
	if (mlx->object[id].radius > MIN_OBJECT_SIZE
		&& mlx->object[id].height > MIN_OBJECT_SIZE
		&& ((mlx->selected_action == SCALE && keycode == DOWN)
			|| (mlx->selected_action == SCALE_LINUX && keycode == DOWN_LINUX)))
	{
		mlx->object[id].radius /= ADJUSTMENT_SCALE;
		mlx->object[id].height /= ADJUSTMENT_SCALE;
		ray_trace(mlx);
	}
	if ((mlx->selected_action == SCALE && keycode == UP)
		|| (mlx->selected_action == SCALE_LINUX && keycode == UP_LINUX))
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
		initialize_vector(&orientation, 0, 0, 1);
	if (keycode == LEFT || keycode == LEFT_LINUX
		|| keycode == RIGHT || keycode == RIGHT_LINUX
		|| keycode == DOWN || keycode == DOWN_LINUX
		|| keycode == UP || keycode == UP_LINUX)
		mlx->object[id].orientation = rotate_vector_by_angle(
				mlx->object[id].orientation, orientation, angle);
	ray_trace(mlx);
}

static void	translate_object(t_mlx *mlx, int id, int keycode)
{
	if (keycode == LEFT || keycode == LEFT_LINUX)
			mlx->object[id].center.x -= 1;
	if (keycode == RIGHT || keycode == RIGHT_LINUX)
			mlx->object[id].center.x += 1;
	if (keycode == DOWN || keycode == DOWN_LINUX)
			mlx->object[id].center.y -= 1;
	if (keycode == UP || keycode == UP_LINUX)
			mlx->object[id].center.y += 1;
	if (keycode == CLOSER || keycode == CLOSER_LINUX)
			mlx->object[id].center.z -= 1;
	if (keycode == FURTHER || keycode == FURTHER_LINUX)
			mlx->object[id].center.z += 1;
	ray_trace(mlx);
}

void	adjust_object(t_mlx *mlx, int id, int keycode)
{
	if (mlx->selected_action == TRANSLATE
		|| mlx->selected_action == TRANSLATE_LINUX)
		translate_object(mlx, id, keycode);
	if (mlx->selected_action == DIAMETER
		|| mlx->selected_action == DIAMETER_LINUX
		|| ((mlx->selected_action == SCALE
				|| mlx->selected_action == SCALE_LINUX)
			&& mlx->object[id].type == SPHERE))
		adjust_radius(mlx, id, keycode);
	if (mlx->object[id].type == CYLINDER || mlx->object[id].type == CONE)
	{
		if (mlx->selected_action == HEIGHT
			|| mlx->selected_action == HEIGHT_LINUX
			|| mlx->selected_action == SCALE
			|| mlx->selected_action == SCALE_LINUX)
			adjust_height_scale(mlx, id, keycode);
		if (mlx->selected_action == ROTATE
			|| mlx->selected_action == ROTATE_LINUX)
			rotate_object(mlx, id, keycode);
	}
}
