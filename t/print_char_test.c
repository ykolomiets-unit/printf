#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include "ft_printf.h"
#include <stdio.h>

#define BUF_SIZE 1024

static char	buffer[BUF_SIZE];

TEST_GROUP(print_char);

TEST_SETUP(print_char)
{
	bzero(buffer, BUF_SIZE);
}

TEST_TEAR_DOWN(print_char)
{
	bzero(buffer, BUF_SIZE);
}

TEST(print_char, 1)
{
	char *fmt = "%c";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, 'a');
	TEST_ASSERT_EQUAL_STRING("a", buffer);
}

TEST(print_char, 2)
{
	char *fmt = "%5c";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, 'a');
	TEST_ASSERT_EQUAL_STRING("    a", buffer);
}

TEST(print_char, 3)
{
	char *fmt = "%-5c";
	printf(" (%s) \n", fmt);
	ft_snprintf(buffer, BUF_SIZE, fmt, 'a');
	TEST_ASSERT_EQUAL_STRING("a    ", buffer);
}
