#include "big_int.h"


void		bi_set_zero(t_big_int *big_int)
{
	big_int->length = 0;
}

t_boolean	bi_is_zero(t_big_int *big_int)
{
	return	big_int->length == 0;
}

void		bi_set_u32(t_big_int *big_int, uint32_t val)
{
	if (val != 0)
	{
		big_int->blocks[0] = val;
		big_int->length = 1;
	}
	else
	{
		big_int->length = 0;
	}
}

uint32_t	bi_get_u32(t_big_int *big_int)
{
	return (big_int->length == 0 ? 0 : big_int->blocks[0]);
}

void		bi_set_u64(t_big_int *big_int, uint64_t val)
{
	if (val > 0xFFFFFFFF)
	{
		big_int->blocks[0] = val & 0xFFFFFFFF;
		val	>>= 32;
		big_int->blocks[1] = val & 0xFFFFFFFF;
		big_int->length = 2;
	}
	else if (val != 0)
	{
		big_int->blocks[0] = val & 0xFFFFFFFF;
		big_int->length = 1;
	}
	else
	{
		big_int->length = 0;
	}
}
