/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_trace.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 17:42:08 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/29 19:41:36 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACE_H
# define RAY_TRACE_H

# include "main.h"

// je wilt niet dat een ray die 'bounct' van een object tegen zichzelf kaatst
# define RAY_T_MIN 0.0001f

// zeer onwaarschijnlijk dat iets verder dan deze max is
# define RAY_T_MAX 1.0e30f

typedef struct s_ray {
	t_xyz	direction;
	t_xyz	origin;
	double	t_max;
}	t_ray;

void	ray_trace(t_mlx *mlx);

#endif
