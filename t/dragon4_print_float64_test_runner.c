#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(dragon4_print_float64)
{
	printf("\n\ndragon4 print_float64\n");
	RUN_TEST_CASE(dragon4_print_float64, positional);
}
