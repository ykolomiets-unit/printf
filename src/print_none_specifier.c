#include "printf_core.h"

int			print_none_specifier(t_printf* options, t_fms *fms)
{
	int			print_res;

	fms->length--;
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	if (fms->specifier)
		if ((print_res = options->putc(options, fms->specifier)))
			return (print_res);
	if (fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	return (0);
}
