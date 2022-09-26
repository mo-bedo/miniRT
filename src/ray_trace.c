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

#include "camera.h"
#include "image_plane.h"
#include "intersect.h"
#include "shape.h"

// static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
// 	char	*dst;
// 	int		offset;
//
// 	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	dst = &img->addr[offset];
// 	*(unsigned int *)dst = color;
// }

t_intersection	create_intersection(t_ray ray)
{
	t_intersection inter;

	inter.plane = NULL;
	inter.sphere = NULL;
	inter.ray = ray;
	inter.t = ray.t_max;
}

// mlx_pixel_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color );

// image moet het 'scherm' zijn (image_screen)
void	ray_trace(t_image image, t_cam cam, t_plane plane, t_sphere sphere)
{
	t_vec2	screen_coord;

	for (int x = 0; x < image.width; x++)
	{
		for (int y = 0; y < image.height; y++)
		{
			//// omzetten van 'apart -1 tot +1 coord systeem' naar screen coord
			screen_coord.u = (2.0 * x) / image.width - 1.0;
			screen_coord.v = (2.0 * y) / image.height + 1.0;

			t_ray ray;
			ray = make_ray(screen_coord, cam);

			double	*cur_pixel;
			double temp;

			temp = (double) (x * y * image.width);
			cur_pixel = &temp;

			t_intersection	intersect;
			intersect = create_intersection(ray);
			if (plane_intersect(plane, &intersect))
				return ;
			else
				return ;
//				my_pixel_put(..., zwart)


		}
	}
}
