#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include "ft_printf.h"

TEST_GROUP(ft_printf);


TEST_SETUP(ft_printf)
{
}

TEST_TEAR_DOWN(ft_printf)
{
}

TEST(ft_printf, test)
{
	TEST_ASSERT_EQUAL_INT(0, ft_printf("abc"));
}
