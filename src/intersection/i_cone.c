/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/13 13:30:25 by jbedaux          ###   ########.fr       */
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
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	theta;
	t_xyz	c_o;
	t_t4	t;



	c_o = substract_vectors(ray.origin, cone.center);
	theta = atan(cone.radius / cone.height);
	theta *= 180 / 3.1415;
	printf("%f\n", theta);
	a = pow(get_dot_product(ray.direction, cone.orientation), 2) - pow(cos(theta), 2);
	b = 2 * ((get_dot_product(ray.direction, cone.orientation)) * 
			(get_dot_product(c_o, cone.orientation)) - get_dot_product(ray.direction, c_o) 
				* pow(cos(theta), 2));
	c = (pow(get_dot_product(c_o, cone.orientation), 2)) - get_dot_product(c_o, c_o) * pow(cos(theta), 2);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (RAY_T_MAX);
	a = 2 * a;
	discriminant = sqrt(discriminant);
	t.t1 = (-b - discriminant) / a;
	t.t2 = (-b + discriminant) / a;
	// if (t.t1 < 0)
	// 	t.t1 = RAY_T_MAX;
	// if (t.t2 < 0)
	// 	t.t2 = RAY_T_MAX;	

	// als we dubbel cone hebben
	// if (v dot p < 0) discard), 

	return (ft_min_float(t.t1, t.t2));
}
