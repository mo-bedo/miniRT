/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:38:51 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/22 12:38:51 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "camera.h"
#include "main.h"
#include "vector_math.h"

t_cam	init_cam(t_mlx mlx)
{
	t_cam	cam;

	// TO DO: what is camera_upguide
	t_xyz camera_upguide;
	camera_upguide.x = 0.0;
	camera_upguide.y = 1.0;
	camera_upguide.z = 0.0;
	cam.origin_point = mlx.d.c.xyz;
	cam.forward = vector_normal(vector_subtraction(mlx.d.c.vector_orientation, camera_upguide));
	cam.right = vector_normal(vector_cross(cam.forward, camera_upguide));
	cam.up = vector_cross(cam.right, cam.forward);
	cam.h = tan(mlx.d.c.field_of_view);
	cam.w = cam.h * (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
	return (cam);
}

//              vec     +         temp				  + temp1
//			    vec     +     vector multi	          + vector multi
//			    vec     + float   * double * vec      +  float   * double * vec
// rayvec = cam.forward + point.x * cam.w * cam.right + point.y * cam.h * cam.up
t_ray	make_ray(t_xyz point, t_cam cam)
{
	t_ray		ray;
	t_xyz	temp;
	t_xyz	temp1;
	t_xyz	temp_add;

	temp = vector_multiplication(cam.right, (point.x * cam.w));
	temp1 = vector_multiplication(cam.up, (point.y * cam.h));
	temp_add = vector_addition(cam.forward, temp);
	ray.direction = vector_normal(vector_addition(temp_add, temp1));
	ray.origin_point = cam.origin_point;
	ray.t_max = RAY_T_MAX;
	return (ray);
}
