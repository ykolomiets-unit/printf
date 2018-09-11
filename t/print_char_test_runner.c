#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(print_char)
{
	printf("\n\nprint_char tests\n");	
	RUN_TEST_CASE(print_char, 1);
	RUN_TEST_CASE(print_char, 2);
	RUN_TEST_CASE(print_char, 3);
}
