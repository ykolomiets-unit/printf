#include "utils.h"

void	ft_bzero(void *p, int size)
{
	char	*s;

	s = (char *)p;
	while (size--)
		s[size] = '\0';
}

int		ft_strlen(char *s)
{
	int	len;

	len	= 0;
	while (*s++)
		len++;
	return (len);
}
