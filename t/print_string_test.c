#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include "ft_printf.h"
#include <stdio.h>

#define BUF_SIZE 1024

static char	buffer[BUF_SIZE];

TEST_GROUP(print_string);

TEST_SETUP(print_string)
{
	bzero(buffer, BUF_SIZE);
}

TEST_TEAR_DOWN(print_string)
{
	bzero(buffer, BUF_SIZE);
}

TEST(print_string, 1)
{
	char *fmt = "%s";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, "test");
	TEST_ASSERT_EQUAL_STRING("test", buffer);
}

TEST(print_string, 2)
{
	char *fmt = "%.3s";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, "test");
	TEST_ASSERT_EQUAL_STRING("tes", buffer);
}

TEST(print_string, 3)
{
	char *fmt = "%5s";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, "test");
	TEST_ASSERT_EQUAL_STRING(" test", buffer);
}

TEST(print_string, 4)
{
	char *fmt = "%-5s";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, "test");
	TEST_ASSERT_EQUAL_STRING("test ", buffer);
}

TEST(print_string, 5)
{
	char *fmt = "%s";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, NULL);
	TEST_ASSERT_EQUAL_STRING("(null)", buffer);
}
