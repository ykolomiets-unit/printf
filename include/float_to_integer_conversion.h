#ifndef FLOAT_TO_INTEGER_CONVERTION_H
# define FLOAT_TO_INTEGER_CONVERTION_H

# include "inttypes.h"

typedef union	s_float_union64
{
	double		floating_point;
	uint64_t	integer;
}				t_float_union64;

int				fu64_is_negative(t_float_union64 val);
uint32_t		fu64_get_exponent(t_float_union64 val);
uint64_t		fu64_get_mantissa(t_float_union64 val);

#endif
