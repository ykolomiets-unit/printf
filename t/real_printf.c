#include <stdio.h>
#include <fcntl.h>
#include <inttypes.h>
#include <wchar.h>
#include <locale.h>
#include "ft_printf.h"
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

int	main(void)
{
	printf("%.20f\n", 9823742742.1231231231);
	ft_printf("%.20f\n", 9823742742.1231231231);
	return (0);
}
