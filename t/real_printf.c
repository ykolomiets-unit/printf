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
	printf("%+#X\n", -128);
	ft_printf("%+#B\n", -128);
	return (0);
}
