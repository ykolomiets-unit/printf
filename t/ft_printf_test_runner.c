#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(ft_printf)
{
	printf("ft_printf tests\n");	
	RUN_TEST_CASE(ft_printf, basic_test);
	RUN_TEST_CASE(ft_printf, output_string_gt_buf_size);
	RUN_TEST_CASE(ft_printf, snptinf);
	RUN_TEST_CASE(ft_printf, only_d);
	RUN_TEST_CASE(ft_printf, string_plus_d);
	RUN_TEST_CASE(ft_printf, string_plus_d_plus_sign_flag);
	RUN_TEST_CASE(ft_printf, string_plus_d_space_sign_flag);
	RUN_TEST_CASE(ft_printf, string_plus_d_space_and_plus_sign_flag);
	RUN_TEST_CASE(ft_printf, string_plus_d_altfmt_flag);
	RUN_TEST_CASE(ft_printf, string_plus_x_altfmt_flag);
	RUN_TEST_CASE(ft_printf, string_plus_o_altfmt_flag);
	RUN_TEST_CASE(ft_printf, string_plus_X);
	RUN_TEST_CASE(ft_printf, string_plus_X_altfmt_flag);
	RUN_TEST_CASE(ft_printf, string_plus_negative_num);
	RUN_TEST_CASE(ft_printf, d_with_length);
	RUN_TEST_CASE(ft_printf, d_with_asterix_length);
	RUN_TEST_CASE(ft_printf, d_with_length_plus_sign);
	RUN_TEST_CASE(ft_printf, d_with_length_lt_real_length);
	RUN_TEST_CASE(ft_printf, d_with_length_lt_real_length_and_zero_flag);
	RUN_TEST_CASE(ft_printf, d_with_left_adjust);
	RUN_TEST_CASE(ft_printf, d_with_negative_asterix_length);
	RUN_TEST_CASE(ft_printf, d_with_precision);
	RUN_TEST_CASE(ft_printf, d_with_precision_and_additional_flags);
	RUN_TEST_CASE(ft_printf, d_with_length_and_precision);
	RUN_TEST_CASE(ft_printf, d_with_0_precision);
	RUN_TEST_CASE(ft_printf, d_equals_0_with_0_precision);
}
