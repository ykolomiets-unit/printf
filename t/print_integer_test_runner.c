#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(print_integer)
{
	printf("\n\nprint_integer tests\n");	
	RUN_TEST_CASE(print_integer, d);
	RUN_TEST_CASE(print_integer, plus_d);
	RUN_TEST_CASE(print_integer, space_d);
	RUN_TEST_CASE(print_integer, string_plus_d_space_and_plus_sign_flag);
	RUN_TEST_CASE(print_integer, string_plus_d_altfmt_flag);
	RUN_TEST_CASE(print_integer, string_plus_x_altfmt_flag);
	RUN_TEST_CASE(print_integer, string_plus_o_altfmt_flag);
	RUN_TEST_CASE(print_integer, string_plus_X);
	RUN_TEST_CASE(print_integer, string_plus_X_altfmt_flag);
	RUN_TEST_CASE(print_integer, minus_and_zero_flags);
	RUN_TEST_CASE(print_integer, string_plus_negative_num);
	RUN_TEST_CASE(print_integer, d_with_length);
	RUN_TEST_CASE(print_integer, d_with_asterix_length);
	RUN_TEST_CASE(print_integer, d_with_length_plus_sign);
	RUN_TEST_CASE(print_integer, d_with_length_lt_real_length);
	RUN_TEST_CASE(print_integer, d_with_length_lt_real_length_and_zero_flag);
	RUN_TEST_CASE(print_integer, d_with_left_adjust);
	RUN_TEST_CASE(print_integer, d_with_left_adjust_and_zero_pad);
	RUN_TEST_CASE(print_integer, d_with_negative_asterix_length);
	RUN_TEST_CASE(print_integer, d_with_precision);
	RUN_TEST_CASE(print_integer, d_with_precision_and_additional_flags);
	RUN_TEST_CASE(print_integer, d_with_length_and_precision);
	RUN_TEST_CASE(print_integer, d_with_0_precision);
	RUN_TEST_CASE(print_integer, o_with_0_presicion_and_altfmt);
	RUN_TEST_CASE(print_integer, empty_precision_with_zero_value);
	RUN_TEST_CASE(print_integer, d_equals_0_with_0_precision);
	RUN_TEST_CASE(print_integer, d_with_asterix_precision);
	RUN_TEST_CASE(print_integer, d_with_negative_asterix_precision);
	RUN_TEST_CASE(print_integer, string_plus_u);
	RUN_TEST_CASE(print_integer, string_plus_u_and_negative_value);
	RUN_TEST_CASE(print_integer, hd_with_value_gt_maxshort);
	RUN_TEST_CASE(print_integer, hhd_with_value_gt_maxshort);
	RUN_TEST_CASE(print_integer, U_with_maximum_unsigned_long);
	RUN_TEST_CASE(print_integer, hU_with_maximum_unsigned_long);
	RUN_TEST_CASE(print_integer, jx_with_4294967296);
	RUN_TEST_CASE(print_integer, jx_with_minus_4294967296);
	RUN_TEST_CASE(print_integer, jx_with_minus_4294967297);
	RUN_TEST_CASE(print_integer, jd_with_9223372036854775807);
	RUN_TEST_CASE(print_integer, jd_with_minus_9223372036854775808);
}
