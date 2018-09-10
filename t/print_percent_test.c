#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include "ft_printf.h"
#include <stdio.h>

#define BUF_SIZE 1024

static char	buffer[BUF_SIZE];

TEST_GROUP(print_percent);

TEST_SETUP(print_percent)
{
	bzero(buffer, BUF_SIZE);
}

TEST_TEAR_DOWN(print_percent)
{
	bzero(buffer, BUF_SIZE);
}

TEST(print_percent, 1)
{
	char *fmt = "%%";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt);
	TEST_ASSERT_EQUAL_STRING("%", buffer);
}

TEST(print_percent, 2)
{
	char *fmt = "%5%";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt);
	TEST_ASSERT_EQUAL_STRING("    %", buffer);
}

TEST(print_percent, 3)
{
	char *fmt = "%-5%";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt);
	TEST_ASSERT_EQUAL_STRING("%    ", buffer);
}

TEST(print_percent, 4)
{
	char *fmt = "%05%";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt);
	TEST_ASSERT_EQUAL_STRING("0000%", buffer);
}
