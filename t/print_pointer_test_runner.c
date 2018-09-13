#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(print_pointer)
{
	printf("\n\nprint_pointer tests\n");	
	RUN_TEST_CASE(print_pointer, 1);
	RUN_TEST_CASE(print_pointer, 2);
	RUN_TEST_CASE(print_pointer, 3);
	RUN_TEST_CASE(print_pointer, 4);
	RUN_TEST_CASE(print_pointer, 5);
}
