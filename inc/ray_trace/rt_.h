#ifndef RT__H
# define RT__H

# include "main.h"

typedef struct s_ray {
	t_xyz		direction;
	t_xyz		origin;
	t_object	object;
}	t_ray;

t_xyz	get_color(t_mlx *mlx, t_ray ray, int recursion_depth);
void	ray_trace(t_mlx *mlx);

#endif
