NAME = libasm.a

NASM = nasm
CC = cc
AR = ar

NASMFLAGS = -f elf64
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR)

SRC_DIR = src
BONUS_DIR = bonus
TEST_DIR = test
OBJ_DIR = obj
INC_DIR = includes

SRCS = $(wildcard $(SRC_DIR)/*.s)
BONUS_SRCS = $(wildcard $(BONUS_DIR)/*.s)

OBJS = $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(SRCS))
BONUS_OBJS = $(patsubst $(BONUS_DIR)/%.s, $(OBJ_DIR)/bonus/%.o, $(BONUS_SRCS))

TEST = libasm_test

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/bonus/%.o: $(BONUS_DIR)/%.s
	@mkdir -p $(dir $@)
	$(NASM) $(NASMFLAGS) $< -o $@

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) rcs $(NAME) $(OBJS) $(BONUS_OBJS)

test: all
	$(CC) $(CFLAGS) $(TEST_DIR)/main.c $(NAME) -o $(TEST)
	./$(TEST)

clean:
	rm -rf $(OBJ_DIR)

fclean:
	rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re bonus test
