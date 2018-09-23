#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(dragon4_log_base_2)
{
	printf("\n\ndragon4 log2");	
	RUN_TEST_CASE(dragon4_log_base_2, log_0);
	RUN_TEST_CASE(dragon4_log_base_2, log_2);
	RUN_TEST_CASE(dragon4_log_base_2, log_5);
	RUN_TEST_CASE(dragon4_log_base_2, log_256);
	RUN_TEST_CASE(dragon4_log_base_2, log_4096);
}
