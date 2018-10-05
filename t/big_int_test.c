#include "unity.h"
#include "unity_fixture.h"
#include "big_int.h"
#include <stdio.h>

TEST_GROUP(big_int);

TEST_SETUP(big_int)
{
}

TEST_TEAR_DOWN(big_int)
{
}

static void print_big_int(t_big_int *val)
{
	printf("val = ");
	if (val->length == 0)
		printf("0\n");
	else
	{
		for (int i = val->length - 1; i >= 0; i--)
		{
			printf("%#x ", val->blocks[i]);
		}
		printf("\n");
	}
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

	bi_set_u32(&bi1, 0);
	bi_set_u32(&bi2, 0);
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

TEST(big_int, add_zeroes)
{
	t_big_int	bi1;
	t_big_int	bi2;
	t_big_int	result;

	bi_set_u32(&bi1, 0);
	bi_set_u32(&bi2, 0);
	bi_add(&result, &bi1, &bi2);
	TEST_ASSERT_EQUAL_UINT32(0, result.length);
}

TEST(big_int, add_small_numbers)
{
	t_big_int	bi1;
	t_big_int	bi2;
	t_big_int	result;

	bi_set_u32(&bi1, 325);
	bi_set_u32(&bi2, 175);
	bi_add(&result, &bi1, &bi2);
	TEST_ASSERT_EQUAL_UINT32(1, result.length);
	TEST_ASSERT_EQUAL_UINT32(500, result.blocks[0]);
}

TEST(big_int, add_big_numbers)
{
	t_big_int	bi1;
	t_big_int	bi2;
	t_big_int	result;

	bi_set_u64(&bi1, 0xffffffffffffffff);
	bi_set_u64(&bi2, 0xffffffffffffffff);
	bi_add(&result, &bi1, &bi2);
	TEST_ASSERT_EQUAL_UINT32(3, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x1, result.blocks[2]);
	TEST_ASSERT_EQUAL_UINT32(0xffffffff, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0xfffffffe, result.blocks[0]);
}

TEST(big_int, add_with_different_length)
{
	t_big_int	bi1;
	t_big_int	bi2;
	t_big_int	result;

	bi_set_u64(&bi1, 0xffffffff);
	bi_set_u64(&bi2, 0xffffffffffffffff);
	bi_add(&result, &bi1, &bi2);
	TEST_ASSERT_EQUAL_UINT32(3, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x1, result.blocks[2]);
	TEST_ASSERT_EQUAL_UINT32(0x00000000, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0xfffffffe, result.blocks[0]);
}

TEST(big_int, mult_bi_by_bi_1)
{
	t_big_int	bi1;
	t_big_int	bi2;
	t_big_int	result;

	bi_set_u64(&bi1, 0x2);
	bi_set_u64(&bi2, 0xffffffffffffffff);
	bi_mult_bi_by_bi(&result, &bi1, &bi2);
	TEST_ASSERT_EQUAL_UINT32(3, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x1, result.blocks[2]);
	TEST_ASSERT_EQUAL_UINT32(0xffffffff, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0xfffffffe, result.blocks[0]);
}

TEST(big_int, mult_bi_by_bi_2)
{
	t_big_int	bi1;
	t_big_int	bi2;
	t_big_int	result;

	bi_set_u64(&bi1, 0xffffff);
	bi_set_u64(&bi2, 0xffff);
	bi_mult_bi_by_bi(&result, &bi1, &bi2);
	TEST_ASSERT_EQUAL_UINT32(2, result.length);
	TEST_ASSERT_EQUAL_UINT32(0xff, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0xfeff0001, result.blocks[0]);
}

TEST(big_int, mult_bi_by_int)
{
	t_big_int	bi1;
	t_big_int	result;

	bi_set_u64(&bi1, 0xffffff);
	bi_mult_bi_by_uint32(&result, &bi1, 0xffff);
	TEST_ASSERT_EQUAL_UINT32(2, result.length);
	TEST_ASSERT_EQUAL_UINT32(0xff, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0xfeff0001, result.blocks[0]);
}

TEST(big_int, mult_bi_by_2_without_carry)
{
	t_big_int	bi1;
	t_big_int	result;

	bi_set_u64(&bi1, 0xff);
	bi_mult_bi_by_2(&result, &bi1);
	TEST_ASSERT_EQUAL_UINT32(1, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x1fe, result.blocks[0]);
}

TEST(big_int, mult_bi_by_2_with_carry)
{
	t_big_int	bi1;
	t_big_int	result;

	bi_set_u64(&bi1, 0xffffffff);
	bi_mult_bi_by_2(&result, &bi1);
	TEST_ASSERT_EQUAL_UINT32(2, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x1, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0xfffffffe, result.blocks[0]);
}

TEST(big_int, mult_bi_by_2_in_place_without_carry)
{
	t_big_int	result;

	bi_set_u64(&result, 0xffff);
	bi_mult_bi_by_2_inplace(&result);
	TEST_ASSERT_EQUAL_UINT32(1, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x1fffe, result.blocks[0]);
}

TEST(big_int, mult_bi_by_2_in_place_with_carry)
{
	t_big_int	result;

	bi_set_u64(&result, 0xffffffffffffffff);
	bi_mult_bi_by_2_inplace(&result);
	TEST_ASSERT_EQUAL_UINT32(3, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x1, result.blocks[2]);
	TEST_ASSERT_EQUAL_UINT32(0xffffffff, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0xfffffffe, result.blocks[0]);
}

TEST(big_int, mult_bi_by_10_in_place_without_carry)
{
	t_big_int	result;

	bi_set_u64(&result, 0xffffff);
	bi_mult_bi_by_10_inplace(&result);
	TEST_ASSERT_EQUAL_UINT32(1, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x9fffff6, result.blocks[0]);
}

TEST(big_int, mult_bi_by_10_in_place_with_carry)
{
	t_big_int	result;

	bi_set_u64(&result, 0xffffffffffffffff);
	bi_mult_bi_by_10_inplace(&result);
	TEST_ASSERT_EQUAL_UINT32(3, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x9, result.blocks[2]);
	TEST_ASSERT_EQUAL_UINT32(0xffffffff, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0xfffffff6, result.blocks[0]);
}

TEST(big_int, pow10_5)
{
	t_big_int	result;

	bi_pow10(&result, 5);
	TEST_ASSERT_EQUAL_UINT32(1, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x186a0, result.blocks[0]);
}

TEST(big_int, pow10_25)
{
	t_big_int	result;

	bi_pow10(&result, 25);
	TEST_ASSERT_EQUAL_UINT32(3, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x84595, result.blocks[2]);
	TEST_ASSERT_EQUAL_UINT32(0x16140148, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0x4A000000, result.blocks[0]);
}

TEST(big_int, pow10_32)
{
	t_big_int	result;

	bi_pow10(&result, 32);
	TEST_ASSERT_EQUAL_UINT32(4, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x4EE, result.blocks[3]);
	TEST_ASSERT_EQUAL_UINT32(0x2D6D415B, result.blocks[2]);
	TEST_ASSERT_EQUAL_UINT32(0x85ACEF81, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0x00000000, result.blocks[0]);
}

TEST(big_int, mult_pow10_2)
{
	t_big_int	result;
	t_big_int	bi;

	bi_set_u32(&bi, 0xff00ff00);
	bi_mult_by_pow10(&result, &bi, 2);
	TEST_ASSERT_EQUAL_UINT32(2, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x63, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0x9C639C00, result.blocks[0]);
}

TEST(big_int, mult_pow10_9)
{
	t_big_int	result;
	t_big_int	bi;

	bi_set_u32(&bi, 0xff00ff00);
	bi_mult_by_pow10(&result, &bi, 9);
	TEST_ASSERT_EQUAL_UINT32(2, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x3B5F6A95, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0x2F360000, result.blocks[0]);
}

TEST(big_int, pow2_2)
{
	t_big_int	result;

	bi_pow2(&result, 2);
	TEST_ASSERT_EQUAL_UINT32(1, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x4, result.blocks[0]);
}

TEST(big_int, pow2_127)
{
	t_big_int	result;

	bi_pow2(&result, 127);
	TEST_ASSERT_EQUAL_UINT32(4, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x80000000, result.blocks[3]);
	TEST_ASSERT_EQUAL_UINT32(0, result.blocks[2]);
	TEST_ASSERT_EQUAL_UINT32(0, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0, result.blocks[0]);
}

TEST(big_int, shift_left_1)
{
	t_big_int	result;

	bi_set_u64(&result, 0x00ffffff);
	bi_shift_left(&result, 1);
	TEST_ASSERT_EQUAL_UINT32(1, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x01fffffe, result.blocks[0]);
}

TEST(big_int, shift_left_32)
{
	t_big_int	result;

	bi_set_u64(&result, 0x00ffffff);
	bi_shift_left(&result, 32);
	TEST_ASSERT_EQUAL_UINT32(2, result.length);
	TEST_ASSERT_EQUAL_UINT32(0x00ffffff, result.blocks[1]);
	TEST_ASSERT_EQUAL_UINT32(0x0, result.blocks[0]);
}
