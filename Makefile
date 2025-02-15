NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I. -pthread -fsanitize=thread
SRC = init.c main.c math.c set_table.c routines.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re