/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_cylinder.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:28 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:07:17 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_CYLINDER_H
# define I_CYLINDER_H

# include <stdbool.h>
# include "main.h"
# include "ray_trace/rt_.h"

float	get_intersection_ray_cylinder(t_ray ray, t_cylinder cylinder);

#endif
