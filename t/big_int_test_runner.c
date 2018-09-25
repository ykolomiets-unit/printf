#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP_RUNNER(big_int)
{
	printf("\n\nbig_int\n");	
	RUN_TEST_CASE(big_int, set_zero);
	RUN_TEST_CASE(big_int, set_u32_zero);
	RUN_TEST_CASE(big_int, set_u32_not_zero);
	RUN_TEST_CASE(big_int, set_u64_zero);
	RUN_TEST_CASE(big_int, set_u64_lt_0xffffffff);
	RUN_TEST_CASE(big_int, set_u64_gt_0xffffffff);
	RUN_TEST_CASE(big_int, compare_zero_with_zero);
	RUN_TEST_CASE(big_int, compare_equal);
	RUN_TEST_CASE(big_int, compare_with_different_lengths);
	RUN_TEST_CASE(big_int, compare_with_same_lengths);
	RUN_TEST_CASE(big_int, add_zeroes);
	RUN_TEST_CASE(big_int, add_small_numbers);
	RUN_TEST_CASE(big_int, add_big_numbers);
	RUN_TEST_CASE(big_int, add_with_different_length);
	RUN_TEST_CASE(big_int, mult_bi_by_bi_1);
	RUN_TEST_CASE(big_int, mult_bi_by_bi_2);
	RUN_TEST_CASE(big_int, mult_bi_by_int);
	RUN_TEST_CASE(big_int, mult_bi_by_2_without_carry);
	RUN_TEST_CASE(big_int, mult_bi_by_2_with_carry);
	RUN_TEST_CASE(big_int, mult_bi_by_2_in_place_without_carry);
	RUN_TEST_CASE(big_int, mult_bi_by_2_in_place_with_carry);
	RUN_TEST_CASE(big_int, mult_bi_by_10_in_place_without_carry);
	RUN_TEST_CASE(big_int, mult_bi_by_10_in_place_with_carry);
	RUN_TEST_CASE(big_int, pow10_5);
	RUN_TEST_CASE(big_int, pow10_25);
	RUN_TEST_CASE(big_int, pow10_32);
}
