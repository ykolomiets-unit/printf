#ifndef DRAGON4_H
# define DRAGON4_H

# include <stdint.h>
# include <stddef.h>

typedef	int		t_boolean;

typedef enum		e_cutoff_mode
{
	CUTOFF_MODE_UNIQUE,
	CUTOFF_MODE_TOTAL_LENGTH,
	CUTOFF_MODE_FRACTIONAL_LENGTH
}					t_cutoff_mode;

typedef struct		s_dragon4_arg
{
	uint64_t		mantissa;
	int32_t			exponent;
	uint32_t		mantissa_high_bit_idx;
	t_boolean		has_unequal_margins;
	t_cutoff_mode	cutoff_mode;
	uint32_t		cutoff_number;
	char			*out_buffer;
	uint32_t		buffer_size;
	int32_t			*out_exponent;
}					t_dragon4_arg;

uint32_t			dragon4(t_dragon4_arg arg);
uint32_t			log_base_2(uint32_t val);

#endif
