#ifndef DRAGON4_H
# define DRAGON4_H

# include <stdint.h>
# include <stddef.h>

typedef	int		t_boolean;

typedef char        t_c8;
 
typedef uint8_t     t_u8;
typedef uint16_t    t_u16;
typedef uint32_t    t_u32;
typedef uint64_t    t_u64;
  
// Signed integer types
typedef int8_t      t_s8;
typedef int16_t     t_s16;
typedef int32_t     t_s32;
typedef int64_t     t_s64;
   
// Floating point types
typedef float       t_f32;
typedef double      t_f64;
  
typedef size_t      t_size;
typedef ptrdiff_t   t_ptr_diff;

typedef enum		e_cutoff_mode
{
	CUTOFF_MODE_UNIQUE,
	CUTOFF_MODE_TOTAL_LENGTH,
	CUTOFF_MODE_FRACTIONAL_LENGTH
}					t_cutoff_mode;

typedef struct		s_dragon4_arg
{
	t_u64			mantissa;
	t_s32			exponent;
	t_u32			mantissa_high_bit_idx;
	t_boolean		has_unequal_margins;
	t_cutoff_mode	cutoff_mode;
	t_u32			cutoff_number;
	t_c8			*out_buffer;
	t_u32			buffer_size;
	t_s32			*out_exponent;
}					t_dragon4_arg;

t_u32				dragon4(t_dragon4_arg arg);
t_u32				log_base_2(t_u32 val);

#endif
