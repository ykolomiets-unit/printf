#include "_printf.h"
#include "utils.h"
#include "dragon4.h"

static int	print_pad_and_sign(t_printf *options, t_fms *fms, char sign_char)
{
	int	print_res;

	if (fms->padc == ' ' && !fms->left_adjust)
	{
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	}
	if (sign_char)
		if ((print_res = options->putc(options, sign_char)))
			return (print_res);
	if (fms->padc == '0')
	{
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, '0')))
				return (print_res);
	}
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

static void	apply_dragon4(t_printf *options, t_fms *fms, char *buf, int *is_negative)
{
	t_print_float64_arg	arg;

	arg.value = va_arg(*options->ap, double);
	*is_negative = arg.value < 0;
	if (*is_negative)
		arg.value = -arg.value;
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

static int	add_point_in_positional(char *buf)
{
	int	i;

	int len;

	len = ft_strlen(buf);
	i = -1;
	while (++i < len)
		if (buf[i] == '.')
			return (0);
	buf[len] = '.';
	buf[len + 1] = '\0';
	return (1);
}

static int add_point_in_scientific(char *buf)
{
	int	i;
	int len;

	len = ft_strlen(buf);
	i = -1;
	while (++i < len)
	{
		if (buf[i] == '.')
			return (0);
		if (buf[i] == 'e' || buf[i] == 'E')
			break;
	}
	ft_memmove(buf + i + 1, buf + i, len - i + 1);
	buf[i] = '.';
	return (1);
}

static int	insert_point(t_fms *fms, char *buf)
{
	if (fms->altfmt)
	{
		if (fms->specifier == 'f' || fms->specifier == 'F')
			return (add_point_in_positional(buf));
		else
			return (add_point_in_scientific(buf));
	}
	return (0);
}
static int	output_buf(t_printf *options, int precision, char *buf)
{
	int	print_res;
	int	i;

	i = -1;
	while (buf[++i])
	{
		if ((print_res = options->putc(options, buf[i])))
			return (print_res);
		if (buf[i] == '.')
		{
			while (buf[++i] && buf[i] != 'e' && buf[i] != 'E')
			{
				if ((print_res = options->putc(options, buf[i])))
					return (print_res);
				precision--;
			}
			while (precision-- > 0)
				if ((print_res = options->putc(options, '0')))
					return (print_res);
			if (buf[i] == '\0')
				return (0);
			--i;
		}
	}
	return (0);
}

static int 	get_length_with_precision(char *buf, int precision)
{
	int	len;
	int real_precision;

	len = -1;
	real_precision = 0;
	while (buf[++len])
	{
		if (buf[len] == '.')
		{
			len++;
			while (buf[len] && buf[len] != 'e' && buf[len] != 'E')
			{
				len++;
				real_precision++;
			}
			if (buf[len] == '\0')
				break ;
		}
	}
	return (len + precision - real_precision);
}

int			print_float(t_printf *options, t_fms *fms)
{
	int					print_res;
	int					length_with_precision;
	char				buf[1024];
	char 				sign_char;
	int 				is_negative;

	apply_dragon4(options, fms, buf, &is_negative);
	sign_char = is_negative ? '-' : fms->plus_sign;
	if (sign_char)
		fms->length--;
	length_with_precision = get_length_with_precision(buf, fms->precision);
	fms->length -= length_with_precision;
	fms->length -= insert_point(fms, buf);
	if ((print_res = print_pad_and_sign(options, fms, sign_char)))
		return (print_res);
	if ((print_res = output_buf(options, fms->precision, buf)))
		return (print_res);
	if ((print_res = print_left_adjust(options, fms)))
		return (print_res);
	return (0);
}