#include "utils.h"

static int get_active_bits_count(wchar_t ch)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (i++ <= BITS_IN_WCHAR)
	{
		if (ch & 0x1)
			count = i;
		ch >>= 1;
	}
	return (count);
}

int			wchar_length_in_bytes(wchar_t ch)
{
	int	active_bits;

	active_bits = get_active_bits_count(ch);
	if (active_bits <= 7)
		return (1);
	else if (active_bits <= 11)
		return (2);
	else if (active_bits <= 16)
		return (3);
	else if (active_bits <= 21)
		return (4);
	return (0);
}

int			wchartobuf(wchar_t ch, char *buf)
{
	int	bytes;
	int	i;

	bytes = wchar_length_in_bytes(ch);
	if (bytes == 1)
		buf[0] = (char)ch;
	else if (bytes <= 4)
	{
		i = 0;
		while (i < bytes - 1)
		{
			buf[i++] = (ch & SIX_BITS_MASK) | UTF8_AUX_BYTE_MASK;
			ch >>= 6;
		}
		if (bytes == 2)
			buf[1] = (ch & FIVE_BITS_MASK) | UTF8_2_BYTES_MASK;
		else if (bytes == 3)
			buf[2] = (ch & FOUR_BITS_MASK) | UTF8_3_BYTES_MASK;
		else if (bytes == 4)
			buf[3] = (ch & FOUR_BITS_MASK) | UTF8_4_BYTES_MASK;
	}
	return (bytes);
}
