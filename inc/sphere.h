/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbedaux <jbedaux@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:52:28 by jbedaux       #+#    #+#                 */
/*   Updated: 2022/09/28 17:08:02 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include <stdbool.h>
# include "main.h"
# include "ray_trace.h"

typedef struct s_quadratic {
	double	a;
	double	b;
	double	c;
	double	discriminant;
}	t_quadratic;

bool	sphere_intersect(t_sphere sphere, t_intersection *intersection);

#endif
