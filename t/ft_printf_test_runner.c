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
	RUN_TEST_CASE(ft_printf, string_plus_negative_num);
}
