/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_trace.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:20 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 16:02:28 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "ray_trace.h"
#include "plane.h"
#include "sphere.h"
#include <math.h>
// #include "utils/vector_math.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	x = WINDOW_WIDTH/2 + x;
	y = WINDOW_HEIGHT/2 - y - 1;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = &img->addr[offset];
	*(unsigned int *)dst = color;
}

// ======================================================================
//  Linear algebra and helpers.
// ======================================================================

// Conceptually, an "infinitesimaly small" real number.
#define EPSILON 0.001;


// Dot product of two 3D vectors.
double	get_dot_product(t_xyz v1, t_xyz v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// Length of a 3D vector.
double	get_vector_length(t_xyz vector)
{
	return(sqrt(get_dot_product(vector, vector)));
}

float	ft_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_max(float a, float b)
{
	// DEBUG_FLOAT(b);
	if (a > b)
		return (a);
	return (b);
}

// Computes k * vec.
t_xyz	multiply_vectors(double number, t_xyz vector)
{
	vector.x *= number;
	vector.y *= number;
	vector.z *= number;
	return (vector);
}

// Computes v1 + v2.
t_xyz	add_vectors(t_xyz v1, t_xyz v2)
{
	t_xyz	add;

	add.x = v1.x + v2.x;
	add.y = v1.y + v2.y;
	add.z = v1.z + v2.z;
	return (add);
}

// Computes v1 - v2.
t_xyz	substract_vectors(t_xyz v1, t_xyz v2)
{
	t_xyz	sub;

	sub.x = v1.x - v2.x;
	sub.y = v1.y - v2.y;
	sub.z = v1.z - v2.z;
	return (sub);
}

// Clamps a color to the canonical color range.
static int	create_color(int transparancy, int red, int green, int blue)
{
	return (transparancy << 24 | red << 16 | green << 8 | blue);
}

int	clamp_color(t_xyz rgb)
{
	t_rgb	color;
	color.red = (int)ft_min(255, ft_max(0, rgb.x));
	color.green = (int)ft_min(255, ft_max(0, rgb.y));
	color.blue = (int)ft_min(255, ft_max(0, rgb.z));
	return (create_color(1, color.red, color.green, color.blue));
}

// Computes the reflection of v1 respect to v2.
t_xyz get_reflection_of_vector_1_towards_vector_2(t_xyz v1, t_xyz v2)
{
	return (substract_vectors(multiply_vectors(2*get_dot_product(v1, v2), v2), v1));
}


// ======================================================================
//  A raytracer with diffuse and specular illumination, shadows and reflections.
// ======================================================================

// Converts 2D canvas coordinates to 3D viewport coordinates.
t_xyz CanvasToViewport(t_camera camera, t_xy xy)
{
	t_xyz vector;

	vector.x = xy.x * camera.viewport_size / WINDOW_HEIGHT;
	vector.y = xy.y * camera.viewport_size / WINDOW_HEIGHT;
	vector.z = camera.projection_plane_z;
	return (vector);
}


// Computes the intersection of a ray and a sphere. Returns the values
// of t for the intersections.
t_xy get_intersection_ray_sphere(t_xyz origin, t_xyz direction, t_sphere sphere) {
	t_xyz	oc = substract_vectors(origin, sphere.center);

	double k1 = get_dot_product(direction, direction);
	double k2 = 2*get_dot_product(oc, direction);
	double k3 = get_dot_product(oc, oc) - sphere.radius*sphere.radius;

	double discriminant = k2*k2 - 4*k1*k3;
	t_xy xy;
	xy.x = RAY_T_MAX;
	xy.y = RAY_T_MAX;
	if (discriminant < 0 || k1 == 0)
		return (xy);
	xy.x = (-k2 + sqrt(discriminant)) / (2*k1);
	xy.y = (-k2 - sqrt(discriminant)) / (2*k1);
	return (xy);
}

typedef struct s_closest_intersection
{
	t_sphere	*sphere;
	double		t;
}	t_closest_intersection;


// Find the closest intersection between a ray and the spheres in the scene.
t_closest_intersection ClosestIntersection(t_mlx *mlx, t_xyz origin, t_xyz direction, float min_distance, float max_distance)
{
	t_closest_intersection closest_intersection;
	closest_intersection.t = RAY_T_MAX;
	closest_intersection.sphere = NULL;

	for (int i = 0; i < mlx->o.sp_count; i++)
	{
		t_xy xy = get_intersection_ray_sphere(origin, direction, mlx->o.sp[i]);
		if (xy.x < closest_intersection.t && min_distance < xy.x && xy.x < max_distance)
		{
			closest_intersection.t = xy.x;
			closest_intersection.sphere = &mlx->o.sp[i];
		}
		if (xy.y < closest_intersection.t && min_distance < xy.y && xy.y < max_distance)
		{
			closest_intersection.t = xy.y;
			closest_intersection.sphere = &mlx->o.sp[i];
		}
	}
	return (closest_intersection);
}

double ComputeLighting(t_mlx *mlx, t_xyz point, t_xyz normal, t_xyz view, int specular) {
	double intensity = mlx->ambient_light.lighting_ratio;
	double length_n = get_vector_length(normal);  // Should be 1.0, but just in case...
	double length_v = get_vector_length(view);

	t_xyz	vec_l = substract_vectors(mlx->point_light.xyz, point);
	float	min_distance = EPSILON;
	float	max_distance = 1.0;

	// Shadow check.
	t_closest_intersection blocker = ClosestIntersection(mlx, point, vec_l, min_distance, max_distance);
	if (!blocker.sphere)
	{
		// Diffuse reflection.
		double n_dot_l = get_dot_product(normal, vec_l);
		if (n_dot_l > 0)
			intensity += mlx->point_light.brightness * n_dot_l / (length_n * get_vector_length(vec_l));

		// Specular reflection.
		if (specular != -1) {
			t_xyz vec_r = get_reflection_of_vector_1_towards_vector_2(vec_l, normal);
			double r_dot_v = get_dot_product(vec_r, view);
			if (r_dot_v > 0)
				intensity += mlx->point_light.brightness * pow(r_dot_v / (get_vector_length(vec_r) * length_v), specular);
		}
	}
	return (intensity);
}

// Traces a ray against the set of spheres in the scene.
t_xyz TraceRay(t_mlx *mlx, t_xyz origin, t_xyz direction, float min_distance, float max_distance, int depth)
{
	t_xyz	background_color;
	background_color.x = 0;
	background_color.y = 0;
	background_color.z = 0;
	t_closest_intersection intersection = ClosestIntersection(mlx, origin, direction, min_distance, max_distance);
	// DEBUG_FLOAT(intersection.t);
	if (!intersection.sphere)
		return (background_color);
	// DEBUG_FLOAT(intersection.t);
	t_xyz point = add_vectors(origin, multiply_vectors(intersection.t, direction));
	t_xyz normal = substract_vectors(point, intersection.sphere->center);
	normal = multiply_vectors(1.0 / get_vector_length(normal), normal);

	t_xyz view = multiply_vectors(-1, direction);
	double lighting = ComputeLighting(mlx, point, normal, view, intersection.sphere->specular);
	t_xyz local_color = multiply_vectors(lighting, intersection.sphere->rgb);

	if (intersection.sphere->reflective <= 0 || depth <= 0)
		return (local_color);
	float small_number = EPSILON;

	t_xyz reflected_ray = get_reflection_of_vector_1_towards_vector_2(view, normal);
	t_xyz reflected_color = TraceRay(mlx, point, reflected_ray, small_number, RAY_T_MAX, depth - 1);

	return (add_vectors(multiply_vectors(1 - intersection.sphere->reflective, local_color),
			multiply_vectors(intersection.sphere->reflective, reflected_color)));
}


void ray_trace(t_mlx *mlx)
{
	t_xy xy;

    mlx->o.sp[0].specular = 500;	// rood
    mlx->o.sp[0].reflective = 0.2;
    mlx->o.sp[1].specular = 100;	// groen
    mlx->o.sp[1].reflective = 0.7;
    mlx->o.sp[2].specular = 500;	// blauw
    mlx->o.sp[2].reflective = 0.5;
    mlx->o.sp[3].specular = 1000;	// geel
    mlx->o.sp[3].reflective = 0.6;	
	mlx->camera.viewport_size = 1;
	mlx->camera.projection_plane_z = 1;
	int recursion_depth = 3;

	for (int x = -WINDOW_WIDTH/2; x < WINDOW_WIDTH/2; x++)
	{
		for (int y = -WINDOW_HEIGHT/2; y < WINDOW_HEIGHT/2; y++)
		{
			xy.x = x;
			xy.y = y;
			t_xyz direction = CanvasToViewport(mlx->camera, xy);
			t_xyz color = TraceRay(mlx, mlx->camera.origin_point, direction, 1, RAY_T_MAX, recursion_depth);
			my_mlx_pixel_put(&mlx->img, x, y, clamp_color(color));
		}
	}
    mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
}

