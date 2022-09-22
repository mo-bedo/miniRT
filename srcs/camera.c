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


t_cam	init_cam(t_vec origin, t_vec target, t_vec upguide, float fov, \
										float aspect_ratio)
{
	t_cam	cam;

	cam.origin_point = origin;
	cam.forward = vector_normal(vector_subtraction(target, upguide));
	cam.right = vector_normal(vector_cross(cam.forward, upguide));
	cam.up = vector_cross(cam.right, cam.forward);
	cam.h = tan(fov);
	cam.w = cam.h * aspect_ratio;
	return (cam);
}

//              vec     +         temp				  + temp1
//			    vec     +     vector multi	          + vector multi
//			    vec     + float   * double * vec      +  float   * double * vec
// rayvec = cam.forward + point.x * cam.w * cam.right + point.y * cam.h * cam.up
t_ray	make_ray(t_xyz point, t_cam cam)
{
	t_ray	ray;
	t_vec	temp;
	t_vec	temp1;
	t_vec	temp_add;

	temp = vector_multi(cam.right, (point.x * cam.w));
	temp1 = vector_multi(cam.up, (point.y * cam.h));
	temp_add = vector_addition(cam.forward, temp);
	ray.direction = vector_normal(vector_addition(temp_add, temp1));
	ray.origin_point = cam.origin_point;
	ray.t_max = RAY_T_MAX;
	return (ray);
}
