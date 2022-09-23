#include "../../unity/extras/fixture/src/unity_fixture.h"
#include "utils.h"
#include "parse_scene/parse_scene_utils.h"

TEST_GROUP(parse_scene_utils);

TEST_SETUP(parse_scene_utils)
{
}

TEST_TEAR_DOWN(parse_scene_utils)
{
}


TEST(parse_scene_utils, parse_int_correct)
{
	char *input_1 = "0";
	char *input_2 = "125";
	char *input_3 = "255";

	TEST_ASSERT_EQUAL_INT(0, parse_int(&input_1, 0, 255));
	TEST_ASSERT_EQUAL_INT(125, parse_int(&input_2, 0, 255));
	TEST_ASSERT_EQUAL_INT(255, parse_int(&input_3, 0, 255));
}

TEST(parse_scene_utils, parse_int_incorrect)
{
	// TEST_ASSERT_EQUAL_INT(-1, parse_int("0", 0, 255));
	// TEST_ASSERT_EQUAL_INT(a, parse_int("125", 0, 255));
	// TEST_ASSERT_EQUAL_INT(0.2, parse_int("125", 0, 255));
	// TEST_ASSERT_EQUAL_INT(256, parse_int("255", 0, 255));
}

TEST(parse_scene_utils, parse_float_correct)
{
	char *input_1 = "0";
	char *input_2 = "0.5";
	char *input_3 = "1.0";
	char *input_4 = "-0.9";

	TEST_ASSERT_EQUAL_FLOAT(0.0, parse_float(&input_1, -1, 2));
	TEST_ASSERT_EQUAL_FLOAT(0.5, parse_float(&input_2, -1, 2));
	TEST_ASSERT_EQUAL_FLOAT(1.0, parse_float(&input_3, -1, 2));
	TEST_ASSERT_EQUAL_FLOAT(-0.9, parse_float(&input_4, -1, 2));
}

TEST(parse_scene_utils, parse_float_incorrect)
{
	// TO DO, write test ti check if error message is generated
	// examples of incorrect ratio's:
	// TEST_ASSERT_EQUAL_FLOAT(-1.0, parse_float("-1.0", 0, 255));
	// TEST_ASSERT_EQUAL_FLOAT(255.1, parse_float("255.1", 0, 255));
	// 00.1
	// 1
	// .1
	// 0,1
	// a
	// 0.a
	// 0.
	// 1.1
	// -1.0
	// -0.2
	// 0.12
}


TEST(parse_scene_utils, parse_rgb)
{
	// TO DO: beslissen of we kleurn als 1 int opslaan
	// of in t_rgb struct
}

TEST(parse_scene_utils, parse_xyz)
{
	// Correct RGB range
	// TEST_ASSERT_EQUAL_DOUBLE(0.0, parse_xyz("0.0"));
	// TEST_ASSERT_EQUAL_DOUBLE(125, parse_xyz("125"));
	// TEST_ASSERT_EQUAL_DOUBLE(255, parse_xyz("255"));

	// Incorrect RGB range
	// -1
	// 256
	// a
}