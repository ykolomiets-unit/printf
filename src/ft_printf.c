#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#define BUF_SIZE 8
#define INT_BUF_SIZE sizeof(long long int) * 8

#define CHAR_TO_DIGIT(x) ((x) - '0')

#define TRUE 1
#define FALSE 0

typedef int		boolean;

typedef struct	s_printf
{
	int			fd;
	char		buffer[BUF_SIZE];	
	int			pos_in_buffer;
	char		*external_buffer;
	int			external_buffer_size;
	int			(*putc)(struct s_printf *, char);
	int			(*flush)(struct s_printf *);
}				t_printf;

typedef struct	s_fms
{
	char		specifier;
	boolean		left_adjust;
	boolean		altfmt;
	char		plus_sign;
	char		padc;
	boolean		long_long;
	boolean		long_;
	int			length;
	int			precision;
}				t_fms;

static int	is_digit(char c)
{
	return c >= '0' && c <= '9';
}

static void ft_bzero(void *p, int size)
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
	while (TRUE)
	{
		c = **fmt;
		if (c == '#')
			fms->altfmt = TRUE;
		else if (c == '-')
			fms->left_adjust = TRUE;
		else if (c == '+')
			fms->plus_sign = '+';
		else if (c == ' ')
		{
			if (!fms->plus_sign)
				fms->plus_sign = ' ';
		}
		else if (c == '0')
			fms->padc = '0';
		else
			break;
		(*fmt)++;
	}
	return (1);
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
	(void)ap;
	char	c;

	c = **fmt;
	fms->precision = -1;
	if (c == '.')
	{
		fms->padc = ' ';
		(*fmt)++;
		c = **fmt;
		if (is_digit(c))
		{
			fms->precision = 0;
			while (is_digit(c))
			{
				fms->precision = fms->precision * 10 + CHAR_TO_DIGIT(c);
				(*fmt)++;
				c = **fmt;
			}
		}
	}
	return (0);
}

static int parse_fms(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	parse_flags(fmt, fms);
	parse_length(fmt, fms, ap);
	parse_precision(fmt, fms, ap);
	c = **fmt;
	fms->specifier = c;
	(*fmt)++;
	return (0);
}

static void get_base_register_sign(char spec, int *base,
									int *capitals, boolean *is_signed) 
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

static int	num_in_buffer(unsigned long long u, int base, int capitals, char **buf)
{
	static char	digs[] = "0123456789abcdef0123456789ABCEDF";
	int	length;

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

static char	*get_prefix(unsigned long long u, t_fms *fms, int base, int capitals)
{
	if (u == 0 || !fms->altfmt)
		return 0;
	if (base == 8)
		return "0";
	else if (base == 16)
		return capitals ? "0X" : "0x";
	return 0;
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

static int	print_num(unsigned long long u, t_printf *options,
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
								int	base, int capitals,
								va_list *ap, int *printed)
{
	long long			n;
	unsigned long long	u;
	char				sign_char;
	
	if (fms->long_long)
		n = va_arg(*ap, long long);
	else if (fms->long_)
		n = va_arg(*ap, long);
	else
		n = va_arg(*ap, int);
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
								  int base, int capitals,
								  va_list *ap, int *printed)
{
	unsigned long long	u;

	if (fms->long_long)
		u = va_arg(*ap, unsigned long long);
	else if (fms->long_)
		u = va_arg(*ap, unsigned long);
	else
		u = va_arg(*ap, unsigned);
	return print_num(u, options, fms, base, capitals, 0, printed);
}

static int print_integer(t_printf *options, t_fms *fms, va_list *ap, int *printed)
{
	int		base;
	int		capitals;
	boolean	is_signed;
	int		res;

	get_base_register_sign(fms->specifier, &base, &capitals, &is_signed);
	if (is_signed)
		res = print_signed_integer(options, fms, base, capitals, ap, printed);
	else
		res = print_unsigned_integer(options, fms, base, capitals, ap, printed);
	return (res);
}

static int print_specifier(t_printf *options, t_fms *fms, va_list *ap, int *printed)
{
	char	spec;

	spec = fms->specifier;
	if (spec == '%')
	{
		if (options->putc(options, '%'))
			(*printed)++;
	}
	else if (spec == 'd' || spec == 'i' ||
		spec == 'o' || spec == 'O' ||
		spec == 'x' || spec == 'X')
	{
		print_integer(options, fms, ap, printed);
	}
	return (0);
}

static int	_printf(t_printf *options, const char *fmt, va_list *ap)
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
			parse_fms(&fmt, &fms, ap);
			if (print_specifier(options, &fms, ap, &printed))
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
	va_list		ap;
	t_printf	options;

	options.fd = 1;
	options.pos_in_buffer = 0;
	ft_bzero(options.buffer, BUF_SIZE);
	options.putc = print_to_stream;
	options.flush = flush_to_stream;
	va_start(ap, fmt);
	printed = _printf(&options, fmt, &ap);
	va_end(ap);
	return (printed);
}

int			ft_dprintf(const int fd, const char *fmt, ...)
{
	int			printed;
	va_list		ap;
	t_printf	options;

	options.fd = fd;
	options.pos_in_buffer = 0;
	ft_bzero(options.buffer, BUF_SIZE);
	options.putc = print_to_stream;
	options.flush = flush_to_stream;
	va_start(ap, fmt);
	printed = _printf(&options, fmt, &ap);
	va_end(ap);
	return (printed);
}

int			ft_snprintf(char *buf, const int size, const char *fmt, ...)
{
	int			printed;
	va_list		ap;
	t_printf	options;

	options.external_buffer = buf;
	options.external_buffer_size = size;
	options.pos_in_buffer = 0;
	options.putc = print_to_buf;
	options.flush = flush_to_buf;
	va_start(ap, fmt);
	printed = _printf(&options, fmt, &ap);
	va_end(ap);
	return (printed);
}
