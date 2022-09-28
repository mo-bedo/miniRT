/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unused_code.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/28 16:47:33 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "main.h"
// #include <math.h>
// #include <stdbool.h>

// #include "shape.h"
// #include "camera.h"
// #include "intersect.h"
// #include "main.h"
// #include "vector_math.h"

// //	Calculeert dan het punt op de ray als je waarde t weet
// //	van r = p + td
// t_xyz	get_coordinates_of_ray_at_distance(t_ray ray, double distance)
// {
// 	t_xyz	math;

// 	math = multiply_vector(ray.direction, distance);
// 	return (add_vectors(ray.origin_point, math));
// }

// // geeft aan of de ray iets raakt
// bool	ray_is_intersecting_with_object(t_intersection intersection)
// {
// 	return (intersection.sphere != NULL);
// }

// // als de ray iets raakt geeft dit de positie waar hij dat doet
// t_xyz	get_coordinates_of_intersection(t_intersection intersection)
// {
// 	t_xyz	point;

// 	point = get_coordinates_of_ray_at_distance(
// 			intersection.ray, intersection.t);
// 	return (point);
// }

// // FOV meot / 2 en height en width ook (voor de berekeningen)
// // dit geldt alleen bij normal vector iets
// // aspect ratio = height / width
// // height of image plane = tan tot de macht -1 (FOV)
// // dus uitkomst van de atan(FOV) moet x 2 voor de echte hieght.
// // omdat r = h / w   is  w = r * h    dus met FOV en aspect ratio kan je het
// // image plane maken
// t_image	parse_image_plane(double fov, int aspect_ratio)
// {
// 	t_image	screen;

// 	screen.height = 2 * (atan(fov / 2));
// 	screen.width = screen.height * aspect_ratio;
// 	return (screen);
// }

// // raakt ray de sphere ja of nee, zou door alle objecten moeten loopen en dan
// // returnen zodra hij de eerste raakt
// bool	plane_does_intersect(t_plane plane, t_ray ray)
// {
// 	double	d_dot_n;
// 	double	t;

// 	d_dot_n = get_dot_product(ray.direction, plane.vector_orientation);
// 	if (d_dot_n == 0.0)
// 		return (false);
// 	//// vindt het punt van intersectie
// 	t = get_dot_product(substract_vectors(plane.xyz, \
// 			ray.origin_point), plane.vector_orientation) / d_dot_n;
// 	if (t < RAY_T_MIN || t > ray.t_max)
// 		return (false);
// 	return (true);
// }

// // raakt ray de sphere ja of nee, zou door alle objecten moeten loopen en dan
// // returnen zodra hij de eerste raakt
// bool	sphere_does_intersect(t_sphere sphere, t_ray ray)
// {
// 	t_ray	local_ray;
// 	local_ray = ray;
// 	local_ray.origin_point = substract_vectors(local_ray.origin_point, sphere.centre);
// 	// quadratic
// 	double	a = get_2d_vector_magnitude(local_ray.direction);
// 	double	b = 2 * get_dot_product(local_ray.direction, local_ray.origin_point);
// 	double	c = get_2d_vector_magnitude(local_ray.origin_point) - (sphere.radius * sphere.radius);
// 	double	discriminant = (b * b) - 4 * a * c;
// 	if (discriminant < 0.0) //// dan raakt ray de sphere niet
// 		return (false);
// 	double t1 = (-b - sqrt(discriminant)) / (2 * a);
// 	if (t1 > RAY_T_MIN && t1 < ray.t_max)
// 		return (true);
// 	double t2 = (-b + sqrt(discriminant)) / (2 * a);
// 	if (t2 > RAY_T_MIN && t2 < ray.t_max)
// 		return (true);
// 	return (false);
// }
