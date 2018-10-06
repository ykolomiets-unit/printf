/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:40:44 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/06 13:22:59 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		ft_bzero(void *p, int size)
{
	char	*s;

	s = (char *)p;
	while (size--)
		s[size] = '\0';
}

int			ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest > src)
	{
		dest += n;
		src += n;
		while (n--)
			*((char*)--dest) = *((char*)--src);
		return (dest);
	}
	while (i < n)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return (dest);
}

void		*ft_memset(void *s, int c, size_t n)
{
	char	*temp;

	temp = (char*)s;
	while (n-- > 0)
		temp[n] = (char)c;
	return (s);
}

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n--)
		((char*)dest)[n] = ((char*)src)[n];
	return (dest);
}
