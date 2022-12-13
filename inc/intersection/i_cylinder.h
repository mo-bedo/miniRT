#ifndef I_CYLINDER_H
# define I_CYLINDER_H

# include <stdbool.h>
# include "main.h"
# include "ray_trace/rt_.h"

void	get_cylinder_normal(t_object *object);
float	get_intersect_with_cap_planes(t_ray ray, t_object cylinder, float flag);
float	get_intersection_ray_cylinder(t_ray ray, t_object *cylinder);

#endif
