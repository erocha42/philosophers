NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I.

OBJ_DIR = objs

SRC = utils.c routine.c reaper.c routine_utils.c


OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) main.c -o $(NAME)

$(OBJ_DIR)/%.o: %.c philosophers.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re