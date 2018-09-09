#include "_printf.h"

int		is_specifier(char c)
{
	static char	specifiers[] = "%douxiDOUX";
	char		*p;

	p = specifiers;
	while (*p)
	{
		if (c == *p)
			return (1);
		p++;
	}
	return (0);
}

void	parse_specifier(const char **fmt, t_fms *fms)
{
	char	c;

	c = **fmt;
	if (c == '%')
		fms->specifier_type = ST_PERCENT;
	else if (c == 'U' || c == 'D' || c == 'O')
	{
		set_length_modifier(fms, LM_LONG);
		fms->specifier_type = ST_INTEGER;
	}
	else if (c == 'd' || c == 'i' || c == 'u' ||
			c == 'o' || c == 'x' || c == 'X')
		fms->specifier_type	= ST_INTEGER;
	else
	{
		fms->specifier_type = ST_NONE;
		return ;
	}
	fms->specifier = c;
	(*fmt)++;
}
