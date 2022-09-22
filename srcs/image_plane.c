/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweitenb <mweitenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 12:20:58 by mweitenb      #+#    #+#                 */
/*   Updated: 2022/09/21 13:02:37 by mweitenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

// FOV meot / 2 en height en width ook (voor de berekeningen)
// dit geldt alleen bij normal vector iets
// aspect ratio = height / width
// height of image plane = tan tot de macht -1 (FOV)
// dus uitkomst van de atan(FOV) moet x 2 voor de echte hieght.
// omdat r = h / w   is  w = r * h    dus met FOV en aspect ratio kan je het
// image plane maken

t_image	parse_image_plane(double fov, int aspect_ratio)
{
	t_image	screen;

	screen.height = 2 * (atan(fov / 2));
	screen.width = screen.height * aspect_ratio;
	return (screen);
}
