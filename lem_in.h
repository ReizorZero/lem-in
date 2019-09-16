#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //DEL THEN
# include "libft/libft.h"
# include "libft/get_next_line.h"

# define ERROR_EXIT { ft_putendl("ERROR"); exit(0); }

typedef struct	s_room
{
	char			*name;
	struct s_room	*next;
	struct s_room	*adj_room;//MALLOC
	struct s_room	*adj_top;
	struct s_room	*c_from;
	struct s_room	*adj_origin;
	int				is_empty;
	int 			x;
	int 			y;
}				t_room;

typedef struct	s_path
{
	struct s_path	*head;
	struct s_path	*next;
	struct s_path	*prev;
	t_room			*actual;
	//int				path_len;
	//int			ant_index;
}				t_path;

typedef struct	s_path_list
{
	struct s_path_list	*next;
	t_path 				*actual_path;
	int					path_len;
	int					id;
	//int			ant_index;
}				t_path_list;

typedef struct	s_input
{
	char *str;
	struct	s_input *next;
}				t_input;

typedef struct	s_ant
{
	struct s_ant	*next;
	t_path			*ant_path;
	int				index;
	int				delay;
	int				at_end;
}				t_ant;

typedef struct	s_qlist
{
	struct s_qlist	*next;
	t_room			*actual;
}				t_qlist;

typedef struct	s_info
{
	int		ants_n;
	int		s_rooms;
	int		e_rooms;
	t_room	*start;
	t_room	*end;
	t_room	*graph;//del these
	t_room	*graph_top;
	t_path_list	*paths;//del these
	t_path_list	*paths_top;
	int			paths_n;
	int			max_path_len;
	char		sorry;
	t_input		*input;//del these
	t_input		*input_top;
	//t_path	*shortest_path;//for the case with one ant
	t_ant		*ants;//del these
	t_ant		*ants_top;
	t_qlist		*qlist_top;
}				t_info;

int			map(t_info *info);
int	check_first_comment(char *s, t_info *info);
void	connect_origins(t_info *info);
void	check_line(char *s, t_info *info);
int	check_connection(char *s, t_info *info);
void connection_exists(t_info *info, char *room_1, char *room_2);
void	check_dashes(char *s, t_info *info);
int	check_room(char *s, t_info *info, char flag);
int check_existing(t_info *info, char *room_name, int x, int y);
void	check_ants_n(char *s, t_info *info);
t_room	*find_origin(t_info *info, t_room *room);
void add_line(t_info *info, char *s);

t_info		*new_info(void);
t_input		*new_input(char *str);
t_room		*new_room(char *name, int x, int y);
t_qlist		*new_qlist(t_room *room);
t_path		*new_path(t_room *room);
t_path_list *new_path_list(t_path *path);
t_ant *new_ant(int index);

void		operate(t_info *info);
void		bfs(t_info *info);
t_path	*shortest_path(t_info *info, int *shortest_len);
void	clear_all(t_info **info);

void	free_path(t_path **path);
//void free_qlist(t_qlist **qlist_top);

void	print_two_dim(t_room *dat);//REMOVE THEN

#endif