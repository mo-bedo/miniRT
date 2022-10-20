/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   u_identify.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:36:14 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/10/13 21:25:53 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_IDENTIFY_H
# define U_IDENTIFY_H

# include "main.h"

int     ft_strlen(char *s);
bool	ft_is_digit(int c);
bool	ft_is_space(char c);
bool    is_cap(t_xyz normal, t_xyz orientation);

#endif
