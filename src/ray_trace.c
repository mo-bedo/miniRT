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

void	ray_trace(t_mlx *mlx, t_cam cam)
{
	t_xyz			screen_point;
	t_ray			ray;
	t_intersection	intersect;
	int				i;

	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		for (int y = 0; y < WINDOW_HEIGHT; y++)
		{
			//// omzetten van 'apart -1 tot +1 coord systeem' naar screen coord
			screen_point.x = (2.0 * x) / WINDOW_WIDTH - 1.0;
			screen_point.y = (-2.0 * y) / WINDOW_HEIGHT + 1.0;
			ray = create_ray(screen_point, cam);
			intersect = create_intersection(ray);
			i = 0;
			while (i <  mlx->d.o.pl_count)
			{
				if (plane_intersect(mlx->d.o.pl[i], &intersect))
				{
					mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0xFF0000);
				}
				i++;
			}
			i = 0;
			while (i < mlx->d.o.sp_count)
			{
				if (sphere_intersect(mlx->d.o.sp[i], &intersect))
				{
					mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0x00FF00);
				}
				i++;
			}
		}
	}
}
