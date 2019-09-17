/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_connection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:12:30 by rzero             #+#    #+#             */
/*   Updated: 2019/09/17 16:12:33 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_defis(char *s)
{
	int i;
	int defis;

	i = 0;
	defis = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			defis++;
		i++;
	}
	if (defis > 1)
		ERROR_EXIT;
}

void	find_room(char *s1, char *s2, t_info *info)
{
	int		room_found;
	t_room	*temp;
	//t_room *del;

	room_found = 0;
	temp = info->graph_top;
	while (temp)
	{
		if (!ft_strcmp(s1, temp->name))
		{
			room_found = 1;
			if (!temp->adj_room)
				temp->adj_room = new_room(s2, 0, 0);
			else
			{
				temp->adj_room->next = new_room(s2, 0, 0);
				//del = temp->adj_room->next;
				// free(del->name);
				// free(del);
				temp->adj_room = temp->adj_room->next;
				//free(del->name);
				//free(del);
			}
			if (!temp->adj_top)
				temp->adj_top = temp->adj_room;
		}
		temp = temp->next;
	}
	if (!room_found)
		ERROR_EXIT;
}

int		check_connection(char *s, t_info *info)
{
	char	**arr;

	if (ft_strchr(s, '-') && !(ft_strchr(s, '#')))
	{
		check_defis(s);
		arr = ft_strsplit(s, '-');
		if (!arr[1] || arr[2])
			ERROR_EXIT;
		connection_exists(info, arr[0], arr[1]);
		find_room(arr[0], arr[1], info);
		find_room(arr[1], arr[0], info);
		info->sorry = 'c';
		free(arr[0]);
		free(arr[1]);
		free(arr);
		return (1);
	}
	return (0);
}
