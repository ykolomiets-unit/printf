#include "_printf.h"
#include <stdio.h>

#define POINTER_BUF_SIZE (sizeof(void *) * 2)

static int	num_in_buffer(long long u, char **buf)
{
	static char	digs[] = "0123456789abcdef";
	int			length;

	length = 0;
	do
	{
		**buf = digs[u % 16];
		(*buf)--;
		u /= 16;
		length++;
	} while (u != 0);
	return (length);
}


int			print_pointer(t_printf* options, t_fms *fms)
{
	int			print_res;
	long long	pointer;
	char		buf[POINTER_BUF_SIZE];
	char		*p;
	int			size;

	pointer = (long long)va_arg(*options->ap, void *);
	p = &buf[POINTER_BUF_SIZE - 1];
	if (pointer == 0 && fms->precision == 0)
		size = 0;
	else
		size = num_in_buffer(pointer, &p);
	fms->precision -= size;
	fms->length -= (2 + size + (fms->precision > 0 ? fms->precision : 0));
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	if ((print_res = options->putc(options, '0')))
		return (print_res);
	if ((print_res = options->putc(options, 'x')))
		return (print_res);
	while (--fms->precision >= 0)
		if ((print_res = options->putc(options, '0')))
			return (print_res);
	while (++p != &buf[POINTER_BUF_SIZE])
		if ((print_res = options->putc(options, *p)))
			return (print_res);
	while (--fms->length >= 0)
		if ((print_res = options->putc(options, ' ')))
			return (print_res);
	return (0);
}
