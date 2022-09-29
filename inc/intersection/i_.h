/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:44:21 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I__H
# define I__H

# include "main.h"
# include "intersection/i_plane.h"
# include "intersection/i_sphere.h"

typedef struct s_intersection {
	t_ray		ray;
	double		t;
	t_sphere	*sphere;
	t_plane		*plane;
}	t_intersection;

t_closest_object	get_closest_intersection(t_mlx *mlx, t_ray ray,
						float min_distance, float max_distance);

#endif
