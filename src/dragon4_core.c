/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:10:14 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:10:16 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dragon4.h"
#include "big_int.h"
#include "math.h"

uint32_t	dragon4(t_dragon4_arg arg)
{
	char		*cur_digit;
	t_big_int	scale;
	t_big_int	scaled_value;
	t_big_int	scaled_margin_low;
	t_big_int	*p_scaled_margin_high;
	t_big_int	optional_margin_high;

	cur_digit = arg.out_buffer;
	if (arg.mantissa == 0)
	{
		*cur_digit = '0';
		*arg.out_exponent = 0;
		return (1);
	}
	if (arg.has_unequal_margins)
	{
		if (arg.exponent > 0)
		{
			bi_set_u64(&scaled_value, 4 * arg.mantissa);
			bi_shift_left(&scaled_value, (uint32_t)arg.exponent);
			bi_set_u32(&scale, 4);
			bi_pow2(&scaled_margin_low, (uint32_t)arg.exponent);
			bi_pow2(&optional_margin_high, (uint32_t)arg.exponent + 1);
		}
		else
		{
			bi_set_u64(&scaled_value, 4 * arg.mantissa);
			bi_pow2(&scale, -arg.exponent + 2);
			bi_set_u32(&scaled_margin_low, 1);
			bi_set_u32(&optional_margin_high, 2);
		}
		p_scaled_margin_high = &optional_margin_high;
	}
	else
	{
		if (arg.exponent > 0)
		{
			bi_set_u64(&scaled_value, 2 * arg.mantissa);
			bi_shift_left(&scaled_value, (uint32_t)arg.exponent);
			bi_set_u32(&scale, 2);
			bi_pow2(&scaled_margin_low, (uint32_t)arg.exponent);
		}
		else
		{
			bi_set_u64(&scaled_value, 2	* arg.mantissa);
			bi_pow2(&scale, -arg.exponent + 1);
			bi_set_u32(&scaled_margin_low, 1);
		}
		p_scaled_margin_high = &scaled_margin_low;
	}

	const double log10_2 = 0.30102999566398119521373889472449;
	int32_t digit_exponent = (int32_t)(ceil(((int32_t)arg.mantissa_high_bit_idx + arg.exponent) * log10_2 - 0.69));
	if (arg.cutoff_mode == CUTOFF_MODE_FRACTIONAL_LENGTH && digit_exponent <= -(int32_t)arg.cutoff_number)
		digit_exponent = -(int32_t)arg.cutoff_number + 1;
	
	if (digit_exponent > 0)
	{
		t_big_int	temp;
		bi_mult_by_pow10(&temp, &scale, (uint32_t)digit_exponent);
		scale = temp;
	}
	else if (digit_exponent < 0)
	{
		t_big_int	pow10;
		bi_pow10(&pow10, -digit_exponent);

		t_big_int	temp;
		bi_mult_bi_by_bi(&temp, &scaled_value, &pow10);
		scaled_value = temp;

		bi_mult_bi_by_bi(&temp, &scaled_margin_low, &pow10);
		scaled_margin_low = temp;

		if (p_scaled_margin_high != &scaled_margin_low)
			bi_mult_bi_by_2(p_scaled_margin_high, &scaled_margin_low);
	}

	if (bi_compare(&scaled_value, &scale) >= 0)
	{
		digit_exponent = digit_exponent + 1;
	}
	else
	{
		bi_mult_bi_by_10_inplace(&scaled_value);
		bi_mult_bi_by_10_inplace(&scaled_margin_low);
		if (p_scaled_margin_high != &scaled_margin_low)
			bi_mult_bi_by_2(p_scaled_margin_high, &scaled_margin_low);
	}

	int32_t	cutoff_exponent = digit_exponent - arg.buffer_size;
	if (arg.cutoff_mode == CUTOFF_MODE_TOTAL_LENGTH)
	{
		int32_t	desired_cutoff_exponent = digit_exponent - (int32_t)arg.cutoff_number;
		if (desired_cutoff_exponent > cutoff_exponent)
			cutoff_exponent = desired_cutoff_exponent;
	}
	else if (arg.cutoff_mode == CUTOFF_MODE_FRACTIONAL_LENGTH)
	{
		int32_t	desired_cutoff_exponent = -(int32_t)arg.cutoff_number;
		if (desired_cutoff_exponent > cutoff_exponent)
			cutoff_exponent = desired_cutoff_exponent;
	}

	*arg.out_exponent = digit_exponent - 1;

	uint32_t	hi_block = scale.blocks[scale.length - 1];
	if (hi_block < 8 ||	hi_block > 429496729)
	{
		uint32_t	hi_block_log2 =	log_base_2_uint32(hi_block);
		uint32_t	shift = (32 + 27 -	hi_block_log2) % 32;

		bi_shift_left(&scale, shift);
		bi_shift_left(&scaled_value, shift);
		bi_shift_left(&scaled_margin_low, shift);
		if (p_scaled_margin_high != &scaled_margin_low)
			bi_mult_bi_by_2(p_scaled_margin_high, &scaled_margin_low);
	}

	t_boolean	low;
	t_boolean	high;
	uint32_t	output_digit;

	if (arg.cutoff_mode == CUTOFF_MODE_UNIQUE)
	{
		while (1)
		{
			digit_exponent = digit_exponent - 1;
			output_digit = bi_divide_with_remainder_maxquotient9(&scaled_value, &scale);

			t_big_int	scaled_value_high;
			bi_add(&scaled_value_high, &scaled_value, p_scaled_margin_high);

			low = bi_compare(&scaled_value, &scaled_margin_low) < 0;
			high = bi_compare(&scaled_value_high, &scale) >	0;
			if (low | high | (digit_exponent == cutoff_exponent))
				break ;
			*cur_digit = (char)('0' + output_digit);
			cur_digit++;

			bi_mult_bi_by_10_inplace(&scaled_value);
			bi_mult_bi_by_10_inplace(&scaled_margin_low);
			if (p_scaled_margin_high != &scaled_margin_low)
				bi_mult_bi_by_2(p_scaled_margin_high, &scaled_margin_low);
		}
	}
	else
	{
		low = 0;
		high = 0;
		while (1)
		{
			digit_exponent = digit_exponent - 1;
			output_digit = bi_divide_with_remainder_maxquotient9(&scaled_value, &scale);
			if (bi_is_zero(&scaled_value) | (digit_exponent == cutoff_exponent))
				break ;
			*cur_digit = (char)('0' + output_digit);
			cur_digit++;
			bi_mult_bi_by_10_inplace(&scaled_value);
		}
	}

	t_boolean	round_down = low;
	if (low == high)
	{
		bi_mult_bi_by_2_inplace(&scaled_value);
		int32_t compare = bi_compare(&scaled_value, &scale);
		round_down = compare < 0;
		if (compare == 0)
			round_down = (output_digit & 1)	== 0;
	}

	if (round_down)
	{
		*cur_digit = (char)('0' + output_digit);
		cur_digit++;
	}
	else
	{
		if (output_digit == 9)
		{
			while (1)
			{
				if (cur_digit == arg.out_buffer)
				{
					*cur_digit = '1';
					cur_digit++;
					*arg.out_exponent = 1;
					break;
				}

				--cur_digit;
				if (*cur_digit != '9')
				{
					*cur_digit += 1;
					cur_digit++;
					break;
				}
			}
		}
		else
		{
			*cur_digit = (char) ('0' + output_digit + 1);
			cur_digit++;
		}
	}
	uint32_t	output_length = (uint32_t)(cur_digit - arg.out_buffer);
	return (output_length);
}
