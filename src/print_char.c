#include "_printf.h"

int		print_char(t_printf* options, t_fms *fms)
{
	(void)fms;
	int				print_res;
	unsigned char	c;

	fms->length--;
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	c = (unsigned char)va_arg(*options->ap, int);
	if ((print_res = options->putc(options, c)))
		return (print_res);
	if (fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	return (0);
}
