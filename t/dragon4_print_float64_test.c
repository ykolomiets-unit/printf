#include "unity.h"
#include "unity_fixture.h"
#include "utils.h"
#include "dragon4.h"

TEST_GROUP(dragon4_print_float64);

# define BUF_SIZE 1024

static	t_print_float64_arg arg;
char	buffer[BUF_SIZE];

TEST_SETUP(dragon4_print_float64)
{
	arg.out_buffer = buffer;
	arg.buffer_size = BUF_SIZE;
	ft_bzero(buffer, BUF_SIZE);
}

TEST_TEAR_DOWN(dragon4_print_float64)
{
}

TEST(dragon4_print_float64, positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = -0.231231231231231;
	arg.precision = 6;
	print_float64(arg);
	printf("\n%s\n", buffer);
	printf("%f\n", arg.value);
}
