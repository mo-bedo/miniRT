/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by mweitenb          #+#    #+#             */
/*   Updated: 2022/09/23 17:43:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_SCENE_H
#define PARSE_SCENE_H

#include "main.h"

int		parse_int(char **str, int min, int max);
float	parse_float(char **str, int min, int max);
t_rgb	parse_rgb(char **str);
t_xyz	parse_xyz(char **str, int min, int max);

enum e_xyz_range {
	MIN_COLOR			= 0,
	MAX_COLOR			= 255,
	MIN_LiGHTING_RATIO	= 0,
	MAX_LiGHTING_RATIO	= 1,
	MIN_XYZ				= -1800,
	MAX_XYZ				= 1800,
	MIN_3D				= -1,
	MAX_3D				= 1,
	MIN_BRIGHTNESS		= 0,
	MAX_BRIGHTNESS		= 1,
	MIN_DIAMETER		= 0,
	MAX_DIAMETER		= 100,
	MIN_CY_HEIGHT		= 0,
	MAX_CY_HEIGHT		= 100
};

#endif
