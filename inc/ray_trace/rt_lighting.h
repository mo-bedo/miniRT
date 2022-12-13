#ifndef RT_LIGHTING_H
# define RT_LIGHTING_H

# include "main.h"

t_xyz	compute_reflected_ray(t_xyz ray_direction, t_xyz normal);
void	compute_lighting(t_object *object, t_mlx *mlx, t_xyz view);

#endif
