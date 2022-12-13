/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_cone_utils_bonus.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 13:36:10 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/09 20:01:10 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_CONE_UTILS_BONUS_H
# define I_CONE_UTILS_BONUS_H

# include "main_bonus.h"
# include "ray_trace/rt_bonus.h"
# include "intersection/i_utils_bonus.h"

t_t4	check_cone_top_bottom(t_ray ray, t_object cone,
			t_t4 t, t_xyz bottom_center);

#endif
