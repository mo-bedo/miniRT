/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/09 20:15:32 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace/rt_.h"
#include "ray_trace/rt_lighting.h"
#include "ray_trace/rt_pixel_put.h"
#include "intersection/i_.h"
#include "utils/u_.h"

static t_ray	compute_ray(t_mlx mlx, t_xyz origin, t_xyz direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	ray.object = get_closest_intersection(mlx, ray, RAY_T_MAX);
	return (ray);
}

t_xyz	get_color(t_mlx *mlx, t_ray ray)
{
	if (!ray.object.type)
		return (mlx->background_color);
	compute_lighting(&ray.object, mlx);
	return (ray.object.color);
}

void	ray_trace(t_mlx *mlx)
{
	t_xyz	color;
	t_xyz	direction;
	t_ray	ray;
	int		x;
	int		y;

	x = -HALF_WINDOW_WIDTH;
	while (x < HALF_WINDOW_WIDTH)
	{
		y = -HALF_WINDOW_HEIGHT;
		while (y < HALF_WINDOW_HEIGHT)
		{
			direction = convert_2d_canvas_to_3d_coordinates(mlx->camera, x, y);
			ray = compute_ray(*mlx, mlx->camera.center, direction);
			color = get_color(mlx, ray);
			pixel_put(&mlx->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
