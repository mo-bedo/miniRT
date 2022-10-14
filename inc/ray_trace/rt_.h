/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/13 15:12:06 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT__H
# define RT__H

# include "main.h"

typedef struct s_ray {
	t_xyz		direction;
	t_xyz		origin;
	t_object	object;
}	t_ray;

t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera, int x, int y);
t_ray	compute_ray(t_mlx mlx, t_xyz origin, t_xyz direction);
t_xyz	get_color(t_mlx *mlx, t_ray ray, int recursion_depth);
void	ray_trace(t_mlx *mlx);

#endif
