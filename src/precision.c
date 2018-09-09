#include "_printf.h"
#include "utils.h"

int		is_precision_start(char c)
{
	if (c == '.')
		return (1);
	return (0);
}

void	parse_precision(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	c = **fmt;
	if (c == '.')
	{
		fms->padc = ' ';
		(*fmt)++;
		c = **fmt;
		fms->precision = 0;
		if (IS_DIGIT(c))
		{
			while (IS_DIGIT(c))
			{
				fms->precision = fms->precision * 10 + CHAR_TO_DIGIT(c);
				(*fmt)++;
				c = **fmt;
			}
		}
		else if (c == '*')
		{
			fms->precision = va_arg(*ap, int);
			(*fmt)++;
		}
	}
}
