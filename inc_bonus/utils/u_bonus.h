/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_bonus.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/11/09 19:01:43 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_BONUS_H
# define U_BONUS_H

# include "main_bonus.h"
# include "utils/u_compare_bonus.h"
# include "utils/u_conversion_bonus.h"
# include "utils/u_identify_bonus.h"
# include "utils/u_rotate_vector_bonus.h"
# include "utils/u_vector_math_bonus.h"
# include "utils/u_vector_operators_bonus.h"

void	ft_putstr(char *s);
void	*ft_calloc(size_t count, size_t size);
void	initialize_quaternion(t_wxyz *q, float w, t_xyz vector);
t_wxyz	multiply_quaternion(t_wxyz q1, t_wxyz q2);

#endif
