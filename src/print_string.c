#include "_printf.h"
#include "utils.h"
#include <limits.h>

static int	print_wchar_string(t_printf *options, t_fms *fms)
{
	wchar_t	*p1;
	wchar_t *p2;
	int		print_res;
	char	buf[4];
	int		len;
	int		str_len;

	if (!(p1 = va_arg(*options->ap, wchar_t *)))
		p1 = L"(null)";
	p2 = p1;
	str_len = 0;
	while (*p2 != L'\0' && str_len < fms->precision)
	{
		len = wchar_length_in_bytes(*p2);
		if (str_len + len <= fms->precision)
			str_len += len;
		p2++;
	}
	fms->length -= str_len;
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	while (*p1 != L'\0')
	{
		len = wchartobuf(*p1++, buf);
		if (len > fms->precision)
			break;
		fms->precision -= len;
		while (--len >= 0)
			if ((print_res = options->putc(options, buf[len])))
				return (print_res);
	}
	if (fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	return (0);
}

static int	print_char_string(t_printf *options, t_fms *fms)
{
	int		print_res;
	int		str_len;
	char	*p;

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

int		print_string(t_printf* options, t_fms *fms)
{

	if (fms->precision == -1)
		fms->precision = INT_MAX;
	if (fms->length_modifier == LM_LONG)
		return (print_wchar_string(options, fms));
	else
		return(print_char_string(options, fms));
}
