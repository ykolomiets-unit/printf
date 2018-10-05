#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(print_float)
{
	printf("\n\nprint_float tests\n");	
	RUN_TEST_CASE(print_float, f_100);
	RUN_TEST_CASE(print_float, minus_f_100);
	RUN_TEST_CASE(print_float, e_100);
	RUN_TEST_CASE(print_float, minus_e_100);
	RUN_TEST_CASE(print_float, f_100_zero_precision);
	RUN_TEST_CASE(print_float, e_100_zero_precision);
	RUN_TEST_CASE(print_float, f_100_not_a_zero_precision);
	RUN_TEST_CASE(print_float, e_100_not_a_zero_precision);
	RUN_TEST_CASE(print_float, f_width1);
	RUN_TEST_CASE(print_float, f_width2);
	RUN_TEST_CASE(print_float, f_width_with_zero_pad);
	RUN_TEST_CASE(print_float, e_width_with_zero_pad);
	RUN_TEST_CASE(print_float, f_width_with_left_adjust);
	RUN_TEST_CASE(print_float, f_space_sign_for_positive);
	RUN_TEST_CASE(print_float, f_space_sign_for_negative);
	RUN_TEST_CASE(print_float, f_plus_sign_for_positive);
	RUN_TEST_CASE(print_float, f_plus_sign_for_negative);
	RUN_TEST_CASE(print_float, f_alternative_form);
}
