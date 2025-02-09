NAME = philo 

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

SRC = philo.c life_philo.c init.c control.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re