NAME = lem-in

SRCF = main.c libft/get_next_line.c map.c operate.c new_elements.c bfs.c check_room.c check_connection.c clear_all.c efficiency.c bfs_tools.c clear_additional.c map_tools.c new_elements_pt2.c operate_tools.c operate_tools_pt2.c operate_tools_pt3.c bonuses.c

LIB = libft/libft.a ft_printf/libftprintf.a

CC = gcc #-g #-fsanitize=address

CFLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCF)
	make -C libft/ fclean && make -C libft/
	make -C ft_printf/ fclean && make -C ft_printf/
	$(CC) $(CFLAG) -o $(NAME) $(SRCF) $(LIB)

clean:
	make -C libft/ clean
	make -C ft_printf/ clean
	/bin/rm -f *.o

fclean: clean
	make -C libft/ fclean
	make -C ft_printf/ fclean
	/bin/rm -f $(NAME)

re: fclean all