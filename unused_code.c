/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbedaux <jbedaux@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:20:58 by mweitenb          #+#    #+#             */
/*   Updated: 2022/10/12 15:54:27 by jbedaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "main.h"
// #include <math.h>
// #include <stdbool.h>

// #include "shape.h"
// #include "camera.h"
// #include "intersect.h"
// #include "main.h"
// #include "vector_math.h"

// //	Calculeert dan het punt op de ray als je waarde t weet
// //	van r = p + td
// t_xyz	get_coordinates_of_ray_at_distance(t_ray ray, double distance)
// {
// 	t_xyz	math;

// 	math = multiply_vector(ray.direction, distance);
// 	return (add_vectors(ray.origin, math));
// }

// // geeft aan of de ray iets raakt
// bool	ray_is_intersecting_with_object(t_intersection intersection)
// {
// 	return (intersection.sphere != NULL);
// }

// // als de ray iets raakt geeft dit de positie waar hij dat doet
// t_xyz	get_coordinates_of_intersection(t_intersection intersection)
// {
// 	t_xyz	point;

// 	point = get_coordinates_of_ray_at_distance(
// 			intersection.ray, intersection.t);
// 	return (point);
// }

// // FOV meot / 2 en height en width ook (voor de berekeningen)
// // dit geldt alleen bij normal vector iets
// // aspect ratio = height / width
// // height of image plane = tan tot de macht -1 (FOV)
// // dus uitkomst van de atan(FOV) moet x 2 voor de echte hieght.
// // omdat r = h / w   is  w = r * h    dus met FOV en aspect ratio kan je het
// // image plane maken
// t_image	parse_image_plane(double fov, int aspect_ratio)
// {
// 	t_image	screen;

// 	screen.height = 2 * (atan(fov / 2));
// 	screen.width = screen.height * aspect_ratio;
// 	return (screen);
// }

// // raakt ray de sphere ja of nee, zou door alle objecten moeten loopen en dan
// // returnen zodra hij de eerste raakt
// bool	plane_does_intersect(t_plane plane, t_ray ray)
// {
// 	double	d_dot_n;
// 	double	t;

// 	d_dot_n = get_dot_product(ray.direction, plane.orientation);
// 	if (d_dot_n == 0.0)
// 		return (false);
// 	//// vindt het punt van intersectie
// 	t = get_dot_product(substract_vectors(plane.xyz, \
// 			ray.origin), plane.orientation) / d_dot_n;
// 	if (t < RAY_T_MIN || t > ray.t_max)
// 		return (false);
// 	return (true);
// }

// // raakt ray de sphere ja of nee, zou door alle objecten moeten loopen en dan
// // returnen zodra hij de eerste raakt
// bool	sphere_does_intersect(t_sphere sphere, t_ray ray)
// {
// 	t_ray	local_ray;
// 	local_ray = ray;
// 	local_ray.origin = substract_vectors(local_ray.origin, sphere.centre);
// 	// quadratic
// 	double	a = get_2d_vector_magnitude(local_ray.direction);
// 	double	b = 2 * get_dot_product(local_ray.direction, local_ray.origin);
// 	double	c = get_2d_vector_magnitude(local_ray.origin) - (sphere.radius * sphere.radius);
// 	double	discriminant = (b * b) - 4 * a * c;
// 	if (discriminant < 0.0) //// dan raakt ray de sphere niet
// 		return (false);
// 	double t1 = (-b - sqrt(discriminant)) / (2 * a);
// 	if (t1 > RAY_T_MIN && t1 < ray.t_max)
// 		return (true);
// 	double t2 = (-b + sqrt(discriminant)) / (2 * a);
// 	if (t2 > RAY_T_MIN && t2 < ray.t_max)
// 		return (true);
// 	return (false);
// }

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

// cross product
// is a measure of difference
//  0 = same direction
//  1 = at angle of 90 degrees
// -1 = opposite direction
// t_xyz	get_cross_product(t_xyz v1, t_xyz v2)
// {
// 	t_xyz	cross;

// 	cross.x = v1.y * v2.z - v1.z * v2.y;
// 	cross.y = v1.z * v2.x - v1.x * v2.z;
// 	cross.z = v1.x * v2.y - v1.y * v2.x;
// 	return (cross);
// }




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
//////////////////////////// INVERT MATRIX					//////////////////////////// 
//////////////////////////// //////////////////////////// //////////////////////////// 

/* 	
	Convert matrix to row echelon vorm
	Row echelon vorm is dat je matrix alleen maar 0 waardes 'links onder' heeft en 1 op de diagonaal, 
	rechtsboven mag alle waardes hebben. Dit beriek je door elementary row operations, nl: 
	- add a multiple van een rij aan een andere
	- mulitiply een rij met een non-zero waarde
	- swap een rij met een andere 

	x + 3y - z = 13
	4x - y + z = 9
	2x + 4y + 3z = -6 

	in matrix vorm
	| 1		3		-1 | 	| x |   	| 13 |
	| 4		-1		1  | 	| y | 	= 	| 9  |
	| 2		4		3  | 	| z |   	| -6 |

	dan voeg je de rechter matrix (het antwoord) bij de linker matrix
	| 1		3		-1		13 |
	| 4		-1		1 		9  |
	| 2		4		3  		-6 |

	vanaf hier pas je elementary row operartions toe om de echelon vorm te bereiken. Dit heet Gaussian elimination
	als eerste 'add -2 * row3 to row2`. Dan krijg je dus in rij 2: 

	| 4 (+ -2*2))		-1 (+ -2*4)		1 (+ -2*3)		9 (+ -2*-6) |
	dit maakt 
	| 1		3		-1		13 |
	| 0		-9		-5 		21 |	op deze rij is nu het eerste element 0
	| 2		4		3  		-6 |

	dit blijf je toe passen totdat je de echelon vorm bereikt (multiply row2 by -1/9, add -2*row1 to row3, add 2*row2 to row3)
	Als je echelon vorm hebt, zet je matrix weer terug zoals in begin

	| 1		3		-1		13 		|	maakt 		| 1		3		-1   | 	| x |   	| 13     |
	| 0		1		0.555 	-2.333  |				| 0		1		0.555| 	| y | 	= 	| -2.333 |
	| 0		0		6.111	-36.666 |				| 0		0		6.111| 	| z |   	| -36.666|

	hiermee kan je de somoplossen door naar de laatste rij te kijken:
	0*x + 0*y + 6.111*z = -36.666		dus weet je waarde z, en dan kan je ook de andere waardes berekenen. 
	0*x + 1*y + 0.555*-6 = -2.333       en
	1*x + 3*1 + -1*-6 = 13			x = 4, y = 1 en z = -6

		Gauss Jordan Elimination
	Dit gaat verder op de Gaussian waardoor je de reduced row echelon vorm krijgt. Dit betekent dat alle 'leading' elements 1 zijn 
	en de rest 0. Voor de matrix van hieronder zou dat zijn:
	| 1		0		0  		x   x   x |
	| 0		1		0   	x   x   x |		met x = kan elke waarde zijn, en dat is dan ook gelijk de inverted matrix!
	| 0		0		1   	x   x   x |

	Een inverted matrix heeft de eigenschap A A^-1 = I			I = een identity matrix
	Dus
	| 1		3		-1 | 			| 1   0   0 |
	| 4		-1		1  | A^-1   = 	| 0   1   0 |
	| 2		4		3  | 			| 0   0   1 |
	Om dan A^-1 te krijgen kan je hetzelfde doen als hiervoor dus voeg rechter matrix aan linker toe: 
	| 1		3		-1  	1   0   0 |
	| 4		-1		1   	0   1   0 |
	| 2		4		3   	0   0   1 |
	Pas elementary row operations toe totdat je reduced row echelon vorm hebt.
	| 1		0		0  		7/55 	13/55	-2/55 |									| 7/55 		13/55	-2/55 |
	| 0		1		0   	2/110   -1/11	1/11  |		inverted matrix is dus 		| 2/110   	-1/11	1/11  |
	| 0		0		1   	-18/55  -2/55	13/55 |									| -18/55	-2/55	13/55 |	


*/ 

///////////////////////////	///////////////////////////	///////////////////////////
///////////////////////////	APPLY MATRIX				///////////////////////////
/////////////////////////// ///////////////////////////	///////////////////////////



t_xyz	apply_matrix4_to_vector(t_matrix4 m, t_xyz v)
{
	int			row;
	int			column;
	t_vector4	ret;
	
	ret.a = 1;
	ret.x = (m.value[0][0] * v.x) + (m.value[0][1] * v.y) + (m.value[0][2] * v.z) + (m.value[0][3] * 1);
	ret.y = (m.value[1][0] * v.x) + (m.value[1][1] * v.y) + (m.value[1][2] * v.z) + (m.value[1][3] * 1);
	ret.z = (m.value[2][0] * v.x) + (m.value[2][1] * v.y) + (m.value[2][2] * v.z) + (m.value[2][3] * 1);
	ret.a = (m.value[3][0] * v.x) + (m.value[3][1] * v.y) + (m.value[3][2] * v.z) + (m.value[3][3] * 1);

	v.x = ret.x;
	v.y = ret.y;
	v.z = ret.z;

	return (v);
}









//////////////////////////// //////////////////////////// 	//////////////////////////// 
//////////////////////////// MATRIX MATH 					//////////////////////////// 
//////////////////////////// //////////////////////////// 	//////////////////////////// 

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
	return (lhs);
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
	return (obj);
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
t_matrix4	set_matrix_element(t_matrix4 obj, int row, int column, float value)
{
	obj.value[row][column] = value;
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

	t_matrix4	to_world_coord;
	
	to_world_coord = set_matrix_to_identity(to_world_coord);

	translate_matrix = set_matrix_to_identity(translate_matrix);
	rotate_matrix_X = set_matrix_to_identity(rotate_matrix_X);
	rotate_matrix_Y = set_matrix_to_identity(rotate_matrix_Y);
	rotate_matrix_Z = set_matrix_to_identity(rotate_matrix_Z);
	scale_matrix = set_matrix_to_identity(scale_matrix);

	translate_matrix = set_translation_matrix(translate_matrix, translation_vector);

	rotate_matrix_X = set_rotation_matrix_x_axis(rotate_matrix_X, rotate.x); // what is theta dan 
	rotate_matrix_Y = set_rotation_matrix_y_axis(rotate_matrix_X, rotate.y); // what is theta dan
	rotate_matrix_Z = set_rotation_matrix_z_axis(rotate_matrix_X, rotate.z); // what is theta dan
	
	set_scale_matrix(scale_matrix, scale);

	// translate*scale*rotateX*rotateY*rotateZ
	to_world_coord = multiply_matrices(multiply_matrices(multiply_matrices
						(multiply_matrices(translate_matrix, rotate_matrix_X), 
											rotate_matrix_Y), 
											rotate_matrix_Z), 
											scale_matrix);
	return (to_world_coord);
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
	// obj = set_matrix_to_identity(obj);		// kan weg gelaten worden als het sneller (ook in andere 2 rotatie functie), staat er nu nog in om bugs te voorkomen
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
	// obj = set_matrix_to_identity(obj);
	obj.value[0][0] = cos(theta); 
	obj.value[0][2] = sin(theta);
	obj.value[2][0] = -sin(theta);
	obj.value[2][2] = cos(theta);
	return (obj);
}

t_matrix4	set_scale_matrix(t_matrix4 obj, t_xyz scale)
{
	obj.value[0][0] = scale.x; 
	obj.value[1][1] = scale.y; 
	obj.value[2][2] = scale.z; 
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
	// obj = set_matrix_to_identity(obj);
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
	printf("	0	1	2	 3\n");
	printf("   0  \t%.2f\t%.2f\t%.2f\t%.2f\n", obj.value[0][0], obj.value[0][1], obj.value[0][2], obj.value[0][3]);
	printf("   1  \t%.2f\t%.2f\t%.2f\t%.2f\n", obj.value[1][0], obj.value[1][1], obj.value[1][2], obj.value[1][3]);
	printf("   2  \t%.2f\t%.2f\t%.2f\t%.2f\n", obj.value[2][0], obj.value[2][1], obj.value[2][2], obj.value[2][3]);
	printf("   3  \t%.2f\t%.2f\t%.2f\t%.2f\n\n", obj.value[3][0], obj.value[3][1], obj.value[3][2], obj.value[3][3]);
		
}

void	print_matrix8(t_matrix8 obj)
{
	printf("	0		1		2		3		4		5		6		7\n");
	printf("   0  \t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n", obj.value[0][0], obj.value[0][1], obj.value[0][2], obj.value[0][3], obj.value[0][4], obj.value[0][5], obj.value[0][6], obj.value[0][7]);
	printf("   1  \t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n", obj.value[1][0], obj.value[1][1], obj.value[1][2], obj.value[1][3], obj.value[1][4], obj.value[1][5], obj.value[1][6], obj.value[1][7]);
	printf("   2  \t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n", obj.value[2][0], obj.value[2][1], obj.value[2][2], obj.value[2][3], obj.value[2][4], obj.value[2][5], obj.value[2][6], obj.value[2][7]);
	printf("   3  \t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n\n", obj.value[3][0], obj.value[3][1], obj.value[3][2], obj.value[3][3], obj.value[3][4], obj.value[3][5], obj.value[3][6], obj.value[3][7]);
		
}


// int main()
// {
// 	t_matrix4 c;
// 	t_matrix4 b;
// 	t_matrix4 m;
	
// 	int x = 3;
// 	for (int i = 0; i < 4; i++)
// 	{
// 		x++;
// 		for (int j = 0; j < 4; j++)
// 		{
// 			x+= 3; 
// 			b.value[i][j] = x;
// 		}
	
// 	}
	

//  	x = 9;
// 	for (int i = 0; i < 4; i++)
// 	{
// 		x++;
// 		for (int j = 0; j < 4; j++)
// 		{
// 			x += 2; 
// 			c.value[i][j] = x;
// 		}
		
// 	}
	
// 	// print_matrix(b);
// 	// print_matrix(c);


// 	// *m= multiply_matrices(*b, *c);
// 	m= multiply_matrices(b, c);
// 	// print_matrix(*m);
// 	print_matrix(m);
	

// }


/* functies
	join 2 matrices columnwise
	seperate matrix into 2 around specified column

*/

#include "../../inc/utils/matrices.h"
#include "../../inc/utils/u_invert_matrix.h"
#include <math.h>



/////////// INVERT LOGARITME ////////////////
/*
| a1	a2		a3		1 		0		0 |	
| b1	b2		b3		0 		1		0 |	
| c1	c2		c3		0 		0		1 |	

Dmv elementary row operatios het volgende bereiken: (diagonaal op 1 en rest op 0)
a1 = 1	;	b1 en c1  = 0	; 	a2 en a3 = 0; 
b2 = 1	;	c2 naar 0		;	b3 = 0;
c3 = 1	;	

Dus eerst de diagonaalwaarde op 1 beginnend op 0,0, dan in dezelfde column de waardes daaronder naar 0, 
en dan in dezlefde rij de waardes rechts naar 0. en dan naar diagonaal waarde 1,1 naar 1 etc.
*/

// Turn matrix8 into matrix4 by taking the leftside of matrix8 (which is the inverted matrix)
t_matrix4	seperate_matrix(t_matrix8 obj)
{
	t_matrix4	ret;
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret.value[i][j] = obj.value[i][j + 4];
			j++;
		}
		i++;
	}
	return (ret);
}

bool	left_matrix_is_identity(t_matrix8 obj)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i != j)
				if (obj.value[i][j] != 0)
					return (false);
			if (i == j)
				if (obj.value[i][j] != 1)
					return (false);
			
			j++;
		}
		i++;
	}
	return (true);
}

t_matrix4	invert_matrix(t_matrix4 obj)
{
	// Als eerste een identity matrix toevoegen aan de huidige
	t_matrix4	identity;
	t_matrix8	A;

	identity = set_matrix_to_identity(identity);
	A = augment_matrices(obj, identity);

	// Current row en current column
	int	cRow;
	int	cCol;
	int	maxLoop = 100;		// later op 100
	int	i;
	bool	complete;
	double multi_factor;

	complete = false;
	i = 0;
	while (!complete && (i < maxLoop))
	{
		int diagnol_index = 0;
		while (diagnol_index < 4)	// dit loopt over de diagonaal van de matrix en zet ze op 1 
		{
			
			cRow = diagnol_index;
			cCol = diagnol_index;

			// vind de index van de hoogste waarde in de huidige column
			int maxIndex = find_row_with_max_value_at_column8(A, cRow, cCol);

			// als maxwaarde niet in de huidige rij zit wissel ze ze om
			if (maxIndex != cRow)
				A = swap_two_rows8(A, cRow, maxIndex);

			// zorg dat waarde cRow, cCol 1 is
			if (A.value[cRow][cCol] != 1)
			{
				multi_factor = 1.0 / A.value[cRow][cCol];

				// printf("waarde die naar 1 moet = %f mulitfactor = %f\n", A.value[cRow][cCol], multi_factor);
				A = multiply_row_by_number8(A, cRow, multi_factor);
				// print_matrix8(A);
			}

				/////// TOT HIER WERKT HIJ GOED ///////////


				//	dan moeten alles in de column eronder naar 0
				// dus rowindex is ervoor om de rest van de column eronder te bekijken
			int rowIndex;
				
			rowIndex = cRow + 1;
			while (rowIndex < 4)
			{
				// als het element al 0 is kunnen we door
				if (!close_enough(A.value[rowIndex][cCol], 0.0))
				{
					// Obtain the element to work with from the matrix diagonal.
					// As we aim to set all the diagonal elements to one, this should
					// always be valid for a matrix that can be inverted.
					int	row_one_index = cCol;

					float	current_element_value = A.value[rowIndex][cCol];

					float	row_one_value = A.value[row_one_index][cCol];
					// Als deze 0 is kunnen we door
					if (!close_enough(row_one_value, 0.0))
					{
						// bereken correctie factor om waarde om [rowindex][cCol] naar 0 te krijgen
						float	correctionFactor = - (current_element_value / row_one_value);

						A = multiply_row_and_add_to_row8(A, row_one_index, rowIndex, correctionFactor);
					}
				}
				rowIndex++;
			}

			// dan moet de row (rechtsboven) ook naar 0
			int col_index;
			col_index = cCol + 1;

			// loopt naar rechts
			while (col_index < 4)
			{
				
				if (!close_enough(A.value[cRow][col_index], 0.0))
				{
					int	row_one_index = col_index;

					float 	current_element_value = A.value[cRow][col_index];

					float	row_one_value = A.value[row_one_index][col_index];

					if (!close_enough(row_one_value, 0.0))
					{

						float correction_factor = - (current_element_value / row_one_value);

						A = multiply_row_and_add_to_row8(A, row_one_index, cRow, correction_factor);

					}


				}	
				col_index++;
			}




			diagnol_index++;
		}

		if (left_matrix_is_identity (A))
			break ;
		i++;
	}
	t_matrix4 ret;

	ret = seperate_matrix(A);
	return (ret);
}


////////////// INVERT MATH ////////////////

t_matrix8	augment_matrices(t_matrix4 lhs, t_matrix4 rhs)
{
	int	i;
	int	j;
	t_matrix8	ret;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret.value[i][j] = lhs.value[i][j];
			ret.value[i][j + 4] = rhs.value[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}


t_matrix4	swap_two_rows(t_matrix4 obj, int row1, int row2)
{
	float	swap[4];
	int		i;

	i = 0;
	while (i < 4)
	{
		swap[i] = obj.value[row1][i];
		obj.value[row1][i] = obj.value[row2][i];
		obj.value[row2][i] = swap[i];
		i++;
	}
	return (obj);
}

t_matrix8	swap_two_rows8(t_matrix8 obj, int row1, int row2)
{
	float	swap[8];
	int		i;

	i = 0;
	while (i < 8)
	{
		swap[i] = obj.value[row1][i];
		obj.value[row1][i] = obj.value[row2][i];
		obj.value[row2][i] = swap[i];
		i++;
	}
	return (obj);
}

t_matrix4	multiply_row_by_number(t_matrix4 obj, int row, float nb)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		obj.value[row][i] = obj.value[row][i] * nb;
		i++;
	}
	return (obj);
}

t_matrix8	multiply_row_by_number8(t_matrix8 obj, int row, float nb)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		obj.value[row][i] = obj.value[row][i] * nb;
		i++;
	}
	return (obj);
}

// Mulitplies row1 by nb and adds result to row2
t_matrix4	multiply_row_and_add_to_row(t_matrix4 obj, int row1, int row2, float nb)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		obj.value[row2][i] += obj.value[row1][i] * nb;
		i++;
	}
	return (obj);
}

t_matrix8	multiply_row_and_add_to_row8(t_matrix8 obj, int row1, int row2, float nb)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		obj.value[row2][i] += obj.value[row1][i] * nb;
		i++;
	}
	return (obj);
}

// 	Max[0] holds value, max[1] holds row index
// 	Finds max value starting from row
int		find_row_with_max_value_at_column(t_matrix4 obj, int row, int column)
{
	float	max[2];

	max[0] = obj.value[row][column];
	max[1] = row;
	row++;
	while (row < 4)
	{
		if (max[0] < obj.value[row][column])
		{
			max[0] = obj.value[row][column];
			max[1] = row;
		}
		row++;
	}
	return (max[1]);

}

int		find_row_with_max_value_at_column8(t_matrix8 obj, int row, int column)
{
	float	max[2];

	max[0] = obj.value[row][column];
	max[1] = row;
	row++;
	while (row < 4)
	{
		if (max[0] < obj.value[row][column])
		{
			max[0] = obj.value[row][column];
			max[1] = row;
		}
		row++;
	}
	return (max[1]);

}

// van video code:  this-> = rhs en input is lhs. Dus input - this->
// Functions compares all elements of the two matrices and returns true
// if the difference in cumulative sum is lower then the tolerance
bool	compare_matrix_by_sum(t_matrix4 lhs, t_matrix4 rhs, double tolerance)
{
	int		i;
	int		j;
	double	cumulative_sum;

	cumulative_sum = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		{
			cumulative_sum += ((lhs.value[i][j] - rhs.value[i][j]) * (lhs.value[i][j] - rhs.value[i][j]));
			j++;
		}
		i++;
	}		
	
										// total elements -1 ( = aantal rows * aantal columns - 1)
	cumulative_sum = sqrt(cumulative_sum / ((4 * 4) - 1));
	if (cumulative_sum <= tolerance)
		return (true);
	else
		return (false);
}

bool	close_enough(float value1, float value2)
{
	return (fabs(value1 - value2) < 1e-9);
}

// Compares 2 matrices element by element and returns true if they are equal (or close enough < 1e-9)
bool	compare_matrix_by_element(t_matrix4 lhs, t_matrix4 rhs)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		{
			if (!(fabs(lhs.value[i][j] - rhs.value[i][j]) < 1e-9))
				return (false);
			j++;
		}
		i++;
	}				
	return (true);
}




// int main()
// {
// 	t_matrix4 c;
// 	t_matrix4 b;
// 	t_matrix4 m;
	
// 	int x = 3;
// 	for (int i = 0; i < 2; i++)
// 	{
// 		x++;
// 		for (int j = 0; j < 4; j++)
// 		{
// 			x+= 3; 
// 			b.value[i][j] = x;
// 		}
	
// 	}
// 	x = -15;
// 	for (int i = 2; i < 4; i++)
// 	{
// 		x++;
// 		for (int j = 0; j < 4; j++)
// 		{
// 			x-= 3; 
// 			b.value[i][j] = x;
// 		}
	
// 	}

// 	printf("input matrix: \n");
// 	print_matrix(b);

// 	invert_matrix(b);











	// x = 5;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x-= 1; 
	// 		c.value[i][j] = x;
	// 	}
	
	// }
	// print_matrix(c);
	// print_matrix(b);
	// t_matrix8	big = augment_matrices(c, b);
	// print_matrix8(big);
	

	// b = multiply_row_and_add_to_row(b, 0, 1, 2);
	// print_matrix(b);
	

	// x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x--;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x-= 3; 
	// 		c.value[i][j] = x;
	// 	}
	
	// }

			////////////////// TEST MAX VALUE IN ROW	////////////////
	// int	x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		c.value[i][j] = x;
	// 	}
	// }
	// x = 5;	
	// for (int i = 0; i < 4; i++)
	// {
	// 	x--;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x-= 3; 
	// 		b.value[i][j] = x;
	// 	}
	// }	

	// print_matrix(b);
	// printf("row with max value in column 2 = %i\n", find_row_with_max_value_at_column(b, 2, 2));
	// print_matrix(c);
	// printf("row with max value in column 2 = %i\n\n", find_row_with_max_value_at_column(c, 0, 2));



			////////////////// TEST SWAP VALUE IN ROW	////////////////
	// x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		c.value[i][j] = x;
	// 	}
	// }
	// t_matrix8 A = augment_matrices(c, c);
	// print_matrix8(A);
	// A = swap_two_rows8(A, 1, 2);
	// print_matrix8(A);

	// print_matrix(c);
	// c = swap_two_rows(c, 1, 2);
	// print_matrix(c);




			////////////////// TEST COMPARE BY ELEMENT	////////////////
	// 	int x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		b.value[i][j] = x;
	// 	}
	
	// }
	// x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		c.value[i][j] = x;
	// 	}
	
	// }
	// print_matrix(c);
	// print_matrix(b);
	// if (compare_matrix_by_element(b, c))
	// 	printf("Should print because they have same elements over all\n");
	// b.value[0][0] = 2;
	// print_matrix(c);
	// print_matrix(b);
	// if (!compare_matrix_by_element(b, c))
	// 	printf("Should print because they do not have same elements over all\n");

		/////////////////// AUGMENT MATRICES /////////////////////
	// int x = 3;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x+= 3; 
	// 		b.value[i][j] = x;
	// 	}
	
	// }
	// x = 5;
	// for (int i = 0; i < 4; i++)
	// {
	// 	x++;
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		x-= 1; 
	// 		c.value[i][j] = x;
	// 	}
	
	// }
	// print_matrix(c);
	// print_matrix(b);
	// t_matrix8	big = augment_matrices(c, b);
	// print_matrix8(big);

// }

