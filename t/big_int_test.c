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

TEST(big_int, compare_zero_with_zero)
{
	t_big_int	bi1;
	t_big_int	bi2;

	bi_set_zero(&bi1);
	bi_set_zero(&bi2);
	TEST_ASSERT_EQUAL_INT(0, bi_compare(&bi1, &bi2));
}

TEST(big_int, compare_equal)
{
	t_big_int	bi1;
	t_big_int	bi2;

	bi_set_u64(&bi1, 0xff00ff00ff00ff00);
	bi2 = bi1;
	TEST_ASSERT_EQUAL_INT(0, bi_compare(&bi1, &bi2));
}

TEST(big_int, compare_with_different_lengths)
{
	t_big_int	bi1;
	t_big_int	bi2;

	bi_set_u64(&bi1, 0xff00ff00ff00ff00);
	bi_set_u64(&bi2, 0xff00ff00);
	TEST_ASSERT_EQUAL_INT(1, bi_compare(&bi1, &bi2));
	TEST_ASSERT_EQUAL_INT(-1, bi_compare(&bi2, &bi1));
}

TEST(big_int, compare_with_same_lengths)
{
	t_big_int	bi1;
	t_big_int	bi2;

	bi_set_u64(&bi1, 0xff00ff00ff00ff00);
	bi_set_u64(&bi2, 0xff00ff00ffffffff);
	TEST_ASSERT_EQUAL_INT(-1, bi_compare(&bi1, &bi2));
	TEST_ASSERT_EQUAL_INT(1, bi_compare(&bi2, &bi1));
}
