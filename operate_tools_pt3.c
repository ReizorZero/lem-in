/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_tools_pt3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:26:39 by rzero             #+#    #+#             */
/*   Updated: 2019/09/18 22:26:42 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	do_appendix_if(t_info **info, t_path **shortest, int shortest_len)
{
	(*info)->paths = new_path_list(*shortest);
	(*info)->paths->path_len = shortest_len;
	(*info)->paths_n++;
	(*info)->paths->id = (*info)->paths_n;
}

void	do_appendix_else_if(t_info **info, t_path **shortest, int shortest_len)
{
	(*info)->paths->next = new_path_list(*shortest);
	(*info)->paths->next->path_len = shortest_len;
	(*info)->paths = (*info)->paths->next;
	(*info)->paths_n++;
	(*info)->paths->id = (*info)->paths_n;
}

int		remove_ant_index(t_ant *ants_top, int index, t_info *info)
{
	t_ant *temp;
	t_ant *del;

	temp = ants_top;
	while (temp)
	{
		if (temp == ants_top && temp->index == index)
		{
			info->ants_n--;
			del = ants_top;
			ants_top = ants_top->next;
			return (1);
		}
		else if (temp->next && temp->next->index == index)
		{
			info->ants_n--;
			del = temp->next;
			free(del);
			temp->next = temp->next->next;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
