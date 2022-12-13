#ifndef U_VECTOR_OPERATORS_H
# define U_VECTOR_OPERATORS_H

# include "main.h"

t_xyz	add_vectors(t_xyz v1, t_xyz v2);
t_xyz	subtract_vectors(t_xyz v1, t_xyz v2);
t_xyz	get_negative_vector(t_xyz v1);
t_xyz	multiply_vector(t_xyz vector, float number);
t_xyz	divide_vector(t_xyz vector, float number);

#endif 		
