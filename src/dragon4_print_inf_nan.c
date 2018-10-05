#include "dragon4.h"
#include "utils.h"

uint32_t	print_inf_nan(char *buffer, uint32_t buffer_size, uint64_t mantissa, t_boolean is_upper_case)
{
	uint32_t	max_print_len;
	uint32_t	print_len;
	char 		*str;

	max_print_len = buffer_size - 1;
	if (mantissa == 0)
		str = is_upper_case ? "INF" : "inf";
	else
		str = is_upper_case ? "NAN" : "nan";
	print_len = (3 < max_print_len) ? 3 : max_print_len;
	ft_memcpy(buffer, str, print_len);
	buffer[print_len] = '\0';
	return (print_len);
}
