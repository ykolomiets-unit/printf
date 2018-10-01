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

TEST(dragon4_print_float64, 100_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = 100;
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("100", buffer);
}

TEST(dragon4_print_float64, 12345_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = 12345;
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("12345", buffer);
}

TEST(dragon4_print_float64, 1234567890_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = 1234567890;
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("1234567890", buffer);
}

TEST(dragon4_print_float64, negative_100_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = -100;
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("-100", buffer);
}

TEST(dragon4_print_float64, 0_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = 0;
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("0", buffer);
}

TEST(dragon4_print_float64, 0_123456_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = 0.123456;
	arg.precision = 6;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("0.123456", buffer);
}

TEST(dragon4_print_float64, 0_123453_precision5_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = 0.123453;
	arg.precision = 5;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("0.12345", buffer);
}

TEST(dragon4_print_float64, 0_123456_precision5_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = 0.123456;
	arg.precision = 5;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("0.12346", buffer);
}

TEST(dragon4_print_float64, positive_infinity_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = INFINITY;
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("inf", buffer);
}

TEST(dragon4_print_float64, negative_infinity_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	arg.value = -INFINITY;
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("-inf", buffer);
}

TEST(dragon4_print_float64, positive_nan_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	uint64_t inf = 0x7ff0001000000000;
	arg.value = *((double*)&inf);
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("nan", buffer);
}

TEST(dragon4_print_float64, negative_nan_positional)
{
	arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	uint64_t inf = 0xfff0001000000000;
	arg.value = *((double*)&inf);
	arg.precision = 0;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("-nan", buffer);
}

TEST(dragon4_print_float64, 100_scientific)
{
	arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	arg.value = 100;
	arg.precision = 6;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("100", buffer);
}

TEST(dragon4_print_float64, 12345_scientific)
{
	arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	arg.value = 12345;
	arg.precision = 6;
	print_float64(arg);
	TEST_ASSERT_EQUAL_STRING("12345", buffer);
}

TEST(dragon4_print_float64, 1234567890_scientific)
{
	arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	arg.value = 1234567890;
	arg.precision = 6;
	print_float64(arg);
	printf("\n%e\n", arg.value);
	TEST_ASSERT_EQUAL_STRING("1234567890", buffer);
}

TEST(dragon4_print_float64, negative_100_scientific)
{
	arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	arg.value = -100;
	arg.precision = 6;
	print_float64(arg);
	printf("\n%e\n", arg.value);
	TEST_ASSERT_EQUAL_STRING("-100", buffer);
}

TEST(dragon4_print_float64, 0_scientific)
{
	arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	arg.value = 0;
	arg.precision = 6;
	print_float64(arg);
	printf("\n%e\n", arg.value);
	TEST_ASSERT_EQUAL_STRING("0", buffer);
}

TEST(dragon4_print_float64, 0_123456_scientific)
{
	arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	arg.value = 0.123456;
	arg.precision = 6;
	print_float64(arg);
	printf("\n%e\n", arg.value);
	TEST_ASSERT_EQUAL_STRING("0.123456", buffer);
}

TEST(dragon4_print_float64, 0_123453_precision4_scientific)
{
	arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	arg.value = 0.123453;
	arg.precision = 4;
	print_float64(arg);
	printf("\n%.5e\n", arg.value);
	TEST_ASSERT_EQUAL_STRING("0.12345", buffer);
}

TEST(dragon4_print_float64, 0_123456_precision4_scientific)
{
	arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	arg.value = 0.123456;
	arg.precision = 4;
	print_float64(arg);
	printf("\n%.5e\n", arg.value);
	TEST_ASSERT_EQUAL_STRING("0.12346", buffer);
}