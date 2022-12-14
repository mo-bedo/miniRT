/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/13 14:44:22 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I__H
# define I__H

# include "main.h"
# include "intersection/i_plane.h"
# include "intersection/i_sphere.h"
# include "intersection/i_cylinder.h"
# include "intersection/i_cone.h"

t_object	get_closest_intersection(t_mlx mlx, t_ray ray,
				float max_distance);

#endif
