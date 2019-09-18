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

t_garbage *new_garbage(void *ptr)
{
	t_garbage *garbage;

	garbage = (t_garbage*)malloc(sizeof(garbage));
	garbage->ptr = ptr;
	garbage->next = NULL;
	return (garbage);
}

t_room		*new_room(char *name, int x, int y)
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	room->name = ft_strdup(name);
	room->next = NULL;
	room->adj_room = NULL;
	room->c_from = NULL;
	room->adj_origin = NULL;
	room->is_empty = 1;
	room->x = x;
	room->y = y;
	return (room);
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
	info->g = NULL;
	info->top_g = NULL;
	return (info);
}

t_input *new_input(char *str)
{
	t_input *input;

	input = (t_input*)malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->str = ft_strdup(str);
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
