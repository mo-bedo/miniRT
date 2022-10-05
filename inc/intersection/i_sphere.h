/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_sphere.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:28 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:07:08 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_SPHERE_H
# define I_SPHERE_H

# include <stdbool.h>
# include "main.h"
# include "ray_trace/rt_.h"

float	get_intersection_ray_sphere(t_ray ray, t_sphere sphere);

#endif
