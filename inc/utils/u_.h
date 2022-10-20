/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:26:26 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U__H
# define U__H

# include "main.h"
# include "utils/u_compare.h"
# include "utils/u_conversion.h"
# include "utils/u_identify.h"
# include "utils/u_rotate_vector.h"
# include "utils/u_vector_math.h"
# include "utils/u_vector_operators.h"

void	ft_putstr(char *s);
void	*ft_calloc(size_t count, size_t size);
t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera, int x, int y);
void	initialize_quaternion(t_wxyz *q, float w, float x, float y, float z);
t_wxyz	multiply_quaternion(t_wxyz q1, t_wxyz q2);

#endif
