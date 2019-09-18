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

t_path_list	*new_path_list(t_path *path)
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

t_info		*new_info(void)
{
	t_info *info;

	info = (t_info*)malloc(sizeof(t_info));
	if (!info)
		ERROR_EXIT;
	ft_bzero(info, sizeof(t_info));
	return (info);
}

t_input		*new_input(char *str)
{
	t_input *input;

	input = (t_input*)malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->str = ft_strdup(str);
	input->next = NULL;
	return (input);
}

t_ant		*new_ant(int index)
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
