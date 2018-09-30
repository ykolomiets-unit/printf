#ifndef BIG_INT_H
# define BIG_INT_H

# include <stdint.h>

# define BIG_INT_MAX_BLOCK 35

typedef	int		t_boolean;

typedef	struct	s_big_int
{
	uint32_t	length;
	uint32_t	blocks[BIG_INT_MAX_BLOCK];
}				t_big_int;

void			bi_set_zero(t_big_int *big_int);
t_boolean		bi_is_zero(t_big_int *big_int);
void			bi_set_u32(t_big_int *big_int, uint32_t val);
void			bi_set_u64(t_big_int *big_int, uint64_t val);
uint32_t		bi_get_u32(t_big_int *big_int);
int				bi_compare(t_big_int *left, t_big_int *right);
void			bi_add(t_big_int *result, t_big_int *left, t_big_int *right);
void			bi_mult_bi_by_bi(t_big_int *result, t_big_int *left, t_big_int *right);
void			bi_mult_bi_by_uint32(t_big_int *result, t_big_int *left, uint32_t right);
void			bi_mult_bi_by_2(t_big_int *result, t_big_int *in);
void			bi_mult_bi_by_2_inplace(t_big_int *result);
void			bi_mult_bi_by_10_inplace(t_big_int *result);
void			bi_pow10(t_big_int *result, uint32_t exponent);
void			bi_mult_by_pow10(t_big_int *result, t_big_int *in, uint32_t exponent);
void			bi_pow2(t_big_int *result, uint32_t exponent);
uint32_t		bi_divide_with_remainder_maxquotient9(t_big_int	*dividend, t_big_int *divisor);
void			bi_shift_left(t_big_int *result, uint32_t shift);

#endif
