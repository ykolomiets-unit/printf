#include "_printf.h"
#include "utils.h"
#include "dragon4.h"

static int	print_pad(t_printf *options, t_fms *fms)
{
	int		print_res;

	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	return (0);
}

static int	print_left_adjust(t_printf *options, t_fms *fms)
{
	int	print_res;

	if (fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	return (0);
}

static void	apply_dragon4(t_printf *options, t_fms *fms, char *buf)
{
	t_print_float64_arg	arg;

	arg.value = va_arg(*options->ap, double);
	arg.precision = fms->precision == -1 ? 6 : fms->precision;
	arg.buffer_size = 1024;
	arg.out_buffer = buf;
	if (fms->specifier == 'f' || fms->specifier == 'F')
		arg.format = PRINT_FLOAT_FORMAT_POSITIONAL;
	else
		arg.format = PRINT_FLOAT_FORMAT_SCIENTIFIC;
	if (fms->specifier == 'G' || fms->specifier == 'F')
		arg.is_upper_case = 1;
	else
		arg.is_upper_case = 0;
	print_float64(arg);	
}

int			output_buf(t_printf *options, char *buf)
{
	int	print_res;
	int	i;

	i = -1;
	while (buf[++i])
		if ((print_res = options->putc(options, buf[i])))
			return (print_res);
	return (0);
}

int			print_float(t_printf *options, t_fms *fms)
{
	int					print_res;
	char				buf[1024];
	
	apply_dragon4(options, fms, buf);
	if (buf[0] != '-' && fms->plus_sign)
		fms->length--;
	fms->length -= ft_strlen(buf);
	if ((print_res = print_pad(options, fms)))
		return (print_res);
	if (buf[0] != '-' && fms->plus_sign)
		if ((print_res = options->putc(options, fms->plus_sign)))
			return (print_res);
	if ((print_res = output_buf(options, buf)))
		return (print_res);
	if ((print_res = print_left_adjust(options, fms)))
		return (print_res);
	return (0);
}
