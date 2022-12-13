#ifndef U_CONVERSION_H
# define U_CONVERSION_H

# include "main.h"

int		ft_char_to_digit(int c);
int		ft_atoi(const char *str);
float	ft_atof(const char *str);
t_xyz	convert_2d_canvas_to_3d_coordinates(t_camera camera, int x, int y);

#endif
