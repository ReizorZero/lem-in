/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:13:23 by rzero             #+#    #+#             */
/*   Updated: 2019/09/17 16:13:26 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include "libft/get_next_line.h"

# define ERROR_EXIT { ft_putendl("ERROR"); exit(0); }

typedef struct	s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}				t_garbage;

typedef struct	s_room
{
	char			*name;
	struct s_room	*next;
	struct s_room	*adj_room;
	struct s_room	*adj_top;
	struct s_room	*c_from;
	struct s_room	*adj_origin;
	int				is_empty;
	int				x;
	int				y;
}				t_room;

typedef struct	s_path
{
	struct s_path	*head;
	struct s_path	*next;
	struct s_path	*prev;
	t_room			*actual;
}				t_path;

typedef struct	s_path_list
{
	struct s_path_list	*next;
	t_path				*actual_path;
	int					path_len;
	int					id;
}				t_path_list;

typedef struct	s_input
{
	char			*str;
	struct s_input	*next;
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

typedef struct	s_qlost
{
	struct s_qlost	*next;
	t_qlist			*actual;
}				t_qlost;

typedef struct	s_info
{
	int			ants_n;
	int			s_rooms;
	int			e_rooms;
	t_room		*start;
	t_room		*end;
	t_room		*graph;
	t_room		*graph_top;
	t_path_list	*paths;
	t_path_list	*paths_top;
	int			paths_n;
	int			max_path_len;
	char		sorry;
	t_input		*input;
	t_input		*input_top;
	t_ant		*ants;
	t_ant		*ants_top;
	t_qlist		*qlist_top;
	t_qlist		*lost_rooms;
	t_qlist		*lost_top;
	t_qlost		*qlost;
	t_qlost		*qlost_top;
	t_garbage	*g;
	t_garbage	*top_g;
	int			occ;
}				t_info;

int				map(t_info *info);
int				check_first_comment(char *s, t_info *info);
void			connect_origins(t_info *info);
void			check_line(char *s, t_info *info);
int				check_connection(char *s, t_info *info);
void			connection_exists(t_info *info, char *room_1, char *room_2);
void			check_dashes(char *s, t_info *info);
int				check_room(char *s, t_info *info, char flag);
int				check_existing(t_info *info, char *room_name, int x, int y);
void			check_ants_n(char *s, t_info *info);
t_room			*find_origin(t_info *info, t_room *room);
void			add_line(t_info *info, char *s);

t_info			*new_info(void);
t_input			*new_input(char *str);
t_room			*new_room(char *name, int x, int y);
t_qlist			*new_qlist(t_room *room);
t_path			*new_path(t_room *room);
t_path_list		*new_path_list(t_path *path);
t_ant			*new_ant(int index);
t_qlost			*new_qlost(t_qlist *qlist);
t_garbage		*new_garbage(void *ptr);

void			operate(t_info *info, t_path *shortest, int	shortest_len);
void			bfs(t_info *info);
t_path			*shortest_path(t_info *info, int *shortest_len);

void			efficiency(t_info *info, int i);
int				remove_path_id(t_info *info, int id);

void			clear_all(t_info **info);

void			free_graph(t_room **graph);
void			free_path(t_path **path);
void			free_qlist(t_qlist **qlist);
void			free_input(t_input **input);
void			free_path(t_path **path);
void			free_paths_list(t_path_list **paths_list);
void			free_ants(t_ant **ant);
void			free_adj_graph(t_room **adj_graph);

void			collect_lost(t_info *info, t_room *lost_room);
void			temp_adj_cycle(t_room **temp_adj,
t_qlist **qlist, t_qlist **qlist_top);
void			qwerty(t_info *info);
void			lost_qlist(t_info *info, t_qlist *qlost);
void			unvisit_rooms(t_info *info);

void			distinct_rooms(t_info *info, t_room *temp_room,
t_path_list		*temp_pl, t_path *temp_path);
void			create_ants(t_info *info);
void			set_ants_delay(t_info *info);
void			fucking_ants(t_info *info);

int				pathscmp(t_path *path1, t_path *path2);
void			to_garbage(t_info *info, void *ptr);
int				condition(t_info *info, t_room *temp_room, t_path *temp_path);
void			remove_one(t_info *info,
t_path_list *temp_pl, t_path_list *last_path);
void			obnulyai_brat(t_info **info, int *occ, t_path_list **temp_pl,
t_path_list **last_path);
void			ants_appendix(t_info **info,
t_path_list **temp_paths, t_ant **temp_ant);
void			operate_delay(t_ant **temp_ant);
int				remove_ant_index(t_ant *ants_top, int index, t_info *info);
void			do_appendix_if(t_info **info,
t_path **shortest, int shortest_len);
void			do_appendix_else_if(t_info **info,
t_path **shortest, int shortest_len);

#endif
