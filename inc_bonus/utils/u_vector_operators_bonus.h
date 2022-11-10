/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_vector_operators_bonus.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:36:14 by mweitenb          #+#    #+#             */
/*   Updated: 2022/10/16 15:29:42 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_VECTOR_OPERATORS_BONUS_H
# define U_VECTOR_OPERATORS_BONUS_

# include "main_bonus.h"

t_xyz	add_vectors(t_xyz v1, t_xyz v2);
t_xyz	subtract_vectors(t_xyz v1, t_xyz v2);
t_xyz	get_negative_vector(t_xyz v1);
t_xyz	multiply_vector(t_xyz vector, float number);
t_xyz	divide_vector(t_xyz vector, float number);

#endif 		
