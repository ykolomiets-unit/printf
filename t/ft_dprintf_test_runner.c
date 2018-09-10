#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(ft_dprintf)
{
	printf("\n\nft_dprintf tests\n");	
	RUN_TEST_CASE(ft_dprintf, basic_test);
	RUN_TEST_CASE(ft_dprintf, output_string_gt_buf_size);
}
