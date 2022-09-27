/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:38:45 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/22 12:38:45 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "main.h"

// je wilt niet dat een ray die 'bounct' van een object tegen zichzelf kaatst
# define RAY_T_MIN 0.0001f

// zeer onwaarschijnlijk dat iets verder dan deze max is
# define RAY_T_MAX 1.0e30f

typedef struct s_ray {
	t_xyz	direction;
	t_xyz		origin_point;
	double		t_max;
}	t_ray;

typedef struct s_cam {
	t_xyz	origin_point;
	t_xyz	forward;
	t_xyz	up;
	t_xyz	right;
	double	h;
	double	w;
}	t_cam;

t_ray	make_ray(t_xyz point, t_cam cam);
t_cam	init_cam(t_mlx mlx);

#endif			// CAMERA_H
