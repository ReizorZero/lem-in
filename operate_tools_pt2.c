/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_tools_pt2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:24:28 by rzero             #+#    #+#             */
/*   Updated: 2019/09/18 22:24:30 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*do_fucking_step(t_ant *ant)
{
	if (ant->ant_path->prev)
		ant->ant_path = ant->ant_path->prev;
	return (ant->ant_path);
}

void	create_ants(t_info *info)
{
	int ants_n;

	ants_n = 1;
	while (ants_n <= info->ants_n)
	{
		if (!info->ants)
			info->ants = new_ant(ants_n);
		else
		{
			info->ants->next = new_ant(ants_n);
			info->ants = info->ants->next;
		}
		if (!info->ants_top)
			info->ants_top = info->ants;
		ants_n++;
	}
}

void	ants_appendix(t_info **info, t_path_list **temp_paths, t_ant **temp_ant)
{
	if (*temp_paths)
	{
		(*temp_ant)->ant_path = (*temp_paths)->actual_path;
		*temp_paths = (*temp_paths)->next;
	}
	else
	{
		*temp_paths = (*info)->paths_top;
		(*temp_ant)->ant_path = (*temp_paths)->actual_path;
		*temp_paths = (*temp_paths)->next;
	}
}

void	operate_delay(t_ant **temp_ant)
{
	if ((*temp_ant)->delay == 0)
		(*temp_ant)->ant_path = do_fucking_step(*temp_ant);
	else
		(*temp_ant)->delay--;
}
