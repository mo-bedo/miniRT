#ifndef I_UTILS_H
# define I_UTILS_H

# include "main.h"
# include "ray_trace/rt_.h"

typedef struct s_t4
{
	float	t1;
	float	t2;
	float	t3;
	float	t4;
}	t_t4;

t_t4	check_t_values(t_t4 t);
t_t4	quadratic_formula(t_xyz input1, t_xyz input2,
			float input3, float input4);
float	get_intersect_with_cap_planes(t_ray ray, t_object cylinder, float flag);
void	check_if_camera_is_inside_object(t_object *object, t_ray ray);

#endif
