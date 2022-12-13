#ifndef PS__H
# define PS__H

# include "main.h"

bool	has_valid_extension(char *filename, char *valid_ext);
void	parse_scene(t_mlx	*mlx, int argc, char *input);

#endif
