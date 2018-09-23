#include "unity.h"
#include "unity_fixture.h"
#include "dragon4.h"

TEST_GROUP(dragon4_log_base_2);

TEST_SETUP(dragon4_log_base_2)
{
}

TEST_TEAR_DOWN(dragon4_log_base_2)
{
}

TEST(dragon4_log_base_2, log_0)
{
	t_u32 res = log_base_2(0);
	TEST_ASSERT_EQUAL_UINT32(0, res);
}

TEST(dragon4_log_base_2, log_2)
{
	t_u32 res = log_base_2(2);
	TEST_ASSERT_EQUAL_UINT32(1, res);
}

TEST(dragon4_log_base_2, log_5)
{
	t_u32 res = log_base_2(5);
	TEST_ASSERT_EQUAL_UINT32(2, res);
}

TEST(dragon4_log_base_2, log_256)
{
	t_u32 res = log_base_2(256);
	TEST_ASSERT_EQUAL_UINT32(8, res);
}

TEST(dragon4_log_base_2, log_4096)
{
	t_u32 res = log_base_2(4096);
	TEST_ASSERT_EQUAL_UINT32(12, res);
}
