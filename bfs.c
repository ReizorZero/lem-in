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

void	bfs(t_info *info)
{
	t_qlist *qlist;
	t_qlist *qlist_top;
	t_room *temp_adj;
	t_room *qwerty;

	qwerty = info->graph_top;
	while (qwerty)
	{
		qwerty->c_from = NULL;
		qwerty = qwerty->next;
	}
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
		while (temp_adj)
		{
			if (temp_adj->adj_origin->is_empty == 1)
			{
				qlist->next = new_qlist(temp_adj);
				qlist = qlist->next;
				temp_adj->adj_origin->is_empty = 0;
				temp_adj->adj_origin->c_from = qlist_top->actual;
			}
			temp_adj = temp_adj->next;
		}
		qlist_top = qlist_top->next;
	}
	unvisit_rooms(info);
}

void	remove_connection(t_room *from, char *to)
{
	t_room *temp_adj;

	if (from->adj_origin)
	{
		temp_adj = from->adj_origin->adj_top;
		while (temp_adj)
		{
			if (!ft_strcmp(temp_adj->name, to))
				from->adj_origin->adj_top = from->adj_origin->adj_top->next;
			else if (temp_adj->next && !ft_strcmp(temp_adj->next->name, to))
				temp_adj->next = temp_adj->next->next;
			temp_adj = temp_adj->next;
		}
	}
	if (!from->adj_origin)
	{
		temp_adj = from->adj_top;
		while (temp_adj)
		{
			if (!ft_strcmp(temp_adj->name, to))

				from->adj_top = from->adj_top->next;
			else if (temp_adj->next && !ft_strcmp(temp_adj->next->name, to))
				temp_adj->next = temp_adj->next->next;
			temp_adj = temp_adj->next;
		}
	}
}

t_path	*shortest_path(t_info *info, int *shortest_len)
{
	t_room *way;
	t_path *shortest;
	t_path *shortest_top;
	int path_len;
	t_path *head;

	path_len = 0;
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
	shortest_top = shortest;
	head = shortest_top;
	while (shortest)
	{
		shortest->head = head;
		if (shortest->prev)
		{
			remove_connection(shortest->actual, shortest->prev->actual->name);
			remove_connection(shortest->prev->actual, shortest->actual->name);
		}
		path_len++;
		shortest = shortest->prev;
	}
	*shortest_len = path_len - 1;
	if (info->max_path_len < path_len - 1)
		info->max_path_len = path_len - 1;
	return (shortest_top);
}