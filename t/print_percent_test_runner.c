#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(print_percent)
{
	printf("\n\nprint_percent tests\n");	
	RUN_TEST_CASE(print_percent, 1);
	RUN_TEST_CASE(print_percent, 2);
	RUN_TEST_CASE(print_percent, 3);
	RUN_TEST_CASE(print_percent, 4);
}
