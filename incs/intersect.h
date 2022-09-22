/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/22 12:39:01 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "camera.h"
# include "sphere.h"

// Informatie over waar een ray een object raakt
// hier later ook info over materiaal, direction van het oppervlak etc
typedef struct s_intersection {
	t_ray		ray;
	float		t; // bij init intersection t altijd op ray.t_max zetten (zodat je hierop kan testen
	t_sphere	*sphere;

}	t_intersection;

#endif
