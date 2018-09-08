#include "ft_printf.h"

int			ft_dprintf(const int fd, const char *fmt, ...)
{
	int			printed;
	va_list		ap;

	va_start(ap, fmt);
	printed = ft_vdprintf(fd, fmt, &ap);
	va_end(ap);
	return (printed);
}

