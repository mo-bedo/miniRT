/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_lighting_bonus.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/13 14:01:01 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LIGHTING_BONUS_H
# define RT_LIGHTING_BONUS_H

# include "main_bonus.h"

t_xyz	compute_reflected_ray(t_xyz ray_direction, t_xyz normal);
void	compute_lighting(t_object *object, t_mlx *mlx, t_xyz view);

#endif
