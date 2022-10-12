/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:18 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/12 16:40:54 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "math.h"
#include "intersection/i_plane.h"
#include "ray_trace/rt_.h"
#include "utils/u_.h"
#include "utils/u_vector_math.h"

static t_t4	check_t_values(t_t4 t)
{
	if (t.t1 < RAY_T_MIN)
		t.t1 = RAY_T_MAX;
	if (t.t2 < RAY_T_MIN)
		t.t2 = RAY_T_MAX;
	if (t.t3 < RAY_T_MIN)
		t.t3 = RAY_T_MAX;
	if (t.t4 < RAY_T_MIN)
		t.t4 = RAY_T_MAX;
	return (t);
}


/*

    the hit_pt is on the SIDE of the cylinder. We can use dot product to find the point 'pt' 
	on the center line of the cylinder, so that the vector (hit_pt - pt) is orthogonal to the 
	cylinder's orientation.

    t = dot((hit_pt - cy.bottom_center), cy.ori); 
    pt = cy.bottom_center + t * cy.ori;
    surface_normal = normalize(hit_pt - pt)));


*/
static void	get_cylinder_normal(t_ray ray, t_object *cylinder, t_t4 t_)
{
	float	t;
	t_xyz	intersect;
	t_xyz	orientation;
	t_xyz	point_t;

	orientation = normalize_vector(cylinder->vector_orientation);
	t = ft_min_float(t_.t1, t_.t2);
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	t = get_dot_product(substract_vectors(intersect, cylinder->center), orientation);
	point_t = add_vectors(cylinder->center, multiply_vector(orientation, t));
	cylinder->normal = normalize_vector(substract_vectors(intersect, point_t));
 }

// Creating an infinite cylinder with the quadratic equation
// with ray =  Pa + Va t:
// and Q = a point on the cilinder
// (Q - Pa - (Va ,Q - Pa )Va )ˆ2 - Rˆ2 = 0
static t_t4	create_infinite_cylinder(t_ray ray, t_object *cylinder)
{
	float	a;
	float	b;
	float	c;
	float	det;
	t_t4	t;
	t_xyz	temp_cross;
	t_xyz	temp_cross2;

	t.t1 = RAY_T_MAX;
	t.t2 = RAY_T_MAX;
	temp_cross = cross(ray.direction, cylinder->vector_orientation);
	temp_cross2 = cross(substract_vectors(ray.origin, cylinder->center), cylinder->vector_orientation);
	a = get_dot_product(temp_cross, temp_cross);
	b = 2 * get_dot_product(temp_cross, temp_cross2);
	c = get_dot_product(temp_cross2, temp_cross2) - (pow(cylinder->radius, 2) 
		* get_dot_product(cylinder->vector_orientation, cylinder->vector_orientation));
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
		return (t);
	a = 2 * a;
	det = sqrt(det);
	t.t1 = (-b - det) / a;	
	t.t2 = (-b + det) / a;	
	return (t);	
}

// Checks if the infinite cylinder values are between the caps of the cylinder by comparing them
// to the heigth (max).  
static t_t4	create_finite_cylinder_no_caps(t_ray ray, t_object *cylinder, t_t4 t)
{
	double	max_len;
	t_xyz	intersect;
	t_xyz	len;
	
	// max is dus de maximale lengte die tussen het cylinder.centerpoint en het intersectie punt mag zitten.
	// Dit is dus de afstand van het center naar de rand van de cirkel (en berekenen we door pythagoras)
	max_len = sqrt(pow(cylinder->height / 2, 2) + pow(cylinder->radius, 2));
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t.t1));
	len = substract_vectors(intersect, cylinder->center);
	// Als deze if waar is dan is het intersectie punt dus niet tussen de cylinder caps
	if (get_vector_length(len) > max_len) 
		t.t1 = RAY_T_MAX;
	// en dan nog een keer voor t2 kijken	
	intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t.t2));
	len = substract_vectors(intersect, cylinder->center);
	if (get_vector_length(len) > max_len) 
		t.t2 = RAY_T_MAX;	
	return (t);
}

//	formules die gelden voor de cap
//	(Q3 - P1)^2 < R^2
//	(Q4 - P2)^2 < R^2
//	Qi = p + v Ti 
//	P1 = bottomcap center
// dus (lengte van Q3 - P1)^2 < R^2 anders is plane_intersectie niet op de cap
// met flag geef je aan of het de top of de bottom cap is
float	get_intersect_with_cap_planes(t_ray ray, t_object *cylinder, float flag)
{
	t_object	cap;
	t_xyz		plane_intersect;
	float		capcenter_to_intersect;
	float		t;
	t_xyz		orientation;

	orientation = normalize_vector(cylinder->vector_orientation);
	cap.vector_orientation = cylinder->vector_orientation;
	cap.center = add_vectors(cylinder->center, multiply_vector(orientation, (cylinder->height / 2) * flag));
	t = get_intersection_ray_plane(ray, cap);
	plane_intersect = add_vectors(ray.origin, multiply_vector(ray.direction, t));
	capcenter_to_intersect = get_vector_length(substract_vectors(plane_intersect, cap.center));
	if ((t < 0) || (capcenter_to_intersect > cylinder->radius))
		t = RAY_T_MAX;
	return (t);	
}

// Cylinder.center is the exact middle of the cylinder 
// (so not the center of either one of the sides)
float	get_intersection_ray_cylinder(t_ray ray, t_object *cylinder)
{
	t_t4	t;

	t = create_infinite_cylinder(ray, cylinder);
	t = create_finite_cylinder_no_caps(ray, cylinder, t);
	t.t3 = get_intersect_with_cap_planes(ray, cylinder, -1); 	// vind t voor bottom cap
	t.t4 = get_intersect_with_cap_planes(ray, cylinder, 1); 	// vind t voor top cap
	t = check_t_values(t);
	if (ft_min_float(t.t1, t.t2) > ft_min_float(t.t3, t.t4))
		cylinder->normal = cylinder->vector_orientation;
	else	
		get_cylinder_normal(ray, cylinder, t);

	// return (ft_min_float(ft_min_float(t.t1, t.t2), ft_min_float(t.t3, t.t4)));

	
	// *****************	vanaf hier is code er alleen om caps andere kleurtjes te geven voor de duidelijkheid	

	float	small;
	float	small1;
	small = ft_min_float(t.t1, t.t2);
	small1 = ft_min_float(t.t3, t.t4);
	if (small1 < small)		
	{	

		if (t.t3 < t.t4)
			cylinder->color.y = 255;			
		else
			cylinder->color.z = 255;

	}
	return (ft_min_float(small, small1));
}
