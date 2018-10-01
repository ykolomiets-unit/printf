#include "dragon4.h"
#include "utils.h"

uint32_t	print_inf_nan(char *buffer, uint32_t buffer_size, uint64_t mantissa)
{
	uint32_t	max_print_len;
	uint32_t	print_len;
	char 		*str;


	max_print_len = buffer_size - 1;
	if (mantissa == 0)
		str = "inf";
	else
		str = "nan";
	print_len = (3 < max_print_len) ? 3 : max_print_len;
	ft_memcpy(buffer, str, print_len);
	buffer[print_len] = '\0';
	return (print_len);
}
