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

void	add_line(t_info *info, char *s)
{
	if (!info->input)
	{
		info->input = new_input(s);
		info->input_top = info->input;
	}
	else
	{
		info->input->next = new_input(s);
		info->input = info->input->next;
	}
}

void	bfs(t_info *info)
{
	t_qlist	*qlist;
	t_qlist	*qlist_top;
	t_room	*temp_adj;

	qwerty(info);
	qlist = new_qlist(info->start);
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
		temp_adj_cycle(&temp_adj, &qlist, &qlist_top);
		qlist_top = qlist_top->next;
	}
	free_qlist(&info->qlist_top);
	unvisit_rooms(info);
}

void	remove_connection(t_info *info, char *from, char *to, t_room *temp)
{
	t_room *temp_adj;

	temp = info->graph_top;
	while (temp)
	{
		if (!ft_strcmp(temp->name, from))
		{
			temp_adj = temp->adj_top;
			while (temp_adj)
			{
				if (temp_adj == temp->adj_top && !ft_strcmp(temp_adj->name, to))
				{
					collect_lost(info, temp_adj);
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

int		shortest_cycle(t_info **info, t_path **shortest, t_path **head)
{
	int path_len;

	path_len = 0;
	while (*shortest)
	{
		(*shortest)->head = *head;
		if ((*shortest)->prev)
		{
			remove_connection(*info, (*shortest)->actual->name,
			(*shortest)->prev->actual->name, NULL);
			remove_connection(*info, (*shortest)->prev->actual->name,
			(*shortest)->actual->name, NULL);
		}
		path_len++;
		*shortest = (*shortest)->prev;
	}
	return (path_len);
}

t_path	*shortest_path(t_info *info, int *shortest_len)
{
	t_room	*way;
	t_path	*shortest;
	t_path	*shortest_top;
	int		path_len;
	t_path	*head;

	way = info->end;
	if (!info->end->c_from)
		return (NULL);
	shortest = new_path(way);
	while (way)
	{
		shortest->next = new_path(way->c_from);
		shortest->next->prev = shortest;
		shortest = shortest->next;
		way = way->c_from->adj_origin;
	}
	head = shortest;
	shortest_top = shortest;
	path_len = shortest_cycle(&info, &shortest, &head);
	*shortest_len = path_len - 1;
	if (info->max_path_len < path_len - 1)
		info->max_path_len = path_len - 1;
	return (shortest_top);
}
