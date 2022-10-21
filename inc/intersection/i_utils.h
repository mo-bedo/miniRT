/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_utils.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:42:08 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/17 12:07:42 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_UTILS_H
# define I_UTILS_H

# include "main.h"
# include "ray_trace/rt_.h"

typedef struct s_t4
{
	float	t1;
	float	t2;
	float	t3;
	float	t4;
}	t_t4;

t_t4	check_t_values(t_t4 t);
t_t4	quadratic_formula(t_xyz input1, t_xyz input2,
			float input3, float input4);
float	get_intersect_with_cap_planes(t_ray ray, t_object cylinder, float flag);

#endif
