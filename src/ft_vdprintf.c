#include "ft_printf.h"
#include "_printf.h"
#include "utils.h"
#include <unistd.h>

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

int			ft_vdprintf(const int fd, const char *fmt, va_list *ap)
{
	t_printf	options;

	options.fd = fd;
	options.pos_in_buffer = 0;
	ft_bzero(options.buffer, BUF_SIZE);
	options.putc = print_to_stream;
	options.flush = flush_to_stream;
	options.ap = ap;
	return _printf(&options, fmt);
}
