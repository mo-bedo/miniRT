/* all_tests_runner.c */
#include "unity_fixture.h"
#include <stdio.h>

#define GREEN "\e[32m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"
#define NORMAL "\e[00m"

TEST_GROUP_RUNNER(parse_scene)
{
	printf("\n"BLUE"parse_scene\t"PURPLE"parse_scene\n"NORMAL);
	RUN_TEST_CASE(parse_scene, parse_line);
}

TEST_GROUP_RUNNER(parse_scene_utils)
{
	printf("\n"BLUE"parse_scene\t"PURPLE"parse_scene_utils\n"NORMAL);

	// parse_int()
	RUN_TEST_CASE(parse_scene_utils, parse_int_correct);
	RUN_TEST_CASE(parse_scene_utils, parse_int_incorrect);

	// parse_float()
	RUN_TEST_CASE(parse_scene_utils, parse_float_correct);
	RUN_TEST_CASE(parse_scene_utils, parse_float_incorrect);

	// parse_rgb()
	RUN_TEST_CASE(parse_scene_utils, parse_rgb);

	// parse_xyz()
	RUN_TEST_CASE(parse_scene_utils, parse_xyz);
}