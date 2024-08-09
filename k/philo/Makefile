NAME = philo

SRC = food.c get_set.c init.c main.c monitor.c parse.c safe_function.c syn_utils.c utils.c write.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

DEL = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(DEL) $(OBJ) 

fclean: clean
	$(DEL) $(NAME)

re: fclean all

.PHONY: all clean fclean re
