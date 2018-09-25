#include "big_int.h"

static uint32_t	get_pow10_uint32(uint32_t pow)
{
	static uint32_t power_of_10[] =
	{
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
	};

	return (power_of_10[pow]);
}

static t_big_int	*get_pow10_big_int(uint32_t pow)
{
	static t_big_int power_of_10[] =
	{
		{ 1, { 100000000 } },
		{ 2, { 0x6fc10000, 0x002386f2 } },
		{ 4, { 0x00000000, 0x85acef81, 0x2d6d415b, 0x000004ee, } },
		{ 7, { 0x00000000, 0x00000000, 0xbf6a1f01, 0x6e38ed64,
				0xdaa797ed, 0xe93ff9f4, 0x00184f03, } },
		{ 14, { 0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x2e953e01, 0x03df9909, 0x0f1538fd, 0x2374e42f,
				0xd3cff5ec, 0xc404dc08, 0xbccdb0da, 0xa6337f19,
				0xe91f2603, 0x0000024e, } },
		{ 27, { 0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,	0x00000000,
				0x982e7c01, 0xbed3875b, 0xd8d99f72, 0x12152f87,
				0x6bde50c6, 0xcf4a6e70,	0xd595d80f, 0x26b2716e,
				0xadc666b0, 0x1d153624, 0x3c42d35a, 0x63ff540e,
				0xcc5573c0, 0x65f9ef17, 0x55bc28f2, 0x80dcc7f7,
				0xf46eeddc, 0x5fdcefce, 0x000553f7, } }
	};

	return (&power_of_10[pow]);
}

static void			swap_bi_pointers(t_big_int **a, t_big_int **b)
{
	t_big_int	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void				bi_pow10(t_big_int *result, uint32_t exp)
{
	t_big_int	temp1;
	t_big_int	temp2;
	t_big_int	*cur_temp;
	t_big_int	*next_temp;
	uint32_t	table_idx;

	cur_temp = &temp1;
	next_temp = &temp2;
	bi_set_u32(cur_temp, get_pow10_uint32(exp & 0x7));
	exp >>= 3;
	table_idx = 0;
	while (exp)
	{
		if (exp & 1)
		{
			bi_mult_bi_by_bi(next_temp, cur_temp, get_pow10_big_int(table_idx));
			swap_bi_pointers(&next_temp, &cur_temp);
		}
		table_idx++;
		exp >>= 1;
	}
	*result = *cur_temp;
}
 
