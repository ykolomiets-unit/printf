#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "ft_printf.h"

TEST_GROUP(ft_printf);

int	fd_test_file;

TEST_SETUP(ft_printf)
{
	fd_test_file = creat("test", 0777); 
}

TEST_TEAR_DOWN(ft_printf)
{
}

TEST(ft_printf, basic_test)
{
	TEST_ASSERT_EQUAL_INT(3, ft_dprintf(fd_test_file, "abc"));
	lseek(fd_test_file, 0, SEEK_SET);
}

TEST(ft_printf, output_string_gt_buf_size)
{
	TEST_ASSERT_EQUAL_INT(26, ft_dprintf(fd_test_file, "abcdefghijklmnopqrstuvwxyz"));
	lseek(fd_test_file, 0, SEEK_SET);
}
