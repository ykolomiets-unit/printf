#include "float_to_integer_conversion.h"

int				fu64_is_negative(t_float_union64 val)
{
	return ((val.integer >> 63) != 0);
}

uint32_t		fu64_get_exponent(t_float_union64 val)
{
	return ((val.integer >> 52) & 0x7FF);
}

uint64_t		fu64_get_mantissa(t_float_union64 val)
{
	return (val.integer & 0xFFFFFFFFFFFFFull);
}
