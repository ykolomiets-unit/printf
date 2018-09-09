#include "_printf.h"
#include "utils.h"
#include <unistd.h>
#include <inttypes.h>

#include <stdio.h>

static void	parse_flag(const char **fmt, t_fms *fms)
{
	char	c;

	c = **fmt;
	if (c == '#')
		fms->altfmt = TRUE;
	else if (**fmt == '-')
	{
		fms->left_adjust = TRUE;
		fms->padc = ' ';
	}
	else if (c == '+')
		fms->plus_sign = '+';
	else if (c == ' ' && !fms->plus_sign)
		fms->plus_sign = ' ';
	else if (c == '0' && !fms->left_adjust && fms->precision == -1)
		fms->padc = '0';
	(*fmt)++;
}

static void	parse_length(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	c = **fmt;
	fms->length = 0;
	if (IS_DIGIT(c))
	{
		while (IS_DIGIT(c))
		{
			fms->length = fms->length * 10 + CHAR_TO_DIGIT(c);
			(*fmt)++;
			c = **fmt;
		}
	}
	else if (c == '*')
	{
		fms->length = va_arg(*ap, int);
		if (fms->length < 0) 
		{
			fms->left_adjust = TRUE;
			fms->length = -fms->length;
		}
		(*fmt)++;
	}
}

static void	parse_precision(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	c = **fmt;
	if (c == '.')
	{
		fms->padc = ' ';
		(*fmt)++;
		c = **fmt;
		fms->precision = 0;
		if (IS_DIGIT(c))
		{
			while (IS_DIGIT(c))
			{
				fms->precision = fms->precision * 10 + CHAR_TO_DIGIT(c);
				(*fmt)++;
				c = **fmt;
			}
		}
		else if (c == '*')
		{
			fms->precision = va_arg(*ap, int);
			(*fmt)++;
		}
	}
}

static void set_length_modifier(t_fms *fms, t_length_modifier modifier)
{
	if (fms->length_modifier < modifier)
		fms->length_modifier = modifier;
}

static void	parse_length_modifier(const char **fmt, t_fms *fms)
{
	if (**fmt == 'h')
	{
		if (*(*fmt + 1) == 'h')
		{
			(*fmt)++;
			set_length_modifier(fms, SHORT_SHORT);
		}
		else
			set_length_modifier(fms, SHORT);
	}
	else if (**fmt == 'l')
	{
		if (*(*fmt + 1) == 'l')
		{
			(*fmt)++;
			set_length_modifier(fms, LONG_LONG);
		}
		else
			set_length_modifier(fms, LONG);
	}
	else if (**fmt == 'z')
		set_length_modifier(fms, Z);
	else if (**fmt == 'j')
		set_length_modifier(fms, J);
	(*fmt)++;
}

static void parse_specifier(const char **fmt, t_fms *fms)
{
	char	c;

	c = **fmt;
	if (c == 'U' || c == 'D' || c == 'O')
		fms->length_modifier = LONG;
	fms->specifier = c;
	(*fmt)++;
}

static int	is_flag(char c)
{
	if (c == '#' || c == ' ' || c == '0' || c == '+' || c == '-')
		return (1);
	return (0);
}

static int	is_length_start(char c)
{
	if (IS_DIGIT(c) || c == '*')
		return (1);
	return (0);
}

static int	is_precision_start(char c)
{
	if (c == '.')
		return (1);
	return (0);
}

static int	is_length_modifier_start(char c)
{
	if (c == 'h' || c == 'l' || c == 'z' || c == 'j')
		return (1);
	return (0);
}

static int	is_conversion_specifier(char c)
{
	static char	specifiers[] = "%douxiDOUX";
	char		*p;

	p = specifiers;
	while (*p)
	{
		if (c == *p)
			return (1);
		p++;
	}
	return (0);
}

static int	parse_fms(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	do
	{
		c = **fmt;
		if (is_flag(c))
			parse_flag(fmt, fms);
		else if (is_length_start(c))
			parse_length(fmt, fms, ap);
		else if (is_precision_start(c))
			parse_precision(fmt, fms, ap);
		else if (is_length_modifier_start(c))
			parse_length_modifier(fmt, fms);
		else if (is_conversion_specifier(c))
		{
			parse_specifier(fmt, fms);
			break;
		}
		else
			break;
	} while(c);
	return (0);
}

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
	
	if (fms->length_modifier == NONE)
		n = va_arg(*options->ap, int);
	else if (fms->length_modifier == LONG)
		n = va_arg(*options->ap, long);
	else if (fms->length_modifier == LONG_LONG)
		n = va_arg(*options->ap, long long);
	else if (fms->length_modifier == SHORT)
		n = (short) va_arg(*options->ap, int);
	else if (fms->length_modifier == SHORT_SHORT)
		n = (signed char) va_arg(*options->ap, int);
	else if (fms->length_modifier == J)
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

	if (fms->length_modifier == NONE)
		u = va_arg(*options->ap, unsigned);
	else if (fms->length_modifier == LONG_LONG)
		u = va_arg(*options->ap, unsigned long long);
	else if (fms->length_modifier == LONG)
		u = va_arg(*options->ap, unsigned long);
	else if (fms->length_modifier == SHORT)
		u = (unsigned short) va_arg(*options->ap, int);
	else if (fms->length_modifier == SHORT_SHORT)
		u = (unsigned char) va_arg(*options->ap, int);
	else if (fms->length_modifier == J)
		u = va_arg(*options->ap, uintmax_t);
	else /* if (fms->length_modifier == J) */
		u = va_arg(*options->ap, size_t);
	return print_num(u, options, fms, base, capitals, 0);
}

static int	print_integer(t_printf *options, t_fms *fms)
{
	int			base;
	int			capitals;
	t_boolean	is_signed;
	int			res;

	get_base_register_sign(fms->specifier, &base, &capitals, &is_signed);
	if (is_signed)
		res = print_signed_integer(options, fms, base, capitals);
	else
		res = print_unsigned_integer(options, fms, base, capitals);
	return (res);
}

static int	is_integer_specifier(char spec)
{
	if (spec == 'd' || spec == 'D' ||
		spec == 'u' || spec == 'U' || 
		spec == 'i' ||
		spec == 'o' || spec == 'O' ||
		spec == 'x' || spec == 'X')
	{
		return (1);
	}
	return (0);
}

static int	print_percent(t_printf* options, t_fms *fms)
{
	(void)options;
	(void)fms;
	return (0);
}

static int	print_specifier(t_printf *options, t_fms *fms)
{
	char	spec;

	spec = fms->specifier;
	if (spec == '%')
		return print_percent(options, fms);
	else if (is_integer_specifier(spec))
		return print_integer(options, fms);
	return (0);
}

void		set_default_fms(t_fms *fms)
{
	fms->padc = ' ';
	fms->altfmt = FALSE;
	fms->left_adjust = FALSE;
	fms->plus_sign = 0;
	fms->length_modifier = NONE;
	fms->specifier = 0;
	fms->length = 0;
	fms->precision = -1;
}

int			_printf(t_printf *options, const char *fmt)
{
	int		res;
	char	c;
	t_fms	fms;

	while ((c = *fmt++) != '\0')
	{
		if (c == '%')
		{
			set_default_fms(&fms);
			parse_fms(&fmt, &fms, options->ap);
			if ((res = print_specifier(options, &fms)))
				return (res);
		}
		else
		{
			if ((res = options->putc(options, c)))
				return (res);
		}
	}
	options->flush(options);
	return (0);
}
