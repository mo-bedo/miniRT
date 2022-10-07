/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_cylinder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:18 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:07:54 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"
#include "utils/matrices.h"
#include "utils/u_invert_matrix.h"



float	get_intersection_ray_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_matrix4	to_world;
	t_matrix4	to_local;
	t_ray		bck_ray;
	t_cylinder	local_cyl;

	t_xyz	translate;
	t_xyz	rotate;
	t_xyz	scale;


	translate.x = 0 ;
	translate.y = 0;
	translate.z = 0;

	rotate.x = 0;
	rotate.y = 0;
	rotate.z = 0;

	scale.x = 5;
	scale.y = 1;
	scale.z = 5;

	to_local = create_transform_matrix(translate, rotate, scale);
	to_world = invert_matrix(to_local);

	//transform ray to local by applying matrix to_local to ray
	bck_ray.direction = apply_matrix4_to_vector(to_local, ray.direction);
	bck_ray.origin = apply_matrix4_to_vector(to_local, ray.origin);
	
	t_xyz v = normalize_vector( bck_ray.direction);

	t_xyz p = bck_ray.origin;

	float a = pow(v.x, 2.0) + pow(v.y, 2.0);
	float b = 2.0 * (p.x * v.x + p.y * v.y);
	float c = pow(p.x, 2.0) + pow(p.y, 2.0) - 1.0;

	float	num_sqrt = sqrtf(pow(b, 2.0) - 4 * a * c);

	t_xyz poi0;
	t_xyz poi1;
	t_xyz poi2;
	t_xyz poi3;

	float	t[4];
	bool	t1, t2, t3, t4;
	if (num_sqrt > 0.0)
	{
		// There was an intersection.
		// Compute the values for t.
		t[0] = (-b + num_sqrt) / (2 * a);
		t[1] = (-b - num_sqrt) / (2 * a);
		
		// Compute the points of intersection.
		poi0 = add_vectors(bck_ray.origin, multiply_vector(v, t[0]));
		poi1 = add_vectors(bck_ray.origin, multiply_vector(v, t[1]));
		
		// Check if any of these are valid.
		if ((t[0] > 0.0) && (fabs(poi0.z) < 1.0))
		{
			t1 = true;
		}
		else
		{
			t1 = false;
			t[0] = RAY_T_MAX;
		}
		
		if ((t[1] > 0.0) && (fabs(poi1.z) < 1.0))
		{
			t2 = true;
		}
		else
		{
			t2 = false;
			t[1] = RAY_T_MAX;
		}
	}
	else
	{
		t1 = false;
		t2 = false;
		t[0] = RAY_T_MAX;
		t[1] = RAY_T_MAX;
	}


	// test end caps

	if (close_enough(v.x, 0.0))			// dan is de cap gelijk aan de ray dus geen intersect
	{
		t3 = false;
		t4 = false;
		t[2] = RAY_T_MAX;
		t[3] = RAY_T_MAX;
	}
	else		// intersect met cap
	{
		t[2] = (bck_ray.origin.z - 1.0) / -v.z;		// dit is een plane op -1 z
		t[3] = (bck_ray.origin.z + 1.0) / -v.z;		// en 1 op +1 z. dit kan alleen omdat we met een unit cylinder werken in local

		// comput intersect
		poi2 = add_vectors(bck_ray.origin, multiply_vector(v, t[2]));
		poi3 = add_vectors(bck_ray.origin, multiply_vector(v, t[3]));

								// test x^2 + y2 , dus of hij de cirkel raakt
		if ((t[2] > 0.0) && ((sqrtf(pow(poi2.x, 2.0)) + sqrtf(pow(poi2.y, 2.0))) < 1.0 ))
		{
			t3 = true;
		}
		else
		{
			t3 = false;
			t[2] = RAY_T_MAX;
		}
		
		if ((t[3] > 0.0) && ((sqrtf(pow(poi3.x, 2.0)) + sqrtf(pow(poi3.y, 2.0))) < 1.0 ))
		{
			t4 = true;
		}
		else
		{
			t4 = false;
			t[3] = RAY_T_MAX;
		}
	}

	// geen intersect dan stop
	if (!t1 && !t2 && !t3 && !t4)
	{
		return (1e14f);
	}
	float 	temp_cyl = ft_min_float(t[0], t[1]);
	float	temp_cap = ft_min_float(t[2], t[3]);


	// als ray cylinder raakt krijg je andere normal dan wanneer hij de cap raakt.
	//  https://youtu.be/UTz7ytMJ2yk?t=2642
	if (temp_cyl < temp_cap)
	{
		// bereken cylinder normal
	}
	else
	{
		// bereken cap normal
	}	
	return (RAY_T_MAX);		
}
