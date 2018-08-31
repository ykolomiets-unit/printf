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

TEST(ft_printf, string_plus_negative_num)
{
	ft_snprintf(buffer, BUF_SIZE, "abc = %d", -321);
	TEST_ASSERT_EQUAL_STRING("abc = -321", buffer);
}
