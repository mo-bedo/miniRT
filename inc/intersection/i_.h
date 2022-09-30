/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 19:17:58 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I__H
# define I__H

# include "main.h"
# include "intersection/i_plane.h"
# include "intersection/i_sphere.h"

t_closest_object	get_closest_intersection(t_objects o, t_ray ray,
						float min_distance, float max_distance);

#endif
