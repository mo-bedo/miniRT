/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/22 12:39:01 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "shape.h"
#include "camera.h"
#include "intersect.h"
#include "main.h"
#include "vector_math.h"

//	Calculeert dan het punt op de ray als je waarde t weet
//	van r = p + td
t_xyz	get_coordinates_of_ray_at_distance(t_ray ray, double distance)
{
	t_xyz	math;

	math = multiply_vector(ray.direction, distance);
	return (add_vectors(ray.origin_point, math));
}

// geeft aan of de ray iets raakt
bool	ray_is_intersecting_with_object(t_intersection intersection)
{
	return (intersection.sphere != NULL);
}

// als de ray iets raakt geeft dit de positie waar hij dat doet
t_xyz	get_coordinates_of_intersection(t_intersection intersection)
{
	t_xyz	point;

	point = get_coordinates_of_ray_at_distance(intersection.ray, intersection.t);
	return (point);
}
