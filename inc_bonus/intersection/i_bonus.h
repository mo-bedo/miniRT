/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_bonus.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/13 14:44:22 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_BONUS_H
# define I_BONUS_H

# include "main_bonus.h"
# include "intersection/i_plane_bonus.h"
# include "intersection/i_sphere_bonus.h"
# include "intersection/i_cylinder_bonus.h"
# include "intersection/i_cone_bonus.h"

t_object	get_closest_intersection(t_mlx mlx, t_ray ray,
				float max_distance);

#endif
