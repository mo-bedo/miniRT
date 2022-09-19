#ifndef MINIRT_H
#define MINIRT_H

typedef struct s_data {
	void	*img;
	char	*address;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vec {
	int	x;
	int	y;
}	t_vec;

#endif
