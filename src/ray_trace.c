/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_trace.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/28 18:51:55 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "ray_trace.h"
#include "plane.h"
#include "sphere.h"
#include "utils/vector_math.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = &img->addr[offset];
	*(unsigned int *)dst = color;
}

t_xy	convert_to_screen_coordinates(t_xy xy)
{
	xy.x = (2.0 * xy.x) / WINDOW_WIDTH - 1.0;
	xy.y = (-2.0 * xy.y) / WINDOW_HEIGHT + 1.0;
	return (xy);
}

// vector Ray direction = normalized(camera.forward + x_vector + y_vector);
// x_vector = camera.right * x * camera.width
// y_vector = camera.up * y * camera.height
t_ray	make_ray(t_xy xy, t_camera camera)
{
	t_ray	ray;
	t_xyz	x_vector;
	t_xyz	y_vector;

	xy = convert_to_screen_coordinates(xy);
	x_vector = multiply_vector(camera.right, (xy.x * camera.width));
	y_vector = multiply_vector(camera.up, (xy.y * camera.height));
	ray.direction = normalize_vector(
			add_vectors(add_vectors(camera.forward, x_vector), y_vector));
	ray.origin_point = camera.origin_point;
	ray.t_max = RAY_T_MAX;
	return (ray);
}

t_intersection	create_intersection(t_ray ray)
{
	t_intersection	inter;

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

void	draw_planes(t_mlx *mlx, t_xy xy, t_intersection *intersect)
{
	int	i;

	i = 0;
	while (i < mlx->o.pl_count)
	{
		if (plane_intersect(mlx->o.pl[i], intersect))
			my_mlx_pixel_put(&mlx->img, (int)xy.x, (int)xy.y,
				create_color(1,
					mlx->o.pl[i].rgb.red,
					mlx->o.pl[i].rgb.green,
					mlx->o.pl[i].rgb.blue));
		++i;
	}
}

void	draw_spheres(t_mlx *mlx, t_xy xy, t_intersection *intersect)
{
	int	i;

	i = 0;
	while (i < mlx->o.sp_count)
	{
		if (sphere_intersect(mlx->o.sp[i], intersect))
			my_mlx_pixel_put(&mlx->img, (int)xy.x, (int)xy.y,
				create_color(1,
					mlx->o.sp[i].rgb.red,
					mlx->o.sp[i].rgb.green,
					mlx->o.sp[i].rgb.blue));
		++i;
	}
}

void	ray_trace(t_mlx *mlx)
{
	t_ray			ray;
	t_intersection	intersect;
	t_xy			xy;

	xy.x = 0;
	while (xy.x < WINDOW_WIDTH)
	{
		xy.y = 0;
		while (xy.y < WINDOW_HEIGHT)
		{
			ray = make_ray(xy, mlx->camera);
			intersect = create_intersection(ray);
			draw_planes(mlx, xy, &intersect);
			draw_spheres(mlx, xy, &intersect);
			xy.y += 1;
		}
		xy.x += 1;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
