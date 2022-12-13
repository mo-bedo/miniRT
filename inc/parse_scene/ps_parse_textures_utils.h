#ifndef PS_PARSE_TEXTURES_UTILS_H
# define PS_PARSE_TEXTURES_UTILS_H

# include "main.h"

t_xyz	**allocate_map(int width, int height);
int		ft_strlcpy(char *dst, char *src, int size);
char	*get_path(char *input);
int		get_length_of_file(char *path);

#endif
