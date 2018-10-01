#include "unity_fixture.h"

static void	RunAllTests(void)
{
	//UnityFixture.Verbose = 1;
	//RUN_TEST_GROUP(ft_dprintf);
	//RUN_TEST_GROUP(ft_snprintf);
	//RUN_TEST_GROUP(print_percent);
	//RUN_TEST_GROUP(print_integer);
	//RUN_TEST_GROUP(print_char);
	//RUN_TEST_GROUP(print_string);
	//RUN_TEST_GROUP(print_pointer);
	RUN_TEST_GROUP(big_int);
	RUN_TEST_GROUP(dragon4_log_base_2);
	RUN_TEST_GROUP(dragon4_print_float64);
}

int			main(int argc, const char **argv)
{
	return (UnityMain(argc, argv, RunAllTests));
}
