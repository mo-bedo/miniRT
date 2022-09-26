/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:42:08 by jbedaux           #+#    #+#             */
/*   Updated: 2022/09/22 17:42:08 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RAY_TRACE_H
# define RAY_TRACE_H

# include "main.h"
# include "shape.h"

void	ray_trace(t_cam cam, t_plane plane, t_sphere sphere);

#endif

