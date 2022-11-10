/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_sphere_bonus.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:28 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/11/07 16:38:07 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_SPHERE_BONUS_H
# define I_SPHERE_BONUS_H

# include <stdbool.h>
# include "main_bonus.h"
# include "ray_trace/rt_bonus.h"

float	get_intersection_ray_sphere(t_ray ray, t_object *sphere);

#endif
