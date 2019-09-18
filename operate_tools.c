/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:21:49 by rzero             #+#    #+#             */
/*   Updated: 2019/09/18 22:21:51 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		pathscmp(t_path *path1, t_path *path2)
{
	t_path *p1;
	t_path *p2;

	p1 = path1->head;
	p2 = path2->head;
	while (p1 || p2)
	{
		if ((p1 && !p2) || (!p1 && p2))
			return (1);
		if (ft_strcmp(p1->actual->name, p2->actual->name))
			return (1);
		p1 = p1->prev;
		p2 = p2->prev;
	}
	return (0);
}

void	to_garbage(t_info *info, void *ptr)
{
	if (!info->g)
		info->g = new_garbage(ptr);
	else
	{
		info->g->next = new_garbage(ptr);
		info->g = info->g->next;
	}
	if (!info->top_g)
		info->top_g = info->g;
}

int		condition(t_info *info, t_room *temp_room, t_path *temp_path)
{
	if (!ft_strcmp(temp_room->name, temp_path->actual->name)
	&& ft_strcmp(temp_room->name, info->start->name)
	&& ft_strcmp(temp_room->name, info->end->name))
		return (1);
	return (0);
}

void	remove_one(t_info *info, t_path_list *temp_pl, t_path_list *last_path)
{
	(temp_pl->path_len >= last_path->path_len) ?
	remove_path_id(info, temp_pl->id) :
	remove_path_id(info, last_path->id);
}

void	obnulyai_brat(t_info **info, int *occ, t_path_list **temp_pl,
t_path_list **last_path)
{
	*occ = 0;
	*temp_pl = (*info)->paths_top;
	*last_path = NULL;
}
