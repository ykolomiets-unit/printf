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
	LM_NONE,
	LM_SHORT_SHORT,
	LM_SHORT,
	LM_LONG,
	LM_LONG_LONG,
	LM_J,
	LM_Z
}						t_length_modifier;

typedef enum			e_specifier_type
{
	ST_NONE,
	ST_PERCENT,
	ST_INTEGER,
	ST_CHARACTER,
	ST_STRING
}						t_specifier_type;

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
	int					printed;
}						t_printf;

typedef struct			s_fms
{
	char				specifier;
	t_specifier_type	specifier_type;
	t_boolean			left_adjust;
	t_boolean			altfmt;
	char				plus_sign;
	char				padc;
	t_length_modifier	length_modifier;
	int					length;
	int					precision;
}						t_fms;

int						_printf(t_printf *options, const char *fmt);

int						is_flag(char c);
void					parse_flag(const char **fmt, t_fms *fms);
int						is_length_start(char c);
void					parse_length(const char **fmt, t_fms *fms, va_list *ap);
int						is_precision_start(char c);
void					parse_precision(const char **fmt, t_fms *fms, va_list *ap);
int						is_length_modifier_start(char c);
void					set_length_modifier(t_fms *fms, t_length_modifier modifier);
void					parse_length_modifier(const char **fmt, t_fms *fms);
int						is_specifier(char c);
void					parse_specifier(const char **fmt, t_fms *fms);
int						print_percent(t_printf* options, t_fms *fms);
int						print_char(t_printf* options, t_fms *fms);
int						print_integer(t_printf *options, t_fms *fms);
int						print_string(t_printf* options, t_fms *fms);

#endif
