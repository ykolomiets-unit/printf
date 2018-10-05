#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include "ft_printf.h"
#include <stdio.h>

#define BUF_SIZE 1024

static char	buffer[BUF_SIZE];

TEST_GROUP(print_float);

TEST_SETUP(print_float)
{
	bzero(buffer, BUF_SIZE);
}

TEST_TEAR_DOWN(print_float)
{
	bzero(buffer, BUF_SIZE);
}

TEST(print_float, f_100)
{
	ft_snprintf(buffer, BUF_SIZE, "%f", 100.);
	TEST_ASSERT_EQUAL_STRING("100.000000", buffer);
}

TEST(print_float, minus_f_100)
{
	ft_snprintf(buffer, BUF_SIZE, "%f", -100.0);
	TEST_ASSERT_EQUAL_STRING("-100.000000", buffer);
}

TEST(print_float, e_100)
{
	ft_snprintf(buffer, BUF_SIZE, "%e", 100.0);
	TEST_ASSERT_EQUAL_STRING("1.000000e+02", buffer);
}

TEST(print_float, minus_e_100)
{
	ft_snprintf(buffer, BUF_SIZE, "%e", -100.0);
	TEST_ASSERT_EQUAL_STRING("-1.000000e+02", buffer);
}

TEST(print_float, f_100_zero_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.0f", 100.0);
	TEST_ASSERT_EQUAL_STRING("100", buffer);
}

TEST(print_float, e_100_zero_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.0e", 100.0);
	TEST_ASSERT_EQUAL_STRING("1e+02", buffer);
}

TEST(print_float, f_100_not_a_zero_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.3f", 100.0);
	TEST_ASSERT_EQUAL_STRING("100.000", buffer);
}

TEST(print_float, e_100_not_a_zero_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.3e", 100.0);
	TEST_ASSERT_EQUAL_STRING("1.000e+02", buffer);
}

TEST(print_float, f_width1)
{
	ft_snprintf(buffer, BUF_SIZE, "%2.2f", 100.0);
	TEST_ASSERT_EQUAL_STRING("100.00", buffer);
}

TEST(print_float, f_width2)
{
	ft_snprintf(buffer, BUF_SIZE, "%10.2f", 100.0);
	TEST_ASSERT_EQUAL_STRING("    100.00", buffer);
}

TEST(print_float, f_width_with_zero_pad)
{
	ft_snprintf(buffer, BUF_SIZE, "%010.2f", 100.0);
	TEST_ASSERT_EQUAL_STRING("0000100.00", buffer);
}

TEST(print_float, e_width_with_zero_pad)
{
	ft_snprintf(buffer, BUF_SIZE, "%010.2e", 100.0);
	TEST_ASSERT_EQUAL_STRING("001.00e+02", buffer);
}

TEST(print_float, f_width_with_left_adjust)
{
	ft_snprintf(buffer, BUF_SIZE, "%-10.2f", 100.0);
	TEST_ASSERT_EQUAL_STRING("100.00    ", buffer);
}

TEST(print_float, f_space_sign_for_positive)
{
	ft_snprintf(buffer, BUF_SIZE, "% .2f", 100.0);
	TEST_ASSERT_EQUAL_STRING(" 100.00", buffer);
}

TEST(print_float, f_space_sign_for_negative)
{
	ft_snprintf(buffer, BUF_SIZE, "% .2f", -100.0);
	TEST_ASSERT_EQUAL_STRING("-100.00", buffer);
}

TEST(print_float, f_plus_sign_for_positive)
{
	ft_snprintf(buffer, BUF_SIZE, "%+.2f", 100.0);
	TEST_ASSERT_EQUAL_STRING("+100.00", buffer);
}

TEST(print_float, f_plus_sign_for_negative)
{
	ft_snprintf(buffer, BUF_SIZE, "%+.2f", -100.0);
	TEST_ASSERT_EQUAL_STRING("-100.00", buffer);
}

TEST(print_float, f_alternative_form)
{
	ft_snprintf(buffer, BUF_SIZE, "%#.0f", 100.0);
	TEST_ASSERT_EQUAL_STRING("100.", buffer);
}
