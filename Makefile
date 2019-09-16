NAME = lem-in

SRCF = main.c libft/get_next_line.c map.c operate.c new_elements.c bfs.c check_room.c check_connection.c clear_all.c

LIB = libft/libft.a

CC = gcc -g #-fsanitize=address

CFLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCF)
	#make -C libft/ fclean && make -C libft/
	$(CC) $(CFLAG) -o $(NAME) $(SRCF) $(LIB)

clean:
	#make -C libft/ clean
	/bin/rm -f *.o

fclean: clean
	#make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all