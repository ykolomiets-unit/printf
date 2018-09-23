#include "dragon4.h"

# define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n

t_u32 log_base_2(t_u32 val)
{
	static const t_u8 log_table[256] = 
	{
		0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
		LT(4),
		LT(5), LT(5),
		LT(6), LT(6), LT(6), LT(6), 
		LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7),
	};
	t_u32	temp;

	temp = val >> 24;
	if (temp)
		return (24 + log_table[temp]);
	temp = val >> 16;
	if (temp)
		return (16 + log_table[temp]);
	temp = val >> 8;
	if (temp)
		return (8 + log_table[temp]);
	return (log_table[val]);
}
