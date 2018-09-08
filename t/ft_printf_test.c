#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "ft_printf.h"

TEST_GROUP(ft_printf);

#define BUF_SIZE 1024

static int	fd;
static char	buffer[BUF_SIZE];

TEST_SETUP(ft_printf)
{
	bzero(buffer, BUF_SIZE);
	fd = open("test_file", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
}

TEST_TEAR_DOWN(ft_printf)
{
	close(fd);
}

void	read_file(void)
{
	int	nread;
	int totalRead;

	lseek(fd, 0, SEEK_SET);
	nread = 0;
	totalRead = 0;
	while((nread = read(fd, buffer + totalRead, BUF_SIZE - totalRead)) > 0)
		;
}

TEST(ft_printf, basic_test)
{
	ft_dprintf(fd, "1234");
	read_file(); 
	TEST_ASSERT_EQUAL_STRING("1234", buffer);
}

TEST(ft_printf, output_string_gt_buf_size)
{
	ft_dprintf(fd, "1234567890");
	read_file(); 
	TEST_ASSERT_EQUAL_STRING("1234567890", buffer);
}

TEST(ft_printf, snptinf)
{
	ft_snprintf(buffer, BUF_SIZE, "ABCDEFGH");
	TEST_ASSERT_EQUAL_STRING("ABCDEFGH", buffer);
}

TEST(ft_printf, only_d)
{
	ft_snprintf(buffer, BUF_SIZE, "%d", 123);
	TEST_ASSERT_EQUAL_STRING("123", buffer);
}

TEST(ft_printf, string_plus_d)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %d", 321);
	TEST_ASSERT_EQUAL_STRING("abc = 321", buffer);
}

TEST(ft_printf, string_plus_d_plus_sign_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %+d", 321);
	TEST_ASSERT_EQUAL_STRING("abc = +321", buffer);
}

TEST(ft_printf, string_plus_d_space_sign_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = % d", 321);
	TEST_ASSERT_EQUAL_STRING("abc =  321", buffer);
}

TEST(ft_printf, string_plus_d_space_and_plus_sign_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = % +d", 321);
	TEST_ASSERT_EQUAL_STRING("abc = +321", buffer);
}

TEST(ft_printf, string_plus_negative_num)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %d", -321);
	TEST_ASSERT_EQUAL_STRING("abc = -321", buffer);
}

TEST(ft_printf, string_plus_d_altfmt_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %#d", 123);
	TEST_ASSERT_EQUAL_STRING("abc = 123", buffer);
}

TEST(ft_printf, string_plus_x_altfmt_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %#x", 123);
	TEST_ASSERT_EQUAL_STRING("abc = 0x7b", buffer);
}

TEST(ft_printf, string_plus_X)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %X", 123);
	TEST_ASSERT_EQUAL_STRING("abc = 7B", buffer);
}

TEST(ft_printf, string_plus_X_altfmt_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %#X", 123);
	TEST_ASSERT_EQUAL_STRING("abc = 0X7B", buffer);
}

TEST(ft_printf, string_plus_o_altfmt_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %#o", 123);
	TEST_ASSERT_EQUAL_STRING("abc = 0173", buffer);
}

TEST(ft_printf, d_with_length)
{
	ft_snprintf(buffer, BUF_SIZE, "%5d", 10);
	TEST_ASSERT_EQUAL_STRING("   10", buffer);
}

TEST(ft_printf, d_with_asterix_length)
{
	ft_snprintf(buffer, BUF_SIZE, "%*d", 5, 10);
	TEST_ASSERT_EQUAL_STRING("   10", buffer);
}

TEST(ft_printf, d_with_length_plus_sign)
{
	ft_snprintf(buffer, BUF_SIZE, "%+5d", 10);
	TEST_ASSERT_EQUAL_STRING("  +10", buffer);
}

TEST(ft_printf, d_with_length_lt_real_length)
{
	ft_snprintf(buffer, BUF_SIZE, "%5d", 1000000);
	TEST_ASSERT_EQUAL_STRING("1000000", buffer);
}

TEST(ft_printf, d_with_length_and_zero_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "%05d", 1);
	TEST_ASSERT_EQUAL_STRING("00001", buffer);
}

TEST(ft_printf, d_with_length_lt_real_length_and_zero_flag)
{
	ft_snprintf(buffer, BUF_SIZE, "%05d", 1000000);
	TEST_ASSERT_EQUAL_STRING("1000000", buffer);
}

TEST(ft_printf, d_with_left_adjust)
{
	ft_snprintf(buffer, BUF_SIZE, "%-5d", 1);
	TEST_ASSERT_EQUAL_STRING("1    ", buffer);
}

TEST(ft_printf, d_with_negative_asterix_length)
{
	ft_snprintf(buffer, BUF_SIZE, "%*d", -5, 10);
	TEST_ASSERT_EQUAL_STRING("10   ", buffer);
}

TEST(ft_printf, d_with_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.4d", 10);
	TEST_ASSERT_EQUAL_STRING("0010", buffer);
}

TEST(ft_printf, d_with_precision_and_additional_flags)
{
	ft_snprintf(buffer, BUF_SIZE, "%#.4x", 8);
	TEST_ASSERT_EQUAL_STRING("0x0008", buffer);
}

TEST(ft_printf, d_with_length_and_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%05.3d", 1);
	TEST_ASSERT_EQUAL_STRING("  001", buffer);
}

TEST(ft_printf, d_with_0_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.0d", 8);
	TEST_ASSERT_EQUAL_STRING("8", buffer);
}

TEST(ft_printf, d_equals_0_with_0_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.0d", 0);
	TEST_ASSERT_EQUAL_STRING("", buffer);
}

TEST(ft_printf, empty_precision_with_zero_value)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %#.x", 0);
	TEST_ASSERT_EQUAL_STRING("abc = ", buffer);
}

TEST(ft_printf, o_with_0_presicion_and_altfmt)
{
	ft_snprintf(buffer, BUF_SIZE, "%#.o %#.0o", 0, 0);
	TEST_ASSERT_EQUAL_STRING("0 0", buffer);
}

TEST(ft_printf, d_with_asterix_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.*d", 5, 10);
	TEST_ASSERT_EQUAL_STRING("00010", buffer);
}

TEST(ft_printf, d_with_negative_asterix_precision)
{
	ft_snprintf(buffer, BUF_SIZE, "%.*d", -5, 10);
	TEST_ASSERT_EQUAL_STRING("10", buffer);
}

TEST(ft_printf, string_plus_u)
{
	ft_snprintf(buffer, BUF_SIZE, "%u", 10);
	TEST_ASSERT_EQUAL_STRING("10", buffer);
}


TEST(ft_printf, string_plus_u_and_negative_value)
{
	ft_snprintf(buffer, BUF_SIZE, "%u", -1);
	TEST_ASSERT_EQUAL_STRING("4294967295", buffer);
}

TEST(ft_printf, hd_with_value_gt_maxshort)
{
	int d = 100000;
	ft_snprintf(buffer, BUF_SIZE, "%hd", d);
	TEST_ASSERT_EQUAL_STRING("-31072", buffer);
}

TEST(ft_printf, hhd_with_value_gt_maxshort)
{
	int d = 100000;
	ft_snprintf(buffer, BUF_SIZE, "%hhd", d);
	TEST_ASSERT_EQUAL_STRING("-96", buffer);
}

TEST(ft_printf, minus_and_zero_flags)
{
	ft_snprintf(buffer, BUF_SIZE, "%#-08x", 42);
	TEST_ASSERT_EQUAL_STRING("0x2a    ", buffer);
}

TEST(ft_printf, U_with_maximum_unsigned_long)
{
	ft_snprintf(buffer, BUF_SIZE, "%U", 4294967296);
	TEST_ASSERT_EQUAL_STRING("4294967296", buffer);
}

TEST(ft_printf, hU_with_maximum_unsigned_long)
{
	ft_snprintf(buffer, BUF_SIZE, "%hU", 4294967296);
	TEST_ASSERT_EQUAL_STRING("4294967296", buffer);
}

TEST(ft_printf, jx_with_4294967296)
{
	ft_snprintf(buffer, BUF_SIZE, "%jx", 4294967296);
	TEST_ASSERT_EQUAL_STRING("100000000", buffer);
}

TEST(ft_printf, jx_with_minus_4294967296)
{
	ft_snprintf(buffer, BUF_SIZE, "%jx", -4294967296);
	TEST_ASSERT_EQUAL_STRING("ffffffff00000000", buffer);
}

TEST(ft_printf, jx_with_minus_4294967297)
{
	ft_snprintf(buffer, BUF_SIZE, "%jx", -4294967297);
	TEST_ASSERT_EQUAL_STRING("fffffffeffffffff", buffer);
}

TEST(ft_printf, jd_with_9223372036854775807)
{
	ft_snprintf(buffer, BUF_SIZE, "%jd", 9223372036854775807);
	TEST_ASSERT_EQUAL_STRING("9223372036854775807", buffer);
}

TEST(ft_printf, jd_with_minus_9223372036854775808)
{
	ft_snprintf(buffer, BUF_SIZE, "%jd", -9223372036854775808);
	TEST_ASSERT_EQUAL_STRING("-9223372036854775808", buffer);
}
