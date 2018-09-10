#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(ft_snprintf)
{
	printf("\n\nft_snprintf tests\n");	
	RUN_TEST_CASE(ft_snprintf, snptinf);
}
