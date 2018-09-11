#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(print_string)
{
	printf("\n\nprint_string tests\n");	
	RUN_TEST_CASE(print_string, 1);
	RUN_TEST_CASE(print_string, 2);
	RUN_TEST_CASE(print_string, 3);
	RUN_TEST_CASE(print_string, 4);
	RUN_TEST_CASE(print_string, 5);
}
