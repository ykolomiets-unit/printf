#include "ft_printf.h"

int			ft_snprintf(char *buf, const int size, const char *fmt, ...)
{
	int		printed;
	va_list	ap;

	va_start(ap, fmt);
	printed = ft_vsnprintf(buf, size, fmt, &ap);
	va_end(ap);
	return (printed);
}
