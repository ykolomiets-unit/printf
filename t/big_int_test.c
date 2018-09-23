#include "unity.h"
#include "unity_fixture.h"
#include "big_int.h"

TEST_GROUP(big_int);

TEST_SETUP(big_int)
{
}

TEST_TEAR_DOWN(big_int)
{
}

TEST(big_int, set_zero)
{
	t_big_int	bi;

	bi_set_zero(&bi);
	TEST_ASSERT_EQUAL_UINT32(0, bi.length);
}

TEST(big_int, set_u32_zero)
{
	t_big_int	bi;

	bi_set_u32(&bi, 0);
	TEST_ASSERT_EQUAL_UINT32(0, bi.length);
}

TEST(big_int, set_u32_not_zero)
{
	t_big_int	bi;

	bi_set_u32(&bi, 255);
	TEST_ASSERT_EQUAL_UINT32(1, bi.length);
	TEST_ASSERT_EQUAL_UINT32(255, bi.blocks[0]);
}

TEST(big_int, set_u64_zero)
{
	t_big_int	bi;

	bi_set_u64(&bi, 0);
	TEST_ASSERT_EQUAL_UINT32(0, bi.length);
}

TEST(big_int, set_u64_lt_0xffffffff)
{
	t_big_int	bi;

	bi_set_u64(&bi, 255);
	TEST_ASSERT_EQUAL_UINT32(1, bi.length);
	TEST_ASSERT_EQUAL_UINT32(255, bi.blocks[0]);
}

TEST(big_int, set_u64_gt_0xffffffff)
{
	t_big_int	bi;

	bi_set_u64(&bi, 0xff00ff00ffffffff);
	TEST_ASSERT_EQUAL_UINT32(2, bi.length);
	TEST_ASSERT_EQUAL_UINT32(0xffffffff, bi.blocks[0]);
	TEST_ASSERT_EQUAL_UINT32(0xff00ff00, bi.blocks[1]);
}
