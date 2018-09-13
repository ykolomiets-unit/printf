#include <stdio.h>
#include <fcntl.h>
#include <inttypes.h>
#include <wchar.h>
#include "ft_printf.h"

int	main(void)
{
	printf("%#.3o", 10);
	ft_printf("%#.3o", 10);
	return (0);
}
