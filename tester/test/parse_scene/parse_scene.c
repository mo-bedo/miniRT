#include "../../unity/extras/fixture/src/unity_fixture.h"
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
#include "main.h"
#include "parse_scene/parse_scene.h"
#include "parse_scene/parse_scene_utils.h"

TEST_GROUP(parse_scene);

TEST_SETUP(parse_scene)
{
}

TEST_TEAR_DOWN(parse_scene)
{
}

TEST(parse_scene, parse_line)
{
	t_mlx	mlx;
	
	parse_line(&mlx, "A   0.2 										255,255,255");
	TEST_ASSERT_EQUAL_FLOAT(0.2, mlx.d.a.lighting_ratio);
	TEST_ASSERT_EQUAL_INT(255, mlx.d.a.rgb.red);
	TEST_ASSERT_EQUAL_INT(255, mlx.d.a.rgb.blue);
	TEST_ASSERT_EQUAL_INT(255, mlx.d.a.rgb.green);

	parse_line(&mlx, "C   -50.0,0,20 		-1,0,0.2 		70");
	TEST_ASSERT_EQUAL_FLOAT(-50, mlx.d.c.xyz.x);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.c.xyz.y);
	TEST_ASSERT_EQUAL_FLOAT(20, mlx.d.c.xyz.z);
	TEST_ASSERT_EQUAL_FLOAT(-1, mlx.d.c.vector_orientation.x);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.c.vector_orientation.y);
	TEST_ASSERT_EQUAL_FLOAT(0.2, mlx.d.c.vector_orientation.z);
	TEST_ASSERT_EQUAL_FLOAT(70, mlx.d.c.field_of_view);

	parse_line(&mlx, "L   -40,0,30 					0.7 			255,255,255");
	TEST_ASSERT_EQUAL_FLOAT(-40, mlx.d.l.xyz.x);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.l.xyz.y);
	TEST_ASSERT_EQUAL_FLOAT(30, mlx.d.l.xyz.z);
	TEST_ASSERT_EQUAL_FLOAT(0.7, mlx.d.l.brightness);

	parse_line(&mlx, "sp  0.0,0.0,20 						20 				255,0,0");
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.sp.xyz.x);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.sp.xyz.y);
	TEST_ASSERT_EQUAL_FLOAT(20, mlx.d.sp.xyz.z);
	TEST_ASSERT_EQUAL_FLOAT(20, mlx.d.sp.diameter);
	TEST_ASSERT_EQUAL_INT(255, mlx.d.sp.rgb.red);
	TEST_ASSERT_EQUAL_INT(0, mlx.d.sp.rgb.blue);
	TEST_ASSERT_EQUAL_INT(0, mlx.d.sp.rgb.green);

	parse_line(&mlx, "pl  0,0,0 			0,1.0,0 					255,0,225");
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.pl.xyz.x);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.pl.xyz.y);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.pl.xyz.z);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.pl.vector_orientation.x);
	TEST_ASSERT_EQUAL_FLOAT(1, mlx.d.pl.vector_orientation.y);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.pl.vector_orientation.z);
	TEST_ASSERT_EQUAL_INT(255, mlx.d.pl.rgb.red);
	TEST_ASSERT_EQUAL_INT(0, mlx.d.pl.rgb.blue);
	TEST_ASSERT_EQUAL_INT(225, mlx.d.pl.rgb.green);

	parse_line(&mlx, "cy  50.0,0.0,20.6	0,0,1.0 	14.2 	21.42 	10,0,255");
	TEST_ASSERT_EQUAL_FLOAT(50, mlx.d.cy.xyz.x);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.cy.xyz.y);
	TEST_ASSERT_EQUAL_FLOAT(20.6, mlx.d.cy.xyz.z);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.cy.vector_orientation.x);
	TEST_ASSERT_EQUAL_FLOAT(0, mlx.d.cy.vector_orientation.y);
	TEST_ASSERT_EQUAL_FLOAT(1, mlx.d.cy.vector_orientation.z);
	TEST_ASSERT_EQUAL_FLOAT(14.2, mlx.d.cy.diameter);
	TEST_ASSERT_EQUAL_FLOAT(21.42, mlx.d.cy.height);
	TEST_ASSERT_EQUAL_INT(10, mlx.d.cy.rgb.red);
	TEST_ASSERT_EQUAL_INT(0, mlx.d.cy.rgb.blue);
	TEST_ASSERT_EQUAL_INT(255, mlx.d.cy.rgb.green);
}



// example:
// TEST(parse_scene_utils, check_if_ratio)
// {
// 	// ARRANGE
// 	// char	*input;
// 	int		exp_result;
// 	int		our_result;

// 	// input = ft_strdup("0.1");
// 	exp_result = 1;

// 	// ACT
// 	our_result = check_if_ratio("0.1");

// 	// ASSERT
// 	TEST_ASSERT_EQUAL_INT(exp_result, our_result);

// 	// free(input);
// }