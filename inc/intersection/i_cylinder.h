/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:28 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/16 16:37:43 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_CYLINDER_H
# define I_CYLINDER_H

# include <stdbool.h>
# include "main.h"
# include "ray_trace/rt_.h"

void	get_cylinder_normal(t_object *object);
float	get_intersect_with_cap_planes(t_ray ray, t_object cylinder, float flag);
float	get_intersection_ray_cylinder(t_ray ray, t_object *cylinder);

#endif
