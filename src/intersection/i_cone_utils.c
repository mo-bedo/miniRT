#include <math.h>

#include "main.h"
#include "intersection/i_utils.h"
#include "ray_trace/rt_.h"
#include "utils/u_vector_math.h"

// dot product is a measure of similarity 
//  1 = same direction
//  0 = at angle of 90 degrees
// -1 = opposite direction

// cone_orientation points from tip of cone to bottom, so:
// if cone_orientation and tip_to_intersect > 0:
// 		ray hits cone below the tip
static bool	intersect_below_tip(t_xyz cone_orientation,
	t_xyz intersect, t_xyz cone_tip)
{
	t_xyz	tip_to_intersect;

	tip_to_intersect = subtract_vectors(intersect, cone_tip);
	if (get_dot_product(cone_orientation, tip_to_intersect) > 0)
		return (true);
	return (false);
}

// cone_orientation points from tip of cone to bottom, so:
// if cone_orientation and bottom_to_intersect < 0:
// 		ray hits cone above the bottom
static bool	intersect_above_bottom(t_xyz cone_orientation,
	t_xyz intersect, t_xyz bottom_center)
{
	t_xyz	bottom_to_intersect;

	bottom_to_intersect = subtract_vectors(intersect, bottom_center);
	if (get_dot_product(cone_orientation, bottom_to_intersect) < 0)
		return (true);
	return (false);
}

// Checks if intersect points are between the top and bottom of cone.
// if (ray hits cone below tip and above center)
// 		ray hits cone
// else
// 		ray goes over/under cone, therefoe t = RAY_T_MAX
t_t4	check_cone_top_bottom(t_ray ray, t_object cone,
	t_t4 t, t_xyz bottom_center)
{
	t_xyz	intersect_1;
	t_xyz	intersect_2;
	t_xyz	cone_tip;

	intersect_1 = add_vectors(ray.origin, multiply_vector(ray.direction, t.t1));
	intersect_2 = add_vectors(ray.origin, multiply_vector(ray.direction, t.t2));
	cone_tip = add_vectors(bottom_center, get_negative_vector(multiply_vector(
					cone.orientation, cone.height)));
	if (!(intersect_above_bottom(cone.orientation, intersect_1, bottom_center)
			&& intersect_below_tip(cone.orientation, intersect_1, cone_tip)))
		t.t1 = RAY_T_MAX;
	if (!(intersect_above_bottom(cone.orientation, intersect_2, bottom_center)
			&& intersect_below_tip(cone.orientation, intersect_2, cone_tip)))
		t.t2 = RAY_T_MAX;
	return (t);
}
