#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(ft_printf)
{
	printf("ft_printf tests\n");	
	RUN_TEST_CASE(ft_printf, test);
}
