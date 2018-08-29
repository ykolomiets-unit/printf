#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>

#define BUF_SIZE 8

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

static int	_printf(t_printf *options, register const char *fmt, va_list *ap)
{
	(void)ap;
	int		printed;
	char	c;

	printed = 0;
	while ((c = *fmt++) != '\0')
	{
		if (options->putc(options, c))
			return printed;
		printed++;
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
