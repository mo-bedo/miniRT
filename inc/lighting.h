/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:00:49 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "main.h"

t_xyz	get_reflection_of_vector_1_towards_vector_2(t_xyz v1, t_xyz v2);
double	compute_lighting(t_mlx *mlx, t_xyz normal,
			t_xyz view, t_closest_object object);

#endif
