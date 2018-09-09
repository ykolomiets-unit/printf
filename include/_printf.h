#ifndef _PRINTF_H
#define _PRINTF_H

# include <stdarg.h>

# define BUF_SIZE 1024
# define INT_BUF_SIZE sizeof(intmax_t) * 8

# define CHAR_TO_DIGIT(x) ((x) - '0')

# define TRUE 1
# define FALSE 0

typedef int				t_boolean;

typedef	enum			e_length_modifier
{
	NONE,
	SHORT_SHORT,
	SHORT,
	LONG,
	LONG_LONG,
	J,
	Z
}						t_length_modifier;

typedef struct			s_printf
{
	int					fd;
	va_list				*ap;
	char				buffer[BUF_SIZE];	
	int					pos_in_buffer;
	char				*external_buffer;
	int					external_buffer_size;
	int					(*putc)(struct s_printf *, char);
	int					(*flush)(struct s_printf *);
}						t_printf;

typedef struct			s_fms
{
	char				specifier;
	t_boolean			left_adjust;
	t_boolean			altfmt;
	char				plus_sign;
	char				padc;
	t_length_modifier	length_modifier;
	int					length;
	int					precision;
}						t_fms;

int						_printf(t_printf *options, const char *fmt);

#endif
