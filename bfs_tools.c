/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:16:40 by rzero             #+#    #+#             */
/*   Updated: 2019/09/18 20:16:43 by rzero            ###   ########.fr       */
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

void	qwerty(t_info *info)
{
	t_room	*qwerty;

	qwerty = info->graph_top;
	while (qwerty)
	{
		qwerty->c_from = NULL;
		qwerty = qwerty->next;
	}
}

void	temp_adj_cycle(t_room **temp_adj, t_qlist **qlist, t_qlist **qlist_top)
{
	while (*temp_adj)
	{
		if ((*temp_adj)->adj_origin->is_empty == 1)
		{
			(*qlist)->next = new_qlist(*temp_adj);
			(*qlist) = (*qlist)->next;
			(*temp_adj)->adj_origin->is_empty = 0;
			(*temp_adj)->adj_origin->c_from = (*qlist_top)->actual;
		}
		(*temp_adj) = (*temp_adj)->next;
	}
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
