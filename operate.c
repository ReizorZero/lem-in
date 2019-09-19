/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:14:11 by rzero             #+#    #+#             */
/*   Updated: 2019/09/17 16:14:13 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		remove_path_id(t_info *info, int id)
{
	t_path_list *temp;

	temp = info->paths_top;
	while (temp)
	{
		if (temp == info->paths_top && temp->id == id)
		{
			info->paths_top = info->paths_top->next;
			info->paths_n--;
			return (1);
		}
		else if (temp->next && temp->next->id == id)
		{
			info->paths_n--;
			to_garbage(info, temp->next);
			to_garbage(info, temp->next->actual_path);
			temp->next = temp->next->next;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	distinct_rooms(t_info *info, t_room *temp_room,
t_path_list *temp_pl, t_path *temp_path)
{
	t_path_list	*last_path;

	temp_room = info->graph_top;
	while (temp_room)
	{
		obnulyai_brat(&info, &info->occ, &temp_pl, &last_path);
		while (temp_pl)
		{
			temp_path = temp_pl->actual_path->head;
			while (temp_path)
			{
				if (condition(info, temp_room, temp_path))
				{
					if (!last_path)
						last_path = temp_pl;
					else
						remove_one(info, temp_pl, last_path);
					info->occ++;
				}
				temp_path = temp_path->prev;
			}
			temp_pl = temp_pl->next;
		}
		temp_room = temp_room->next;
	}
}

void	set_ants_delay(t_info *info)
{
	t_ant		*temp_ant;
	t_path_list	*temp_paths;
	int			set_delay;
	int			delay_value;

	temp_ant = info->ants_top;
	temp_paths = info->paths_top;
	set_delay = -1;
	delay_value = 0;
	while (temp_ant)
	{
		ants_appendix(&info, &temp_paths, &temp_ant);
		set_delay++;
		if (set_delay == info->paths_n)
		{
			set_delay = 0;
			delay_value++;
		}
		temp_ant->delay = delay_value;
		temp_ant = temp_ant->next;
	}
}

void	fucking_ants(t_info *info)
{
	t_ant *temp_ant;

	while (info->ants_n > 0)
	{
		temp_ant = info->ants_top;
		while (temp_ant)
		{
			operate_delay(&temp_ant);
			if (temp_ant->ant_path->actual != info->end)
			{
				if (temp_ant->ant_path->actual != info->start)
					printf("L%i-%s ", temp_ant->index,
				temp_ant->ant_path->actual->name);
			}
			else if (temp_ant->at_end == 0)
			{
				printf("L%i-%s ", temp_ant->index,
				temp_ant->ant_path->actual->name);
				temp_ant->at_end = 1;
				remove_ant_index(info->ants_top, temp_ant->index, info);
			}
			temp_ant = temp_ant->next;
		}
		printf("\n");
	}
}

void	operate(t_info *info, t_path *shortest, int shortest_len)
{
	while (info->start->adj_top)
	{
		bfs(info);
		shortest = shortest_path(info, &shortest_len);
		if (!shortest)
		{
			info->start->adj_top = NULL;
			break ;
		}
		if (!info->paths)
			do_appendix_if(&info, &shortest, shortest_len);
		else
		{
			if (pathscmp(info->paths->actual_path, shortest))
				do_appendix_else_if(&info, &shortest, shortest_len);
			else
				break ;
		}
		if (!info->paths_top)
			info->paths_top = info->paths;
	}
}
