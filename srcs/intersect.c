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

#include "camera.h"
#include "intersect.h"
#include "main.h"
#include "vector_math.h"

//	Calculeert dan het punt op de ray als je waarde t weet
//	van r = p + td
t_vec	inter_calculate(double t, t_ray ray)
{
	t_vec	math;

	math = vector_multi(ray.direction, t);
	return (vector_addition(ray.origin_point, math));
}

// geeft aan of de ray iets raakt
bool	inter_intersected(t_intersection intersection)
{
	return (intersection.sphere != NULL);
}

// als de ray iets raakt geeft dit de positie waar hij dat doet
t_vec	inter_position(t_intersection intersection)
{
	t_vec	point;

	point = inter_calculate(intersection.t, intersection.ray);
	return (point);
}
