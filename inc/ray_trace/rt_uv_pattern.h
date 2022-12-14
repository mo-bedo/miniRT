/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_uv_pattern.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 17:42:31 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 14:43:29 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_UV_PATTERN_H
# define RT_UV_PATTERN_H

# include "ray_trace/rt_.h"

t_xyz	get_uv_pattern(int pattern, t_object object);

#endif