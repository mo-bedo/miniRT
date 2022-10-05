/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_trace.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 19:21:13 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#include "ray_trace.h"
#include "lighting.h"
#include "pixel_put.h"
#include "intersection/i_.h"
#include "utils/u_.h"
#include "utils/u_rotate_vector.h"
#include "utils/u_vector_math.h"

// fastgraph.com/makegames/3drotation
// tutorialandexample.com/3d-rotation

# define PI 3.14f


// 
static t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera,
	float x, float y)
{
	t_xyz	vector;
	t_xyz	rotation_angles;
	int viewport_size = 1;
	
	vector.x = x * viewport_size / (float)WINDOW_HEIGHT;
	vector.y = y * viewport_size / (float)WINDOW_HEIGHT;
	vector.z = camera.canvas_distance;
	return (rotate_vector(vector, camera.rotation_angles));
}


static t_ray	compute_ray(t_objects o, t_xyz origin,
	t_xyz direction, float min_distance)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	ray.object = get_closest_intersection(o, ray, min_distance, RAY_T_MAX);
	return (ray);
}

static t_xyz	compute_reflections_of_reflections(t_mlx *mlx,
	t_ray ray, t_xyz view, int depth)
{
	t_ray	reflected_ray;
	t_xyz	reflected_color;
	t_xyz	reflectivenes_of_object;

	reflected_ray = compute_ray(mlx->o, ray.object.position,
			compute_reflected_ray(view, ray.object.normal), RAY_T_MIN);
	reflected_color = multiply_vector(get_color(mlx, reflected_ray, --depth),
			ray.object.reflective);
	reflectivenes_of_object = multiply_vector(ray.object.color,
			1 - ray.object.reflective);
	return (add_vectors(reflectivenes_of_object, reflected_color));
}

t_xyz	get_color(t_mlx *mlx, t_ray ray, int depth)
{
	t_xyz	view;
	double	light_intensity;

	if (!ray.object.object)
		return (mlx->background_color);
	view = multiply_vector(ray.direction, -1);
	light_intensity = compute_lighting(mlx, view, ray.object);
	ray.object.color = multiply_vector(ray.object.color, light_intensity);
	if (ray.object.reflective <= 0 || depth <= 0)
		return (ray.object.color);
	return (compute_reflections_of_reflections(mlx, ray, view, depth));
}

void	ray_trace(t_mlx *mlx)
{
	t_xyz	color;
	t_xyz	direction;
	t_ray	ray;
	int		x;
	int		y;

	clock_t CPU_time_3;
	x = -WINDOW_WIDTH / 2;
	while (x < WINDOW_WIDTH / 2)
	{
		y = -WINDOW_HEIGHT / 2;
		while (y < WINDOW_HEIGHT / 2)
		{
			
			direction = convert_2d_canvas_to_3d_coordinates(mlx->camera, x, y);
			ray = compute_ray(mlx->o, mlx->camera.center, direction, mlx->camera.canvas_distance);
			color = get_color(mlx, ray, RECURSION_DEPTH);
			my_mlx_pixel_put(&mlx->img, x, y, color);
			y++;
		}
		x++;
	}
	CPU_time_3 = clock();
    printf("Time after ray_trace\t: %ld\n", CPU_time_3);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}
