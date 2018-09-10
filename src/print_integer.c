#include "_printf.h"
#include "utils.h"
#include <inttypes.h>
#include <unistd.h>

static void get_base_register_sign(char spec, int *base,
									int *capitals, t_boolean *is_signed) 
{
	if (spec == 'd' || spec == 'D' || spec == 'i' || spec == 'u' || spec == 'U')
		*base = 10;
	else if (spec == 'x' || spec == 'X')
		*base = 16;
	else if (spec == 'o' || spec == 'O')
		*base = 8;
	if (spec == 'X')
		*capitals = 16;
	else
		*capitals = 0;
	if (spec == 'd' || spec == 'D' || spec == 'i')
		*is_signed = TRUE;
	else
		*is_signed = FALSE;
}

static int	num_in_buffer(uintmax_t u, int base, int capitals, char **buf)
{
	static char	digs[] = "0123456789abcdef0123456789ABCDEF";
	int			length;

	length = 0;
	do
	{
		**buf = digs[(u % base) + capitals];
		(*buf)--;
		u /= base;
		length++;
	} while (u != 0);
	return (length);
}

static char	*get_prefix(uintmax_t u, t_fms *fms, int base, int capitals)
{
	if (base == 8 && fms->altfmt)
		return ("0");
	else if (base == 16)
	{
		if (u == 0 || !fms->altfmt)
			return (0);
		return (capitals ? "0X" : "0x");
	}
	return (0);
}

static int	get_real_length(int buf_size, char sign_char, char *prefix, int precision)
{
	int	length;

	length = buf_size;
	if (sign_char)
		length++;
	if (prefix)
		length += ft_strlen(prefix);
	if (precision > 0)
		length += precision;
	return (length);
}

static int	print_spacepad_sign_prefix(t_printf *options, t_fms *fms, char sign_char, char *prefix)
{
	int	print_res;

	if (fms->padc == ' ' && !fms->left_adjust)
	{
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	}
	if (sign_char)
		if ((print_res = options->putc(options, sign_char)))
			return (print_res);
	if (prefix)
		while (*prefix)
			if ((print_res = options->putc(options, *prefix++)))
				return (print_res);
	return (0);
}

static int	print_zeropad(t_printf *options, t_fms *fms)
{
	int	print_res;

	if (fms->padc == '0')
	{
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, '0')))
				return (print_res);
	}
	else
	{
		while (--fms->precision >= 0)
			if ((print_res = options->putc(options, '0')))
				return (print_res);
	}
	return (0);
}

static int	print_buf_adjust(t_printf *options, t_fms *fms, char *buf_start, char *buf_end)
{
	int	print_res;

	while (++buf_start != buf_end)
		if ((print_res = options->putc(options, *buf_start)))
			return (print_res);
	if (fms->left_adjust)
	{
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	}
	return (0);
}

static int	print_num(uintmax_t u, t_printf *options,
					  t_fms *fms, int base, int capitals,
					  char sign_char)
{
	char		buffer[INT_BUF_SIZE];
	char		*p;
	char		*prefix;
	int			num_str_length;
	
	p = &buffer[INT_BUF_SIZE - 1];
	if (u == 0 && fms->precision == 0)
		num_str_length = 0;
	else
		num_str_length = num_in_buffer(u, base, capitals, &p);
	fms->precision -= num_str_length;
	prefix = get_prefix(u, fms, base, capitals);
	fms->length -= get_real_length(num_str_length, sign_char, prefix, fms->precision);
	print_spacepad_sign_prefix(options, fms, sign_char, prefix);
	print_zeropad(options, fms);
	print_buf_adjust(options, fms, p, &buffer[INT_BUF_SIZE]);
	return (0);
}


static int	print_signed_integer(t_printf *options, t_fms *fms, int base, int capitals)
{
	intmax_t	n;
	uintmax_t	u;
	char		sign_char;
	
	if (fms->length_modifier == LM_NONE)
		n = va_arg(*options->ap, int);
	else if (fms->length_modifier == LM_LONG)
		n = va_arg(*options->ap, long);
	else if (fms->length_modifier == LM_LONG_LONG)
		n = va_arg(*options->ap, long long);
	else if (fms->length_modifier == LM_SHORT)
		n = (short) va_arg(*options->ap, int);
	else if (fms->length_modifier == LM_SHORT_SHORT)
		n = (signed char) va_arg(*options->ap, int);
	else if (fms->length_modifier == LM_J)
		n = va_arg(*options->ap, intmax_t);
	else /*length_modifier == Z*/
		n = va_arg(*options->ap, ssize_t);
	if (n >= 0)
	{
		u = n;
		sign_char = fms->plus_sign;
	}
	else
	{
		u = -n;
		sign_char = '-';
	}
	return print_num(u, options, fms, base, capitals, sign_char);
}

static int	print_unsigned_integer(t_printf *options, t_fms *fms, int base, int capitals)
{
	uintmax_t	u;

	if (fms->length_modifier == LM_NONE)
		u = va_arg(*options->ap, unsigned);
	else if (fms->length_modifier == LM_LONG_LONG)
		u = va_arg(*options->ap, unsigned long long);
	else if (fms->length_modifier == LM_LONG)
		u = va_arg(*options->ap, unsigned long);
	else if (fms->length_modifier == LM_SHORT)
		u = (unsigned short) va_arg(*options->ap, int);
	else if (fms->length_modifier == LM_SHORT_SHORT)
		u = (unsigned char) va_arg(*options->ap, int);
	else if (fms->length_modifier == LM_J)
		u = va_arg(*options->ap, uintmax_t);
	else /* if (fms->length_modifier == J) */
		u = va_arg(*options->ap, size_t);
	return print_num(u, options, fms, base, capitals, 0);
}

int			print_integer(t_printf *options, t_fms *fms)
{
	int			base;
	int			capitals;
	t_boolean	is_signed;
	int			res;

	if (fms->precision != -1)
		fms->padc = ' ';
	get_base_register_sign(fms->specifier, &base, &capitals, &is_signed);
	if (is_signed)
		res = print_signed_integer(options, fms, base, capitals);
	else
		res = print_unsigned_integer(options, fms, base, capitals);
	return (res);
}
