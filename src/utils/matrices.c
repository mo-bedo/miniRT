/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:52:38 by jbedaux           #+#    #+#             */
/*   Updated: 2022/10/05 18:39:35 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"	
#include "utils/matrices.h"

#include <stdio.h>
#include <math.h>

// rotation matrix uitleg
// https://www.youtube.com/watch?v=7j5yW5QDC2U&t=27s

//		T = theta
// 		 -				   -
//	   	| cos T   -sin T	|
//		| sin T	   cos T	|
//		|  0		0		|
//		 -				   -
//
//												-1
// angle tussen 2 vectors berekenen je door cosˆ   (dot van vector_normal,
// 													dot van vector_normal 2)
// cos tot de macht -1 == acos()
// double	get_angle_between_vectors(t_xyz v1, t_xyz v2)
// {
// 	t_xyz	unit_v1;
// 	t_xyz	unit_v2;
// 	double	angle;

// 	unit_v1 = normalize_vector(v1);
// 	unit_v2 = normalize_vector(v2);
// 	angle = acos(get_dot_product(unit_v1, unit_v2));
// 	return (angle);
// }




//////////////////////////// //////////////////////////// //////////////////////////// 
//////////////////////////// MATRIX MATH //////////////////////////// 
//////////////////////////// //////////////////////////// //////////////////////////// 

/* 	Matrix multiplying (tested and works as expected)
	  -	    -      -	  -			 -                                        -
	| a1  b1 |  * | a2  b2 |    = 	| (dot(a1 b1, a2 c2))    dot(a1 b1, b2 d2) |   
	| c1  d1 |    | c2  d2 |		| (dot(c1 d1, a2 c2))    dot(c1 d1, b2 d2) |
	 -      -      -      -			 -                						  - 

	  -	    -       -	    -        -                                  -
	|  1    2 |  * | 5     6 |    =	| (1 * 5 + 2 * 6)    (1 * 6 + 2 * 8) |   
	|  3    4 |    | 7     8 |		| (3 * 7 + 4 * 8)    (3 * 6 + 4 * 8) |
	 -      -      -       -		 -         						    - 
	 
	You can mulitply matrices by getting the dot_product of the rows with the columns.
	So dotproduct of row1 and column 1, then row1 column2, row1 column3 etc.
	So every row loops through the columns. 
	The order of multiplacation matters!!! So A*B != B*A
*/
t_matrix4	multiply_matrices(t_matrix4 lhs, t_matrix4 rhs)
{
	int			i;
	int			j;
	int			k;
	t_matrix4	ret;
	
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				ret.value[i][j] += lhs.value[i][k] * rhs.value[k][j];
				k++;
			}
			j++;
		}	
		i++;
	}
	return (ret);
}

/*
	 -	    -      -	  -			 -                -
	| a1  b1 |  + | a2  b2 |    = 	| (a1+a2)  (b1+b2) |   
	| c1  d1 |    | c2  d2 |		| (c1+c2)  (d1+d2) |
	 -      -      -      -			 -                - 
*/
t_matrix4	add_matrices(t_matrix4 lhs, t_matrix4 rhs)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			lhs.value[i][j] += rhs.value[i][j];
			j++;
		}
		i++;
	}
}

/* negative matrix: 
	    A 				-A
	 -	      -   	 -	     -		
	|  3     5 |  	| -3   -5 |   
	| -2    23 |    |  2  -23 |	
	 -        -      -       -	
*/
t_matrix4	negative_matrix(t_matrix4 obj)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			obj.value[i][j] *= -1;
			j++;
		}
		i++;
	}
}

/* 
	Same logic as addding matrices. Subtracting matrices is also
	defined as adding a negative matrix.
*/	
t_matrix4	subtract_matrices(t_matrix4 lhs, t_matrix4 rhs)
{
	return (add_matrices(lhs, negative_matrix(rhs)));	
}



// matrix.value[row][column]
t_matrix4	set_matrix_element(t_matrix4 obj, int row, int colomn, float value)
{
	return obj;
}

// Maakt matrix aan die world coord -> local coord transform doet
t_matrix4	create_transform_matrix(t_xyz translation_vector, 
										t_xyz rotate, t_xyz scale)
{
	t_matrix4	translate_matrix;
	t_matrix4	rotate_matrix_X;
	t_matrix4	rotate_matrix_Y;
	t_matrix4	rotate_matrix_Z;
	t_matrix4	scale_matrix;
	
	translate_matrix = set_matrix_to_identity(translate_matrix);
	rotate_matrix_X = set_matrix_to_identity(rotate_matrix_X);
	rotate_matrix_Y = set_matrix_to_identity(rotate_matrix_Y);
	rotate_matrix_Z = set_matrix_to_identity(rotate_matrix_Z);
	translate_matrix = set_matrix_to_identity(translate_matrix);
	
	
}

/*	Rotate om X, met theta = hoek die je wilt draaien over de as		
	 -              - 	
	| 1   0    0   0 |	 
	| 0 cosT -sinT 0 |			
	| 0 sinT  cosT 0 |	
	| 0   0    0   1 |  	
	 -		        -	 
*/
t_matrix4	set_rotation_matrix_x_axis(t_matrix4 obj, float theta)
{
	obj = set_matrix_to_identity(obj);		// kan weg gelaten worden als het sneller (ook in andere 2 rotatie functie), staat er nu nog in om bugs te voorkomen
	obj.value[1][1] = cos(theta); 
	obj.value[1][2] = -sin(theta);
	obj.value[2][1] = sin(theta);
	obj.value[2][2] = cos(theta);
	return (obj);
}

/*	Rotate om Y, met T = hoek die je wilt draaien over de as	
	 -              - 	
	|  cosT 0 sinT  0 |	 
	|    0  1   0   0 |			
	| -sinT 0 cosT  0 |	
	|    0  0   0   1 |  	
	 -		         -	 
*/
t_matrix4	set_rotation_matrix_y_axis(t_matrix4 obj, float theta)
{
	obj = set_matrix_to_identity(obj);
	obj.value[0][0] = cos(theta); 
	obj.value[0][2] = sin(theta);
	obj.value[2][0] = -sin(theta);
	obj.value[2][2] = cos(theta);
	return (obj);
}

t_matrix4	set_scale_matrix(t_matrix4 obj, float scaleX, float scaleY, float scaleZ)
{
	obj.value[0][0] = scaleX; 
	obj.value[1][1] = scaleY; 
	obj.value[2][2] = scaleZ; 
	return (obj);
}

/*	Rotate om Z, met T = hoek die je wilt draaien over de as	
	 -              - 	
	|  cosT -sinT 0  0 |	 
	|  sinT  cosT 0  0 |			
	|   0      0  1  0 |	
	|   0      0  0  1 |  	
	 -		         -	 
*/
t_matrix4	set_rotation_matrix_z_axis(t_matrix4 obj, float theta)
{
	obj = set_matrix_to_identity(obj);
	obj.value[0][0] = cos(theta); 
	obj.value[0][1] = -sin(theta); 
	obj.value[1][0] = sin(theta);
	obj.value[1][1] = cos(theta);
	return (obj);
}

/*
		 -         - 
		| 0 0 0 t.x |	 
		| 0 0 0 t.y |			
	A = | 0 0 0 t.z |
		| 0 0 0 0   |	
		 -		   -	 
*/
t_matrix4	set_translation_matrix(t_matrix4 obj, t_xyz translation)
{	
	obj.value[0][3] = translation.x;
	obj.value[1][3] = translation.y;
	obj.value[2][3] = translation.z;
	return (obj);
}

/*		 _       _ 
		| 1 0 0 0 |	 
		| 0 1 0 0 |			
		| 0 0 1 0 |
		| 0 0 0 1 |	
		 _		 _
stel matrix in als identy matrix		 
*/
t_matrix4	set_matrix_to_identity(t_matrix4 obj)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (j == i)
				obj.value[i][j] = 1;
			else
				obj.value[i][j] = 0;
			j++;	
		}
		i++;
	}
	return (obj);
}

void	print_matrix(t_matrix4 obj)
{
	printf("		0	1	2	 3\n");
	printf("   0  \t%.0f\t%.0f\t%.0f\t%.0f\n", obj.value[0][0], obj.value[0][1], obj.value[0][2], obj.value[0][3]);
	printf("   1  \t%.0f\t%.0f\t%.0f\t%.0f\n", obj.value[1][0], obj.value[1][1], obj.value[1][2], obj.value[1][3]);
	printf("   2  \t%.0f\t%.0f\t%.0f\t%.0f\n", obj.value[2][0], obj.value[2][1], obj.value[2][2], obj.value[2][3]);
	printf("   3  \t%.0f\t%.0f\t%.0f\t%.0f\n\n", obj.value[3][0], obj.value[3][1], obj.value[3][2], obj.value[3][3]);
		
}


int main()
{
	t_matrix4 c;
	t_matrix4 b;
	t_matrix4 m;
	
	int x = 3;
	for (int i = 0; i < 4; i++)
	{
		x++;
		for (int j = 0; j < 4; j++)
		{
			x+= 3; 
			b.value[i][j] = x;
		}
	
	}
	

 	x = 9;
	for (int i = 0; i < 4; i++)
	{
		x++;
		for (int j = 0; j < 4; j++)
		{
			x += 2; 
			c.value[i][j] = x;
		}
		
	}
	
	// print_matrix(b);
	// print_matrix(c);


	// *m= multiply_matrices(*b, *c);
	m= multiply_matrices(b, c);
	// print_matrix(*m);
	print_matrix(m);
	

}