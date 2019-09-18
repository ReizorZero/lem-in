/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_elements_pt2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:02:07 by rzero             #+#    #+#             */
/*   Updated: 2019/09/18 21:02:09 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_garbage	*new_garbage(void *ptr)
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

t_path		*new_path(t_room *room)
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
