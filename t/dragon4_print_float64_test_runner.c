#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(dragon4_print_float64)
{
	printf("\n\ndragon4 print_float64\n");
	RUN_TEST_CASE(dragon4_print_float64, 100_positional);
	RUN_TEST_CASE(dragon4_print_float64, 12345_positional);
	RUN_TEST_CASE(dragon4_print_float64, 1234567890_positional);
	RUN_TEST_CASE(dragon4_print_float64, negative_100_positional);
	RUN_TEST_CASE(dragon4_print_float64, 0_positional);
	RUN_TEST_CASE(dragon4_print_float64, 0_123456_positional);
	RUN_TEST_CASE(dragon4_print_float64, 0_123453_precision5_positional);
	RUN_TEST_CASE(dragon4_print_float64, 0_123456_precision5_positional);
	RUN_TEST_CASE(dragon4_print_float64, positive_infinity_positional);
	RUN_TEST_CASE(dragon4_print_float64, negative_infinity_positional);
	RUN_TEST_CASE(dragon4_print_float64, positive_nan_positional);
	RUN_TEST_CASE(dragon4_print_float64, negative_nan_positional);
}
