/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cone_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:36:10 by jbedaux           #+#    #+#             */
/*   Updated: 2022/11/09 13:39:40 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_CONE_UTILS_H
# define I_CONE_UTILS_H

# include "main.h"
# include "ray_trace/rt_.h"
# include "intersection/i_utils.h"

t_t4	check_cone_top_bottom(t_ray ray, t_object cone,
	t_t4 t, t_xyz bottom_center);

#endif
