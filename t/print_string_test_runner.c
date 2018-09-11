#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(print_string)
{
	printf("\n\nprint_string tests\n");	
	RUN_TEST_CASE(print_string, 1);
}
