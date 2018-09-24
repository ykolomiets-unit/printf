#ifndef BIG_INT_H
# define BIG_INT_H

# include <stdint.h>

# define BIG_INT_MAX_BLOCK 35

typedef	int		t_boolean;

typedef	struct	s_big_int
{
	uint32_t	blocks[BIG_INT_MAX_BLOCK];
	uint32_t	length;
}				t_big_int;

void		bi_set_zero(t_big_int *big_int);
t_boolean	bi_is_zero(t_big_int *big_int);
void		bi_set_u32(t_big_int *big_int, uint32_t val);
void		bi_set_u64(t_big_int *big_int, uint64_t val);
uint32_t	bi_get_u32(t_big_int *big_int);
int			bi_compare(t_big_int *left, t_big_int *right);
void		bi_add(t_big_int *result, t_big_int *left, t_big_int *right);
void		bi_mult_2_numbers(t_big_int *result, t_big_int *left, t_big_int *right);

#endif
