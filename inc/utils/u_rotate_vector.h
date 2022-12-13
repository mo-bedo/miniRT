#ifndef U_ROTATE_VECTOR_H
# define U_ROTATE_VECTOR_H

# include "main.h"

t_xyz	rotate_vector(t_xyz vector,
			t_xyz old_orientation, t_xyz new_orientation);
t_xyz	rotate_vector_by_angle(t_xyz vector, t_xyz orientation, float angle);

#endif
