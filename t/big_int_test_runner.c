#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(big_int)
{
	printf("\n\nbig_int\n");	
	RUN_TEST_CASE(big_int, set_zero);
	RUN_TEST_CASE(big_int, set_u32_zero);
	RUN_TEST_CASE(big_int, set_u32_not_zero);
	RUN_TEST_CASE(big_int, set_u64_zero);
	RUN_TEST_CASE(big_int, set_u64_lt_0xffffffff);
	RUN_TEST_CASE(big_int, set_u64_gt_0xffffffff);
}
