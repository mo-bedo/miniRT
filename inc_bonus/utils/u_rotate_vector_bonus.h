/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_rotate_vector_bonus.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/05 13:54:58 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_ROTATE_VECTOR_BONUS_H
# define U_ROTATE_VECTOR_BONUS_H

# include "main_bonus.h"

t_xyz	rotate_vector(t_xyz vector,
			t_xyz old_orientation, t_xyz new_orientation);
t_xyz	rotate_vector_by_angle(t_xyz vector, t_xyz orientation, float angle);

#endif
