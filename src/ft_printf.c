#include "ft_printf.h"

int			ft_printf(const char *fmt, ...)
{
	int			printed;
	va_list		ap;

	va_start(ap, fmt);
	printed = ft_vdprintf(1, fmt, &ap);
	va_end(ap);
	return (printed);
}
