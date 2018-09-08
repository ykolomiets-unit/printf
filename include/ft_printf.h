#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *fmt, ...);
int	ft_dprintf(const int fd, const char *fmt, ...);
int	ft_snprintf(char *buf, const int size, const char *fmt, ...);

int	ft_vdprintf(const int fd, const char *fmt, va_list *ap);
int	ft_vsnprintf(char *buf, const int size, const char *fmt, va_list *ap);

#endif
