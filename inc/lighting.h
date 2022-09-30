/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/30 18:12:43 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "main.h"

t_xyz	compute_reflected_ray(t_xyz ray_direction, t_xyz normal);
double	compute_lighting(t_mlx *mlx, t_xyz view, t_closest_object object);

#endif
