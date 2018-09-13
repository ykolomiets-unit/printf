NAME :=			libftprintf.a

SRC_DIR :=				./src
LIB_DIR :=				./lib
OBJ_DIR :=				./obj


INC_DIR :=				./include

HEADERS :=				ft_printf.h					\
						_printf.h					\
						utils.h						

HEADERS_DEP :=			$(addprefix $(INC_DIR)/, $(HEADERS))


SRCS :=					ft_printf.c					\
						ft_dprintf.c				\
						ft_snprintf.c				\
						ft_vdprintf.c				\
						ft_vsnprintf.c				\
						utils.c						\
						_printf.c					\
						flags.c						\
						length.c					\
						precision.c					\
						length_modifier.c			\
						specifier.c					\
						print_integer.c				\
						print_percent.c				\
						print_char.c				\
						print_string.c				\
						print_pointer.c				\
						print_none_specifier.c		\


OBJS :=					$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC_FLAGS :=			$(addprefix -I, $(INC_DIR))

TEST_DIR :=				./t
TEST_EXEC :=			$(TEST_DIR)/printf_test	
TEST_OBJ_DIR :=			$(TEST_DIR)/obj

TEST_PRINTF_EXEC :=		$(TEST_DIR)/real_printf

UNITY_DIR :=			$(LIB_DIR)/Unity
UNITY_INC :=			$(UNITY_DIR)/src	
UNITY_FIXTURE_INC :=	$(UNITY_DIR)/extras/fixture/src
#UNITY_FLAGS :=			-DUNITY_INCLUDE_CONFIG_H

UNITY_SRCS :=			unity.c							\
						unity_fixture.c

MOCKS_DIR :=			./mocks
MOCKS_INC :=			$(MOCKS_DIR)
#MOCKS_SRCS :=			runtime_error_stub.c			\

TEST_SRCS :=			$(UNITY_SRCS)					\
						all_tests.c						\
						ft_dprintf_test.c				\
						ft_dprintf_test_runner.c		\
						ft_snprintf_test.c				\
						ft_snprintf_test_runner.c		\
						print_integer_test.c			\
						print_integer_test_runner.c		\
						print_percent_test.c			\
						print_percent_test_runner.c		\
						print_char_test.c				\
						print_char_test_runner.c		\
						print_string_test.c				\
						print_string_test_runner.c		\
						print_pointer_test.c				\
						print_pointer_test_runner.c		\


TEST_REAL_PRINTF :=		real_printf.c					\

TEST_INC_FLAGS :=		-I$(UNITY_INC) -I$(UNITY_FIXTURE_INC) -I$(MOCKS_INC)

TEST_OBJS :=			$(addprefix $(TEST_OBJ_DIR)/, $(TEST_SRCS:.c=.o))

CC :=					clang

CC_FLAGS :=				-Wall
CC_FLAGS +=				-Wextra
CC_FLAGS +=				-Werror

TEST_CC_FLAGS :=		-Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rucs $(NAME) $(OBJS) $(LIBFT)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS_DEP)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(INC_FLAGS) $(LINK_FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

test: $(TEST_EXEC)
	clear
	./$(TEST_EXEC)

$(TEST_EXEC): $(NAME) $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(NAME) -o $(TEST_EXEC) 

$(TEST_OBJS): | $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%.o: %.c
	$(CC) -c $< -o $@ $(TEST_CC_FLAGS) $(UNITY_FLAGS) $(TEST_INC_FLAGS) $(INC_FLAGS)

check_printf: $(TEST_PRINTF_EXEC)
	clear
	$(TEST_PRINTF_EXEC)

$(TEST_PRINTF_EXEC): $(TEST_DIR)/$(TEST_REAL_PRINTF) $(NAME)
	$(CC) $(TEST_DIR)/$(TEST_REAL_PRINTF) $(NAME) $(INC_FLAGS) -o $(TEST_PRINTF_EXEC)

clean:
	rm -f $(OBJS)		
	rm -f $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_EXEC)
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_OBJ_DIR)

re: fclean all

.PHONY: all test clean fclean re

vpath %.c		$(SRC_DIR) $(TEST_DIR) $(UNITY_DIR)/src $(UNITY_DIR)/extras/fixture/src	$(MOCKS_DIR)
