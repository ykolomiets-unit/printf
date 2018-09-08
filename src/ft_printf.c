#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <inttypes.h>

#define BUF_SIZE 1024
#define INT_BUF_SIZE sizeof(intmax_t) * 8

#define CHAR_TO_DIGIT(x) ((x) - '0')

#define TRUE 1
#define FALSE 0

typedef int		t_boolean;
typedef	enum	e_length_modifier
{
	SHORT_SHORT,
	SHORT,
	LONG,
	LONG_LONG,
	J,
	Z,
	NONE
}				t_length_modifier;

typedef struct	s_printf
{
	int			fd;
	va_list		ap;
	char		buffer[BUF_SIZE];	
	int			pos_in_buffer;
	char		*external_buffer;
	int			external_buffer_size;
	int			(*putc)(struct s_printf *, char);
	int			(*flush)(struct s_printf *);
}				t_printf;

typedef struct	s_fms
{
	char				specifier;
	t_boolean			left_adjust;
	t_boolean			altfmt;
	char				plus_sign;
	char				padc;
	t_length_modifier	length_modifier;
	int					length;
	int					precision;
}				t_fms;

static int	is_digit(char c)
{
	return c >= '0' && c <= '9';
}

static void	ft_bzero(void *p, int size)
{
	char	*s;

	s = (char *)p;
	while (size--)
		s[size] = '\0';
}

static int	ft_strlen(char *s)
{
	int	len;

	len	= 0;
	while (*s++)
		len++;
	return (len);
}

static int	parse_flags(const char **fmt, t_fms *fms)
{
	char	c;

	fms->padc = ' ';
	while ((c = **fmt))
	{
		if (c == '#')
			fms->altfmt = TRUE;
		else if (c == '-')
		{
			fms->left_adjust = TRUE;
			fms->padc = ' ';
		}
		else if (c == '+')
			fms->plus_sign = '+';
		else if (c == ' ')
		{
			if (!fms->plus_sign)
				fms->plus_sign = ' ';
		}
		else if (c == '0' && !fms->left_adjust)
			fms->padc = '0';
		else
			break;
		(*fmt)++;
	}
	return (0);
}

static int	parse_length(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	c = **fmt;
	fms->length = 0;
	if (is_digit(c)) {
		while (is_digit(c))
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
	return (0);
}

static int	parse_precision(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	c = **fmt;
	fms->precision = -1;
	if (c == '.')
	{
		fms->padc = ' ';
		(*fmt)++;
		c = **fmt;
		fms->precision = 0;
		if (is_digit(c))
		{
			while (is_digit(c))
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
	return (0);
}

static int	parse_length_modifier(const char **fmt, t_fms *fms)
{
	if (**fmt == 'h')
	{
		(*fmt)++;
		if (**fmt == 'h')
		{
			fms->length_modifier = SHORT_SHORT;
			(*fmt)++;
		}
		else
			fms->length_modifier = SHORT;	
	}
	else if (**fmt == 'l')
	{
		(*fmt)++;
		if (**fmt == 'l')
		{
			fms->length_modifier = LONG_LONG;
			(*fmt)++;
		}
		else
			fms->length_modifier = LONG;	
	}
	else if (**fmt == 'z')
	{
		(*fmt)++;
		fms->length_modifier = Z;
	}
	else if (**fmt == 'j')
	{
		(*fmt)++;
		fms->length_modifier = J;
	}
	else
		fms->length_modifier = NONE;
	return (0);
}

static int parse_specifier(const char **fmt, t_fms *fms)
{
	char	c;

	c = **fmt;
	if (c == 'U' || c == 'D' || c == 'O')
		fms->length_modifier = LONG;
	fms->specifier = c;
	(*fmt)++;
	return (0);
}

static int	parse_fms(const char **fmt, t_fms *fms, va_list *ap)
{
	parse_flags(fmt, fms);
	parse_length(fmt, fms, ap);
	parse_precision(fmt, fms, ap);
	parse_length_modifier(fmt, fms);
	parse_specifier(fmt, fms);
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

static int	print_spacepad_sign_prefix(t_printf *options, t_fms *fms, char sign_char, char *prefix, int *printed)
{
	if (fms->padc == ' ' && !fms->left_adjust)
	{
		while (--fms->length >= 0)
		{
			options->putc(options, ' ');
			(*printed)++;
		}
	}
	if (sign_char)
	{
		options->putc(options, sign_char);
		(*printed)++;
	}
	if (prefix)
	{
		while (*prefix)
		{
			options->putc(options, *prefix++);
			(*printed)++;
		}
	}
	return (0);
}

static int	print_zeropad(t_printf *options, t_fms *fms, int *printed)
{
	if (fms->padc == '0')
	{
		while (--fms->length >= 0)
		{
			options->putc(options, '0');
			(*printed)++;
		}
	}
	else
	{
		while (--fms->precision >= 0)
		{
			options->putc(options, '0');
			(*printed)++;
		}
	}
	return (0);
}

static int	print_buf_adjust(t_printf *options, t_fms *fms, char *buf_start, char *buf_end, int *printed)
{
	while (++buf_start != buf_end)
	{
		options->putc(options, *buf_start);
		(*printed)++;
	}
	if (fms->left_adjust)
	{
		while (--fms->length >= 0)
		{
			options->putc(options, ' ');
			(*printed)++;
		}
	}
	return (0);
}

static int	print_num(uintmax_t u, t_printf *options,
					  t_fms *fms, int base, int capitals,
					  char sign_char, int *printed)
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
	print_spacepad_sign_prefix(options, fms, sign_char, prefix, printed);
	print_zeropad(options, fms, printed);
	print_buf_adjust(options, fms, p, &buffer[INT_BUF_SIZE], printed);
	return (0);
}


static int	print_signed_integer(t_printf *options, t_fms *fms,
								int	base, int capitals, int *printed)
{
	intmax_t	n;
	uintmax_t	u;
	char		sign_char;
	
	if (fms->length_modifier == NONE)
		n = va_arg(options->ap, int);
	else if (fms->length_modifier == LONG)
		n = va_arg(options->ap, long);
	else if (fms->length_modifier == LONG_LONG)
		n = va_arg(options->ap, long long);
	else if (fms->length_modifier == SHORT)
		n = (short) va_arg(options->ap, int);
	else if (fms->length_modifier == SHORT_SHORT)
		n = (signed char) va_arg(options->ap, int);
	else if (fms->length_modifier == J)
		n = va_arg(options->ap, intmax_t);
	else /*length_modifier == Z*/
		n = va_arg(options->ap, ssize_t);
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
	return print_num(u, options, fms, base, capitals, sign_char, printed);
}

static int	print_unsigned_integer(t_printf *options, t_fms *fms,
								  int base, int capitals, int *printed)
{
	uintmax_t	u;

	if (fms->length_modifier == NONE)
		u = va_arg(options->ap, unsigned);
	else if (fms->length_modifier == LONG_LONG)
		u = va_arg(options->ap, unsigned long long);
	else if (fms->length_modifier == LONG)
		u = va_arg(options->ap, unsigned long);
	else if (fms->length_modifier == SHORT)
		u = (unsigned short) va_arg(options->ap, int);
	else if (fms->length_modifier == SHORT_SHORT)
		u = (unsigned char) va_arg(options->ap, int);
	else if (fms->length_modifier == J)
		u = va_arg(options->ap, uintmax_t);
	else /* if (fms->length_modifier == J) */
		u = va_arg(options->ap, size_t);
	return print_num(u, options, fms, base, capitals, 0, printed);
}

static int	print_integer(t_printf *options, t_fms *fms, int *printed)
{
	int			base;
	int			capitals;
	t_boolean	is_signed;
	int			res;

	get_base_register_sign(fms->specifier, &base, &capitals, &is_signed);
	if (is_signed)
		res = print_signed_integer(options, fms, base, capitals, printed);
	else
		res = print_unsigned_integer(options, fms, base, capitals, printed);
	return (res);
}

static int is_integer_specifier(char spec)
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

static int print_specifier(t_printf *options, t_fms *fms, int *printed)
{
	char	spec;

	spec = fms->specifier;
	if (spec == '%')
	{
		if (options->putc(options, '%'))
			(*printed)++;
	}
	else if (is_integer_specifier(spec))
	{
		print_integer(options, fms, printed);
	}
	return (0);
}

static int	_printf(t_printf *options, const char *fmt)
{
	int		printed;
	char	c;
	t_fms	fms;

	printed = 0;
	ft_bzero(&fms, sizeof(fms));
	while ((c = *fmt++) != '\0')
	{
		if (c == '%')
		{
			parse_fms(&fmt, &fms, &options->ap);
			if (print_specifier(options, &fms, &printed))
				return printed;
		}
		else
		{
			if (options->putc(options, c))
				return printed;
			printed++;
		}
	}
	options->flush(options);
	return (printed);
}

static int	print_to_stream(t_printf *options, char c)
{
	options->buffer[options->pos_in_buffer++] = c;
	if (options->pos_in_buffer == BUF_SIZE)
	{
		write(options->fd, options->buffer, BUF_SIZE);
		options->pos_in_buffer = 0;
		ft_bzero(options->buffer, BUF_SIZE);
	}
	return (0);
}

static int	flush_to_stream(t_printf *options)
{
	int	wrote;

	wrote = write(options->fd, options->buffer, ft_strlen(options->buffer));
	if (wrote > 0)
		return (wrote);
	return (0);
}

static int	print_to_buf(t_printf *options, char c)
{
	options->external_buffer[options->pos_in_buffer++] = c;
	if (options->pos_in_buffer == options->external_buffer_size)
		return (1);
	return (0);
}

static int flush_to_buf(t_printf *options)
{
	(void)options;

	return (0);
}

int			ft_printf(const char *fmt, ...)
{
	int			printed;
	t_printf	options;

	options.fd = 1;
	options.pos_in_buffer = 0;
	ft_bzero(options.buffer, BUF_SIZE);
	options.putc = print_to_stream;
	options.flush = flush_to_stream;
	va_start(options.ap, fmt);
	printed = _printf(&options, fmt);
	va_end(options.ap);
	return (printed);
}

int			ft_dprintf(const int fd, const char *fmt, ...)
{
	int			printed;
	t_printf	options;

	options.fd = fd;
	options.pos_in_buffer = 0;
	ft_bzero(options.buffer, BUF_SIZE);
	options.putc = print_to_stream;
	options.flush = flush_to_stream;
	va_start(options.ap, fmt);
	printed = _printf(&options, fmt);
	va_end(options.ap);
	return (printed);
}

int			ft_snprintf(char *buf, const int size, const char *fmt, ...)
{
	int			printed;
	t_printf	options;

	options.external_buffer = buf;
	options.external_buffer_size = size;
	options.pos_in_buffer = 0;
	options.putc = print_to_buf;
	options.flush = flush_to_buf;
	va_start(options.ap, fmt);
	printed = _printf(&options, fmt);
	va_end(options.ap);
	return (printed);
}
