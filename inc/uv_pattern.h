/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interaction.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 17:42:31 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 20:11:42 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_PATTERN_H
# define UV_PATTERN_H

#include "ray_trace/rt_.h"

enum e_uv_codes{
	U			= 0,
	V			= 1
};

t_xyz	get_checkers_color(t_closest_object object);

#endif