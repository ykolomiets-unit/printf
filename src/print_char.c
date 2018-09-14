#include "_printf.h"
#include <wchar.h>

#define BITS_IN_ULONG ((int)sizeof(unsigned long) * 8)
#define UTF8_2_BYTES_MASK 0xC0
#define UTF8_3_BYTES_MASK 0xE0
#define UTF8_4_BYTES_MASK 0xF0
#define UTF8_AUX_BYTE_MASK 0x80
#define SIX_BITS_MASK 0x3F
#define FIVE_BITS_MASK 0x1F
#define FOUR_BITS_MASK 0xF
#define THREE_BITS_MASK 0x6

int		get_active_bits_count(unsigned long int u)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (i++ <= BITS_IN_ULONG)
	{
		if (u & 0x1)
			count = i;
		u >>= 1;
	}
	return (count);
}

int		wchartobuf(wchar_t ch, char *buf)
{
	int	active_bits;

	active_bits = get_active_bits_count(ch);
	if (active_bits <= 7)
	{
		buf[0] = (char)ch;
		return (1);
	}
	else if (active_bits <= 11)
	{
		buf[0] = (ch & SIX_BITS_MASK) | UTF8_AUX_BYTE_MASK;
		ch >>= 6;
		buf[1] = (ch & FIVE_BITS_MASK) | UTF8_2_BYTES_MASK;
		return (2);
	}
	else if (active_bits <= 16)
	{
		buf[0] = (ch & SIX_BITS_MASK) | UTF8_AUX_BYTE_MASK;
		ch >>= 6;
		buf[1] = (ch & SIX_BITS_MASK) | UTF8_AUX_BYTE_MASK;
		ch >>= 6;
		buf[2] = (ch & FOUR_BITS_MASK) | UTF8_3_BYTES_MASK;
		return (3);
	}
	else if (active_bits <= 21)
	{
		buf[0] = (ch & SIX_BITS_MASK) | UTF8_AUX_BYTE_MASK;
		ch >>= 6;
		buf[1] = (ch & SIX_BITS_MASK) | UTF8_AUX_BYTE_MASK;
		ch >>= 6;
		buf[2] = (ch & SIX_BITS_MASK) | UTF8_AUX_BYTE_MASK;
		ch >>= 6;
		buf[3] = (ch & FOUR_BITS_MASK) | UTF8_4_BYTES_MASK;
		return (4);
	}
	return (0);
}

int		print_char(t_printf* options, t_fms *fms)
{
	wchar_t	wc;
	int		print_res;
	char	buf[4];
	int		i;

	if (fms->length_modifier == LM_LONG)
	{
		wc = (wchar_t)va_arg(*options->ap, wint_t);
		i = wchartobuf(wc, buf);
	}
	else
	{
		buf[0] = va_arg(*options->ap, int);
		i = 1;
	}
	fms->length -= i;
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	while (--i >= 0)
		if ((print_res = options->putc(options, buf[i])))
			return (print_res);
	if (fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	return (0);
}
