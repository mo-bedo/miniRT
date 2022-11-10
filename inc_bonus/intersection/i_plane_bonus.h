/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_plane_bonus.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:28 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:06:59 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_PLANE_BONUS_H
# define I_PLANE_BONUS_H

# include <stdbool.h>
# include "main_bonus.h"
# include "ray_trace/rt_bonus.h"

float	get_intersection_ray_plane(t_ray ray, t_object plane);

#endif
