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
	struct s_room	*adj_room;
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
	//int			ant_index;
}				t_path_list;

typedef struct	s_info
{
	int		ants;
	int		s_rooms;
	int		e_rooms;
	t_room	*start;
	t_room	*end;
	t_room	*graph;
	t_room	*graph_top;
	t_path_list	*paths;
	t_path_list	*paths_top;
	int			paths_n;
	int			max_path_len;
	char		sorry;
	//t_path	*shortest_path;//for the case with one ant
}				t_info;

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

typedef struct	s_input
{
	char *name;
	struct	s_input *next;
}				t_input;

int			map(t_info *info);
t_info		*new_info(void);
t_room		*new_room(char *name, int x, int y);
t_qlist		*new_qlist(t_room *room);
t_path		*new_path(t_room *room);
t_path_list *new_path_list(t_path *path);
void		operate(t_info *info);
void		bfs(t_info *info);
t_path		*shortest_path(t_info *info);
void		additional_paths(t_info *info);

#endif