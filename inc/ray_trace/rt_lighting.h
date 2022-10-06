/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_lighting.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/05 20:04:30 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LIGHTING_H
# define RT_LIGHTING_H

# include "main.h"

t_xyz	compute_reflected_ray(t_xyz ray_direction, t_xyz normal);
t_xyz	compute_lighting(t_mlx *mlx, t_xyz view, t_closest_object object);

#endif
