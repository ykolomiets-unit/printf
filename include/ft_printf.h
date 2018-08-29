#ifndef FT_PRINTF_H
#define FT_PRINTF_H

int	ft_printf(const char *fmt, ...);
int ft_dprintf(const int fd, const char *fmt, ...);
int	ft_snprintf(char *buf, const int size, const char *fmt, ...);

#endif
