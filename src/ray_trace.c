/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:42:20 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/22 17:42:20 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "camera.h"
#include "image_plane.h"
#include "intersect.h"
#include "shape.h"

t_intersection	create_intersection(t_ray ray)
{
	t_intersection inter;

	inter.plane = NULL;
	inter.sphere = NULL;
	inter.ray = ray;
	inter.t = ray.t_max;
	return (inter);
}

static int	create_color(int transparancy, int red, int green, int blue)
{
	return (transparancy << 24 | red << 16 | green << 8 | blue);
}


void	ray_trace(t_mlx *mlx)
{
	t_xyz			screen_point;
	t_ray			ray;
	t_intersection	intersect;

	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		for (int y = 0; y < WINDOW_HEIGHT; y++)
		{
			ray = make_ray(x, y, mlx->camera);
			intersect = create_intersection(ray);
			//// build loop for shapes and intersect
			for (int pl_count = 0; pl_count < mlx->o.pl_count; pl_count++)
			{
				if (plane_intersect(mlx->o.pl[pl_count], &intersect))
					mlx_pixel_put(mlx->mlx, mlx->window, x, y, create_color(1, mlx->o.pl[pl_count].rgb.red, mlx->o.pl[pl_count].rgb.green, mlx->o.pl[pl_count].rgb.blue));
			}
			for (int sp_count = 0; sp_count < mlx->o.sp_count; sp_count++)
			{
				if (sphere_intersect(mlx->o.sp[sp_count], &intersect))
					mlx_pixel_put(mlx->mlx, mlx->window, x, y, create_color(1, mlx->o.sp[sp_count].rgb.red, mlx->o.sp[sp_count].rgb.green, mlx->o.sp[sp_count].rgb.blue);
			}
		}
	}
}
