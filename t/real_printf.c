#include <stdio.h>
#include <fcntl.h>
#include <inttypes.h>
#include <wchar.h>
#include <locale.h>
#include "ft_printf.h"
#include <unistd.h>
#include <string.h>

#define BITS_IN_ULONG ((int)sizeof(unsigned long) * 8)
#define UTF8_2_BYTES_MASK 0xC0
#define UTF8_3_BYTES_MASK 0xE0
#define UTF8_4_BYTES_MASK 0xF0
#define UTF8_AUX_BYTE_MASK 0x80
#define SIX_BITS_MASK 0x3F
#define FIVE_BITS_MASK 0x1F
#define FOUR_BITS_MASK 0xF
#define THREE_BITS_MASK 0x6

int	main(void)
{
	setlocale(LC_ALL, "en_US.UTF-8");
	printf("{%05p}", 0);
	ft_printf("{%05p}", 0);
	return (0);
}
