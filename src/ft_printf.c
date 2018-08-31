#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#define BUF_SIZE 8
#define INT_BUF_SIZE sizeof(long long int) * 8

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
	boolean		long_long;
}				t_fms;

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

static int parse_fms(const char **fmt, t_fms *fms, va_list *ap)
{
	(void)ap;
	char	c;

	c = **fmt;
	(*fmt)++;
	fms->specifier = c;
	fms->long_long = FALSE;
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

static int	print_num(unsigned long long u, t_printf *options,
					  t_fms *fms, int base, int capitals,
					  char sign_char, int *printed)
{
	(void)fms;
	static char	digs[] = "0123456789abcdef0123456789ABCEDF";
	char		buffer[INT_BUF_SIZE];
	char		*p;
	
	p = &buffer[INT_BUF_SIZE - 1];
	do
	{
		*p-- = digs[(u % base) + capitals];
		u /= base;
	} while (u != 0);
	if (sign_char)
	{
		options->putc(options, sign_char);
		(*printed)++;
	}
	while (++p != &buffer[INT_BUF_SIZE])
	{
		options->putc(options, *p);
		(*printed)++;
	}
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
	else
		n = va_arg(*ap, long);
	if (n >= 0)
	{
		u = n;
		sign_char = '+';
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
	else
		u = va_arg(*ap, unsigned long);
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
