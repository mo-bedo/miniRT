/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_conversion_bonus.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/09 19:01:46 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_CONVERSION_BONUS_H
# define U_CONVERSION_BONUS_H

# include "main_bonus.h"

int		ft_char_to_digit(int c);
int		ft_atoi(const char *str);
float	ft_atof(const char *str);
t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera, int x, int y);

#endif
