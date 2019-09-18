/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:12:16 by rzero             #+#    #+#             */
/*   Updated: 2019/09/17 16:12:19 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	unvisit_rooms(t_info *info)
{
	t_room *unvisit;
	
	unvisit = info->graph_top;
	while (unvisit)
	{
		unvisit->is_empty = 1;
		unvisit = unvisit->next;
	}
}

void	lost_qlist(t_info *info, t_qlist *qlost)
{
	if (!info->qlost)
		info->qlost = new_qlost(qlost);
	else
	{
		info->qlost->next = new_qlost(qlost);
		info->qlost = info->qlost->next;
	}
	if (!info->qlost_top)
		info->qlost_top = info->qlost;
}

void	bfs(t_info *info)
{
	t_qlist	*qlist;
	t_qlist	*qlist_top;
	t_room	*temp_adj;
	t_room	*qwerty;

	qwerty = info->graph_top;
	while (qwerty)
	{
		qwerty->c_from = NULL;
		qwerty = qwerty->next;
	}
	qlist = new_qlist(info->start);
	//lost_qlist(info, qlist);
	//printf("PROYOB QLIST===============\n");
	qlist_top = qlist;
	info->qlist_top = qlist;
	while (qlist_top)
	{
		if (qlist_top->actual == info->start)
		{
			temp_adj = qlist_top->actual->adj_top;
			qlist_top->actual->is_empty = 0;
		}
		else
			temp_adj = qlist_top->actual->adj_origin->adj_top;
		while (temp_adj)
		{
			if (temp_adj->adj_origin->is_empty == 1 && temp_adj->adj_origin->exist == 1)
			{
				qlist->next = new_qlist(temp_adj);
				//lost_qlist(info, qlist->next);
				//printf("PROYOB QLIST===============\n");
				qlist = qlist->next;
				temp_adj->adj_origin->is_empty = 0;
				temp_adj->adj_origin->c_from = qlist_top->actual;
			}
			//printf("PROYOB QLIST===============\n");
			temp_adj = temp_adj->next;
		}
		//PROBABLY THIS ALSO GIVES LEAKS
		qlist_top = qlist_top->next;
	}
	free_qlist(&info->qlist_top);
	unvisit_rooms(info);
}

void	collect_lost(t_info *info, t_room *lost_room)
{
	if (!info->lost_rooms)
		info->lost_rooms = new_qlist(lost_room);
	else
	{
		info->lost_rooms->next = new_qlist(lost_room);
		info->lost_rooms = info->lost_rooms->next;
	}
	if (!info->lost_top)
		info->lost_top = info->lost_rooms;
}

void	remove_connection(t_info *info, char *from, char *to)
{
	t_room *temp;
	t_room *temp_adj;

	temp = info->graph_top;
	while(temp)
	{
		if (!ft_strcmp(temp->name, from))
		{
			temp_adj = temp->adj_top;
			while (temp_adj)
			{
				if (temp_adj == temp->adj_top && !ft_strcmp(temp_adj->name, to))
				{
					//collect_lost(info, temp->adj_top);
					collect_lost(info, temp_adj);//does it matter if i replace it with temp->adj_top?
					temp->adj_top = temp->adj_top->next;
				}
				else if (temp_adj->next && !ft_strcmp(temp_adj->next->name, to))
				{
					collect_lost(info, temp_adj->next);
					temp_adj->next = temp_adj->next->next;
				}
				temp_adj = temp_adj->next;
			}
		}
		temp = temp->next;
	}
}

t_path	*shortest_path(t_info *info, int *shortest_len)
{
	t_room	*way;
	t_path	*shortest;
	t_path	*shortest_top;
	int		path_len;
	t_path	*head;
	t_path	*tail;

	path_len = 0;
	way = info->end;
	if (!info->end->c_from)
		return (NULL);
	shortest = new_path(way);
	tail = shortest;
	//printf("TAIL IS: %s\n", tail->actual->name);
	//printf("CREATED PATH\n");
	while (way)
	{
		shortest->next = new_path(way->c_from);
		//printf("CREATED PATH\n");
		shortest->next->prev = shortest;
		shortest = shortest->next;
		way = way->c_from->adj_origin;
	}
	shortest_top = shortest;
	head = shortest_top;
	while (shortest)
	{
		shortest->head = head;
		shortest->tail = tail;
		if (shortest->prev)
		{
			remove_connection(info, shortest->actual->name, shortest->prev->actual->name);
			remove_connection(info, shortest->prev->actual->name, shortest->actual->name);
		}
		path_len++;
		shortest = shortest->prev;
	}
	*shortest_len = path_len - 1;
	if (info->max_path_len < path_len - 1)
		info->max_path_len = path_len - 1;
	return (shortest_top);
}
