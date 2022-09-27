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

// mlx_pixel_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color );

// image moet het 'scherm' zijn (image_screen)

void	ray_trace(t_mlx *mlx, t_cam cam)
{
	t_xyz	screen_coord;

	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		for (int y = 0; y < WINDOW_HEIGHT; y++)
		{
			//// omzetten van 'apart -1 tot +1 coord systeem' naar screen coord
			screen_coord.x = (2.0 * x) / WINDOW_WIDTH - 1.0;
			screen_coord.y = (-2.0 * y) / WINDOW_HEIGHT + 1.0;

			t_ray ray;
			ray = make_ray(screen_coord, cam);

			t_intersection	intersect;
			intersect = create_intersection(ray);
			//// build loop for shapes and intersect
			if (plane_intersect(mlx->d.o.pl[0], &intersect))
			{
				mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0xFF0000);
			}
			if (sphere_intersect(mlx->d.o.sp[0], &intersect))
			{
				mlx_pixel_put(mlx->mlx, mlx->window, x, y, 0x00FF00);
			}
		}
	}
}
