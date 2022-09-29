/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 12:38:55 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "sphere.h"
#include "utils/utils.h"
#include "utils/vector_math.h"

t_xyz	substract_vectors(t_xyz v1, t_xyz v2);
//
//// plaatst midden van sphere in het midden van xyz
//static t_ray	transpose_ray(t_ray ray, t_xyz centre)
//{
//	ray.origin_point = substract_vectors(ray.origin_point, centre);
//	return (ray);
//}
//
//// Quadratic Formula:
//// when ax^2 + bx + c = 0
//// 	  x = -b+sqrt((b)^2 - 4ac)) / 2 a
//// or x = -b-sqrt((b)^2 - 4ac)) / 2 a
//static void	prepare_quadratic_formula(t_quadratic *q, t_ray ray, t_sphere sp)
//{
//	ray = transpose_ray(ray, sp.center);
//	q->a = get_2d_vector_magnitude(ray.direction);
//	q->b = 2 * get_dot_product(ray.direction, ray.origin_point);
//	q->c = get_2d_vector_magnitude(ray.origin_point) - (sp.radius * sp.radius);
//	q->discriminant = (q->b * q->b) - 4 * q->a * q->c;
//}
//
//// ray intersects two times with sphere (t1 and t2)
//// t1 < RAY_T_MIN 		this means it can reflect itself
//static double	get_distance_to_intersection_sphere(t_quadratic q)
//{
//	double	t1;
//	double	t2;
//
//	t1 = (-q.b - sqrt(q.discriminant)) / (2 * q.a);
//	t2 = (-q.b + sqrt(q.discriminant)) / (2 * q.a);
//	if (t1 > RAY_T_MIN && t2 > RAY_T_MIN)
//		return (get_smallest_double(t1, t2));
//	else if (t1 > RAY_T_MIN)
//		return (t1);
//	else if (t2 > RAY_T_MIN)
//		return (t2);
//	else
//		return (RAY_T_MAX);
//}
//
//// if discriminant is smaller than zero it means there is no intersection;
//bool	sphere_intersect(t_sphere sphere, t_intersection *intersection)
//{
//	t_quadratic	q;
//	double		t;
//
//	prepare_quadratic_formula(&q, intersection->ray, sphere);
//	if (q.discriminant < 0.0)
//		return (false);
//	t = get_distance_to_intersection_sphere(q);
//	if (t < intersection->t)
//		intersection->t = t;
//	else
//		return (false);
//	intersection->sphere = &sphere; //hoezo moet dit?
//	return (true);
//}
