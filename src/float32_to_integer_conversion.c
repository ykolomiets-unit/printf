#include "float_to_integer_conversion.h"

int				fu32_is_negative(t_float_union32 val)
{
	return ((val.integer >> 31) != 0);
}

uint32_t		fu32_get_exponent(t_float_union32 val)
{
	return ((val.integer >> 23) & 0xff);
}

uint32_t		fu32_get_mantissa(t_float_union32 val)
{
	return (val.integer & 0x7fffff);
}
