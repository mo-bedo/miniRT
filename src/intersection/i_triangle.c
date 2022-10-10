
#include "main.h"
#include "ray_trace/rt_.h"
#include "utils/u_vector_math.h"
#include "utils/u_vector_operators.h"

float	get_triangle_intersection(t_ray ray)						   
{
	float EPSILON = 0.0000001;

	t_triangle triangle;

	triangle.ab.x = 1;
	triangle.ab.y = 1;
	triangle.ab.z = 6;

	triangle.bc.x = 10;
	triangle.bc.y = 1;
	triangle.bc.z = 5;

	triangle.ca.x = 2;
	triangle.ca.y = 20;
	triangle.ca.z = 5;


	t_xyz	vertex0 = triangle.ab;
	t_xyz	vertex1 = triangle.bc;
	t_xyz	vertex2 = triangle.ca;
	t_xyz	edge1, edge2, h, s, q;
	float	a,f,u,v;

	edge1 = substract_vectors(vertex1, vertex0);
    edge2 = substract_vectors(vertex2, vertex0);
    h = cross(ray.direction, edge2);
    a = get_dot_product(edge1, h);
	
		

    if (a > -EPSILON && a < EPSILON)
        return (RAY_T_MAX);    // This ray is parallel to this triangle.
    f = 1.0/a;
    s = substract_vectors(ray.origin, vertex0);
    u = f * get_dot_product(s, h);
    if (u < 0.0 || u > 1.0)
        return (RAY_T_MAX);
    q = cross(s, edge1);
    v = f * get_dot_product(ray.direction, q);
    if (v < 0.0 || u + v > 1.0)
        return (RAY_T_MAX);
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * get_dot_product(edge2, q);

    if (t > EPSILON) // ray intersection
    {
         return (t);
    }
    else // This means that there is a line intersection but not a ray intersection.
        return (RAY_T_MAX);
}