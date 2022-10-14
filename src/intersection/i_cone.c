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

#include <math.h>

#include "main.h"
#include "utils/u_.h"


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

// float	get_intersect_ray_cone(t_ray ray, t_object cone)
// {
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	det;
// 	float	theta;
	
// 	theta = atan(cone.radius / cone.height);
	
// 	a = pow(get_dot_product(ray.direction, cone.orientation), 2) - pow(cos(theta), 2);
// 	b = 2 * ((get_dot_product(ray.direction, cone.orientation)) * )

// 	return (t);
// }
