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
	printf("% .2000e\n", 1.123102104012401241241);
	ft_printf("% .2000e\n", 1.123102104012401241241);
	return (0);
}
