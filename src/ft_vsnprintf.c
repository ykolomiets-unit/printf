#include "ft_printf.h"
#include "_printf.h"

static int	print_to_buf(t_printf *options, char c)
{
	options->external_buffer[options->pos_in_buffer++] = c;
	if (options->pos_in_buffer == options->external_buffer_size)
		return (1);
	return (0);
}

static int	flush_to_buf(t_printf *options)
{
	(void)options;

	return (0);
}

int			ft_vsnprintf(char *buf, const int size, const char *fmt, va_list *ap)
{
	t_printf	options;

	options.ap = ap;
	options.external_buffer = buf;
	options.external_buffer_size = size;
	options.pos_in_buffer = 0;
	options.putc = print_to_buf;
	options.flush = flush_to_buf;
	return (_printf(&options, fmt));
}
