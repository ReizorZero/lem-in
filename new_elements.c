/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:14:00 by rzero             #+#    #+#             */
/*   Updated: 2019/09/17 16:14:04 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*new_room(char *name, int x, int y)
{
	t_room *room;
	//char *temp;

	room = (t_room*)malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	//		BLYAD, POFIKSI ETO!!!!! 


	// temp = room->name;
	// room->name = ft_strdup(name);
	// free(temp);//WHY THE FUCK Y NO WORK???
	
	//temp = ft_strdup(name);
	// room->name = (char*)malloc(sizeof(char) * ft_strlen(name));
	// ft_strcpy(room->name, name);
	//temp = NULL;
	// free(temp);//WHY THE FUCK Y NO WORK???

	// room->name = (char*)malloc(sizeof(char) * ft_strlen(name));
	// ft_strcpy(room->name, name);

	room->name = ft_strdup(name);
	room->next = NULL;
	room->adj_room = NULL;
	room->c_from = NULL;
	room->adj_origin = NULL;
	room->is_empty = 1;
	room->x = x;
	room->y = y;
	room->exist = 1;
	return (room);
}

t_smth	*new_smth(t_path_list *lost_pl)
{
	t_smth *smth;

	smth = (t_smth*)malloc(sizeof(t_smth));
	smth->actual = lost_pl;
	smth->next = NULL;
	return (smth);
}

t_qlost		*new_qlost(t_qlist *qlist)
{
	t_qlost *qlost;

	qlost = (t_qlost*)malloc(sizeof(t_qlost));
	if (!qlost)
		return (NULL);
	qlost->actual = qlist;
	qlost->next = NULL;
	return (qlost);
}

t_qlist		*new_qlist(t_room *room)
{
	t_qlist *qlist;

	qlist = (t_qlist*)malloc(sizeof(t_qlist));
	if (!qlist)
		return (NULL);
	qlist->actual = room;
	qlist->next = NULL;
	return (qlist);
}

t_path *new_path(t_room *room)
{
	t_path *path;

	path = (t_path*)malloc(sizeof(t_path));
	if (!path)
		return (NULL);
	path->actual = room;
	path->next = NULL;
	path->prev = NULL;
	path->head = NULL;
	path->tail = NULL;
	return (path);
}

t_path_list *new_path_list(t_path *path)
{
	t_path_list *path_list;

	path_list = (t_path_list*)malloc(sizeof(t_path_list));
	if (!path_list)
		return (NULL);
	path_list->next = NULL;
	path_list->actual_path = path;
	path_list->path_len = 0;
	path_list->id = 0;
	return (path_list);
}

t_info *new_info(void)
{
	t_info *info;

	info = (t_info*)malloc(sizeof(t_info));
	if (!info)
		ERROR_EXIT;
	//ft_bzero(info, sizeof(t_info));//uncomment this, and all next lines are not needed
	info->ants_n = 0;
	info->s_rooms = 0;
	info->e_rooms = 0;
	info->start = NULL;
	info->end = NULL;
	info->graph = NULL;
	info->graph_top = NULL;
	info->paths = NULL;
	info->paths_top = NULL;
	info->paths_n = 0;
	info->max_path_len = 0;
	info->sorry = 0;
	info->input = NULL;
	info->input_top = NULL;
	info->ants = NULL;
	info->ants_top = NULL;
	info->qlist_top = NULL;
	info->lost_rooms = NULL;
	info->qlost = NULL;
	info->qlost_top = NULL;
	info->lost_pl = NULL;
	info->top_lost_pl = NULL;
	//info->temp = NULL;
	return (info);
}

t_input *new_input(char *str)
{
	t_input *input;

	input = (t_input*)malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->str = ft_strdup(str);//clear memory here should you do it
	input->next = NULL;
	return (input);
}

t_ant *new_ant(int index)
{
	t_ant *ant;

	ant = (t_ant*)malloc(sizeof(t_ant));
	if (!ant)
		return (NULL);
	ant->ant_path = NULL;
	ant->index = index;
	ant->delay = 0;
	ant->at_end = 0;
	ant->next = NULL;
	return (ant);
}
