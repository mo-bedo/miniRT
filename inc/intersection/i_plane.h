/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_plane.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:28 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:43:55 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_PLANE_H
# define I_PLANE_H

# include <stdbool.h>
# include "main.h"
# include "ray_trace.h"

float	get_intersection_ray_plane(t_ray ray, t_plane plane);

#endif
