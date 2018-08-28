#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>

#define BUF_SIZE 8

typedef struct	s_printf
{
	int			fd;
	char		buffer[BUF_SIZE];	
	int			pos_in_buffer;
	int			(*putc)(struct s_printf *, char);
	int			(*flush)(struct s_printf *);
}				t_printf;

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
		for (int i = 0; i < BUF_SIZE; i++)//TODO: replace with ft_memset
			options->buffer[i] = 0;
	}
	return (0);
}

static int	flush_to_stream(t_printf *options)
{
	write(options->fd, options->buffer, BUF_SIZE);
	return (0);
}

int			ft_printf(const char *fmt, ...)
{
	int			printed;
	va_list		ap;
	t_printf	options;

	options.fd = 1;
	options.putc = print_to_stream;
	options.flush = flush_to_stream;
	options.pos_in_buffer = 0;
	va_start(ap, fmt);
	printed = _printf(&options, fmt, &ap);
	va_end(ap);
	return (printed);
}

int			ft_dprintf(int fd, const char *fmt, ...)
{
	int			printed;
	va_list		ap;
	t_printf	options;

	options.fd = fd;
	options.putc = print_to_stream;
	options.flush = flush_to_stream;
	options.pos_in_buffer = 0;
	va_start(ap, fmt);
	printed = _printf(&options, fmt, &ap);
	va_end(ap);
	return (printed);
}
