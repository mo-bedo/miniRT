/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:28 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/22 15:52:28 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include <stdbool.h>
# include "main.h"
# include "camera.h"

typedef struct s_sphere {
	t_vec	centre;
	float	radius;
}	t_sphere;

typedef struct s_plane {
	t_vec	position;
	t_vec	normal;
}	t_plane;

typedef struct s_shape {
	t_sphere	**spheres;
	t_plane		**planes;
}	t_shape;

// Informatie over waar een ray een object raakt
// hier later ook info over materiaal, direction van het oppervlak etc
typedef struct s_intersection {
	t_ray		ray;
	double		t; // bij init intersection t altijd op ray.t_max zetten (zodat je hierop kan testen
	t_sphere	*sphere;
	t_plane		*plane;
}	t_intersection;

bool	plane_intersect(t_plane plane, t_intersection *intersection);
bool	plane_does_intersect(t_plane plane, t_ray ray);
bool	sphere_intersect(t_sphere sphere, t_intersection *intersection);
bool	sphere_does_intersect(t_sphere sphere, t_ray ray);

#endif
