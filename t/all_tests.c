#include "unity_fixture.h"

static void	RunAllTests(void)
{
	UnityFixture.Verbose = 1;
	RUN_TEST_GROUP(ft_printf);
}

int			main(int argc, const char **argv)
{
	return (UnityMain(argc, argv, RunAllTests));
}
