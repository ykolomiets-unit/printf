#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include "ft_printf.h"
#include <stdio.h>

#define BUF_SIZE 1024

static char	buffer[BUF_SIZE];
static char test_buf[BUF_SIZE];

TEST_GROUP(print_pointer);

TEST_SETUP(print_pointer)
{
	bzero(buffer, BUF_SIZE);
	bzero(test_buf, BUF_SIZE);
}

TEST_TEAR_DOWN(print_pointer)
{
	bzero(buffer, BUF_SIZE);
	bzero(test_buf, BUF_SIZE);
}

TEST(print_pointer, 1)
{
	char *fmt = "%p";
	printf(" (%s) \n", fmt);
	snprintf(test_buf, BUF_SIZE, fmt, fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, fmt);
	TEST_ASSERT_EQUAL_STRING(test_buf, buffer);
}

TEST(print_pointer, 2)
{
	char *fmt = "%5p";
	printf(" (%s) \n", fmt);
	snprintf(test_buf, BUF_SIZE, fmt, NULL);
	ft_snprintf(buffer, BUF_SIZE, fmt, NULL);
	TEST_ASSERT_EQUAL_STRING(test_buf, buffer);
}

TEST(print_pointer, 3)
{
	char *fmt = "%.5p";
	printf(" (%s) \n", fmt);
	snprintf(test_buf, BUF_SIZE, fmt, NULL);
	ft_snprintf(buffer, BUF_SIZE, fmt, NULL);
	TEST_ASSERT_EQUAL_STRING(test_buf, buffer);
}

TEST(print_pointer, 4)
{
	char *fmt = "%.p";
	printf(" (%s) \n", fmt);
	snprintf(test_buf, BUF_SIZE, fmt, NULL);
	ft_snprintf(buffer, BUF_SIZE, fmt, NULL);
	TEST_ASSERT_EQUAL_STRING(test_buf, buffer);
}

TEST(print_pointer, 5)
{
	char *fmt = "%-5p";
	printf(" (%s) \n", fmt);
	snprintf(test_buf, BUF_SIZE, fmt, NULL);
	ft_snprintf(buffer, BUF_SIZE, fmt, NULL);
	TEST_ASSERT_EQUAL_STRING(test_buf, buffer);
}
