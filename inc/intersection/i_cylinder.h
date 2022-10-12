/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:28 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/12 12:07:53 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_CYLINDER_H
# define I_CYLINDER_H

# include <stdbool.h>
# include "main.h"
# include "ray_trace/rt_.h"

void	get_cylinder_normal(t_object *object);
float	get_intersection_ray_cylinder(t_ray ray, t_object *cylinder);

#endif
