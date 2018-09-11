#include "_printf.h"
#include <limits.h>

int		print_string(t_printf* options, t_fms *fms)
{
	(void)fms;
	int		print_res;
	int		str_len;
	char	*p;

	if (fms->precision == -1)
		fms->precision = INT_MAX;
	if (!(p = va_arg(*options->ap, char *)))
		p = "(null)";
	str_len = 0;
	while (p[str_len] != '\0' && str_len < fms->precision)
		str_len++;
	fms->length -= str_len;
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	while (*p != '\0' && --fms->precision >= 0)
		if ((print_res = options->putc(options, *p++)))
			return (print_res);
	if (fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	return (0);
}
