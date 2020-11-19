SRCS =	ft_malcolm.c	\
	parsing.c	\

INC =	includes

NAME = ft_malcolm

CC = gcc

CFLAGS = -g3 -fsanitize=address

all:	$(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -I $(INC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
