/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_trace.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 19:04:14 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACE_H
# define RAY_TRACE_H

# include "main.h"

// je wilt niet dat een ray die 'bounct' van een object tegen zichzelf kaatst
# define RAY_T_MIN 0.0001f

// zeer onwaarschijnlijk dat iets verder dan deze max is
# define RAY_T_MAX 1.0e30f

typedef struct s_closest_object
{
	int			object;
	t_xyz		position;
	double		t;
	t_xyz		center;
	t_xyz		vector_orientation;
	float		radius;
	float		height;
	t_xyz		color;
	int			specular;
	float		reflective;
	t_xyz		normal;
}	t_closest_object;

typedef struct s_ray {
	t_xyz				direction;
	t_xyz				origin;
	t_xyz				view;
	double				t_max;
	t_closest_object	object;
}	t_ray;

t_xyz	get_color(t_mlx *mlx, t_ray ray, int recursion_depth);
void	ray_trace(t_mlx *mlx);

#endif
