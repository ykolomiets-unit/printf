#include "dragon4.h"
#include "float_to_integer_conversion.h"

static void			parse_double(double val, t_boolean *negative, uint32_t *float_exponent, uint64_t *float_mantissa)
{
	t_float_union64	float_union;

	float_union.floating_point = val;
	*negative = fu64_is_negative(float_union);
	*float_exponent = fu64_get_exponent(float_union);
	*float_mantissa = fu64_get_mantissa(float_union);
}

static void 		set_sign(t_print_float64_arg *arg, t_boolean negative, uint32_t *prefix_length)
{
	*prefix_length = 0;
	if (negative)
	{
		arg->out_buffer[0] = '-';
		++arg->out_buffer;
		--arg->buffer_size;
		++(*prefix_length);
	}
}

static t_format_arg		get_format_arg(t_print_float64_arg *arg, uint32_t float_exponent, uint64_t float_mantissa)
{
	t_format_arg	format_arg;

	if (float_exponent != 0)
	{
		format_arg.mantissa = (1UL << 52) | float_mantissa;
		format_arg.exponent = float_exponent - 1023 - 52;
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
	format_arg.out_buffer = arg->out_buffer;
	format_arg.buffer_size = arg->buffer_size;
	format_arg.precision = arg->precision;
	return (format_arg);
}

uint32_t			print_float64(t_print_float64_arg arg)
{
	t_boolean 		negative;
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
	parse_double(arg.value, &negative, &float_exponent, &float_mantissa);
	set_sign(&arg, negative, &prefix_length);
	if (float_exponent == 0x7ff)
		return (0); // TODO: infinity
	format_arg = get_format_arg(&arg, float_exponent, float_mantissa);
	if (arg.format == PRINT_FLOAT_FORMAT_POSITIONAL)
		return (format_positional(format_arg) + prefix_length);
	return (0);
}
