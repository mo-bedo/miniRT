/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/16 14:09:33 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// goede uitleg!
// https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/

#include "intersection/i_utils.h"
#include "main.h"
#include "ray_trace/rt_.h"
#include "utils/u_vector_math.h"
#include "utils/u_compare.h"

#include <math.h>



// Quadratic Formula:
// when ax^2 + bx + c = 0
// 	  x = -b+sqrt((b)^2 - 4ac)) / 2 a
// or x = -b-sqrt((b)^2 - 4ac)) / 2 a
// if discriminant is smaller than zero it means there is no intersection;
// ray intersects two times with a 3D object
// static t_t4	quadratic_formula_cone(t_xyz ray_direction, t_xyz cone_orientation,
// 								double theta, t_xyz c_o)
// {
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	discriminant;
// 	t_t4	t;

// 	t.t1 = RAY_T_MAX;
// 	t.t2 = RAY_T_MAX;
// 	a = get_dot_product(ray.direction, ray.direction) - (1.0 + theta * theta) *
// 				powf(get_dot_product(ray.direction, cone.orientation), 2);
// 	b = 2 * (get_dot_product(ray.direction, c_o) - (1.0 + theta * theta) * 
// 				get_dot_product(ray.direction, cone.orientation) * 
// 				get_dot_product(c_o, cone.orientation)); 
// 	c = get_dot_product(c_o, c_o) - (1.0 + theta * theta) * 
// 				powf(get_dot_product(c_o, cone.orientation), 2.0);
// 	discriminant = pow(b, 2) - (4 * a * c);
// 	if (discriminant < 0)
// 		return (RAY_T_MAX);
// 	a = 2 * a;
// 	discriminant = sqrt(discriminant);
// 	t.t1 = (-b - discriminant) / a;
// 	t.t2 = (-b + discriminant) / a;
// 	return (ft_min_float(t.t1, t.t2));
// }


static t_t4	create_2_infinite_cones(t_ray ray, t_object cone)
{
	t_t4	t;
	float	a;
	float	b;
	float	c;
	float	discriminant;	
	
	

	float	theta;
	t_xyz	c_o;
	
	
	c_o = substract_vectors(ray.origin, cone.center);
	theta = atan(cone.radius / cone.height);

	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;
	a = get_dot_product(ray.direction, ray.direction) - (1.0 + theta * theta) *
				powf(get_dot_product(ray.direction, cone.orientation), 2);
	b = 2 * (get_dot_product(ray.direction, c_o) - (1.0 + theta * theta) * 
				get_dot_product(ray.direction, cone.orientation) * 
				get_dot_product(c_o, cone.orientation)); 
	c = get_dot_product(c_o, c_o) - (1.0 + theta * theta) * 
				powf(get_dot_product(c_o, cone.orientation), 2.0);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (t);
	a = 2 * a;
	discriminant = sqrt(discriminant);
	t.t1 = (-b - discriminant) / a;
	t.t2 = (-b + discriminant) / a;
	return (t);
}

/*
	theta
	 |\
	 | \
   h |  \
	 |   \
	 |____\
        r
	To get theta we simple use tan = r / h, since we know height and radius
	
	so theta = tanˆ-1(r/h)
*/
float	get_intersection_ray_cone(t_ray ray, t_object cone)
{

	// float	theta;
	// t_xyz	c_o;
	t_t4	t;
	
	// c_o = substract_vectors(ray.origin, cone.center);
	// theta = atan(cone.radius / cone.height);
	t = create_2_infinite_cones(ray, cone);
	if (t.t1 < 0)
		t.t1 = RAY_T_MAX;
	if (t.t2 < 0)
		t.t2 = RAY_T_MAX;	

	// finite cone maken


	// als we dubbel cone hebben
	// if (v dot p < 0) discard), 
	float	t_result;
	t_xyz	intersect;
	
	t_result = ft_min_float(t.t1, t.t2);
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t_result));
	// if (get_dot_product(cone.orientation, intersect) < 0)
	// 	return RAY_T_MAX;

	// printf("%f %f\n", t.t1, t.t2);
	return (t_result);
}
