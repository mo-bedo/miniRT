/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylinder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:09:16 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/30 13:09:17 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_CYLINDER_H
# define I_CYLINDER_H

# include "main.h"
# include "ray_trace.h"

float	get_intersection_ray_cylinder(t_ray ray, t_cylinder);

#endif 		// I_CYLINDER_H
