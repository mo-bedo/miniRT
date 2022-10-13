/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_utils.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/10/13 15:23:19 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_UTILS_H
# define I_UTILS_H

# include "main.h"

typedef struct s_t4
{
	float	t1;
	float	t2;
	float	t3;
	float	t4;
}	t_t4;

t_t4	check_t_values(t_t4 t);
t_t4	quadratic_formula(t_xyz input1, t_xyz input2,
			double input3, double input4);

#endif
