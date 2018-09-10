#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include "ft_printf.h"

#define BUF_SIZE 1024

static char	buffer[BUF_SIZE];

TEST_GROUP(ft_snprintf);

TEST_SETUP(ft_snprintf)
{
	bzero(buffer, BUF_SIZE);
}

TEST_TEAR_DOWN(ft_snprintf)
{
	bzero(buffer, BUF_SIZE);
}

TEST(ft_snprintf, snptinf)
{
	ft_snprintf(buffer, BUF_SIZE, "ABCDEFGH");
	TEST_ASSERT_EQUAL_STRING("ABCDEFGH", buffer);
}
