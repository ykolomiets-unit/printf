/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:37:13 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:47:49 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <wchar.h>

# define IS_DIGIT(x) ((x) >= '0' && (x) <= '9')
# define BITS_IN_WCHAR ((int)sizeof(wchar_t) * 8)
# define UTF8_2_BYTES_MASK 0xC0
# define UTF8_3_BYTES_MASK 0xE0
# define UTF8_4_BYTES_MASK 0xF0
# define UTF8_AUX_BYTE_MASK 0x80
# define SIX_BITS_MASK 0x3F
# define FIVE_BITS_MASK 0x1F
# define FOUR_BITS_MASK 0xF
# define THREE_BITS_MASK 0x6

void	ft_bzero(void *p, int size);
int		ft_strlen(char *s);
int		wchartobuf(wchar_t ch, char *buf);
int		wchar_length_in_bytes(wchar_t ch);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
