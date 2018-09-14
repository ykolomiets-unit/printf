#include "_printf.h"
#include "utils.h"

int		print_char(t_printf* options, t_fms *fms)
{
	wchar_t	wc;
	int		print_res;
	char	buf[4];
	int		i;

	if (fms->length_modifier == LM_LONG)
	{
		wc = (wchar_t)va_arg(*options->ap, wint_t);
		i = wchartobuf(wc, buf);
	}
	else
	{
		buf[0] = va_arg(*options->ap, int);
		i = 1;
	}
	fms->length -= i;
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	while (--i >= 0)
		if ((print_res = options->putc(options, buf[i])))
			return (print_res);
	if (fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	return (0);
}
