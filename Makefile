TARGET_LIB :=			libftprintf.a

SRC_DIR :=				./src
LIB_DIR :=				./lib
OBJ_DIR :=				./obj

INC_DIRS :=				./include					\

HEADERS :=				ft_printf.h					\

SRCS :=					ft_printf.c					\

OBJS :=					$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC_FLAGS :=			$(addprefix -I, $(INC_DIRS))

TEST_DIR :=				./t
TEST_EXEC :=			$(TEST_DIR)/printf_test	
TEST_OBJ_DIR :=			$(TEST_DIR)/obj

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
						ft_printf_test.c				\
						ft_printf_test_runner.c


TEST_INC_FLAGS :=		-I$(UNITY_INC) -I$(UNITY_FIXTURE_INC) -I$(MOCKS_INC)

TEST_OBJS :=			$(addprefix $(TEST_OBJ_DIR)/, $(TEST_SRCS:.c=.o))

CC :=					clang

CC_FLAGS :=				-Wall
CC_FLAGS +=				-Wextra
CC_FLAGS +=				-Werror

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	ar rucs $(TARGET_LIB) $(OBJS)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(INC_FLAGS)

test: $(TEST_EXEC)
	clear
	./$(TEST_EXEC)

$(TEST_EXEC): $(TARGET_LIB) $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(TARGET_LIB) -o $(TEST_EXEC) 

$(TEST_OBJS): | $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%.o: %.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(UNITY_FLAGS) $(TEST_INC_FLAGS) $(INC_FLAGS)

clean:
	rm -f $(OBJS)		
	rm -f $(TEST_OBJS)

fclean: clean
	rm -f $(TARGET_LIB)
	rm -f $(TEST_EXEC)
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_OBJ_DIR)

.PHONY: all test clean fclean

vpath %.c		$(SRC_DIR) $(TEST_DIR) $(UNITY_DIR)/src $(UNITY_DIR)/extras/fixture/src	$(MOCKS_DIR)
