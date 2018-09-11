#include "unity_fixture.h"

static void	RunAllTests(void)
{
	//UnityFixture.Verbose = 1;
	RUN_TEST_GROUP(ft_dprintf);
	RUN_TEST_GROUP(ft_snprintf);
	RUN_TEST_GROUP(print_percent);
	RUN_TEST_GROUP(print_integer);
	RUN_TEST_GROUP(print_char);
	RUN_TEST_GROUP(print_string);
}

int			main(int argc, const char **argv)
{
	return (UnityMain(argc, argv, RunAllTests));
}
