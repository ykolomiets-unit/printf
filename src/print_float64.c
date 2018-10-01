#include "dragon4.h"
#include "float_to_integer_conversion.h"

uint32_t			print_float64(t_print_float64_arg arg)
{
	t_float_union64	float_union;
	uint32_t		float_exponent;
	uint64_t		float_mantissa;
	uint32_t		prefix_length;
	t_format_arg	format_arg;

	if (arg.buffer_size == 0)
		return (0);
	if (arg.buffer_size == 1)
	{
		arg.out_buffer[0] = '\0';
		return (0);
	}
	float_union.floating_point = arg.value;
	float_exponent = fu64_get_exponent(float_union);
	float_mantissa = fu64_get_mantissa(float_union);
	prefix_length = 0;
	if (fu64_is_negative(float_union))
	{
		arg.out_buffer[0] = '-';
		++arg.out_buffer;
		--arg.buffer_size;
		++prefix_length;
	}
	if (float_exponent == 0x7ff)
	{
		return (0); // TODO: infinity
	}
	else
	{
		if (float_exponent != 0)
		{
			format_arg.mantissa = (1UL << 52) | float_mantissa;
			format_arg.exponent =	float_exponent - 1023 - 52;
			format_arg.mantissa_high_bit_idx = 52;
			format_arg.has_unequal_margins = (float_exponent != 1) && (float_mantissa != 0);
		}
		else
		{
			format_arg.mantissa = float_mantissa;
			format_arg.exponent = 1 - 1023 - 52;
			format_arg.mantissa_high_bit_idx = log_base_2_uint64(format_arg.mantissa);
			format_arg.has_unequal_margins = 0;
		}
	}
	format_arg.out_buffer = arg.out_buffer;
	format_arg.buffer_size = arg.buffer_size;
	format_arg.precision = arg.precision;
	if (arg.format == PRINT_FLOAT_FORMAT_POSITIONAL)
	{
		return (format_positional(format_arg) + prefix_length);
	}
	return (0);
}
