/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:56:41 by rzero             #+#    #+#             */
/*   Updated: 2019/09/18 20:56:43 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*find_origin(t_info *info, t_room *room)
{
	t_room *temp;

	temp = info->graph_top;
	while (temp)
	{
		if (!ft_strcmp(temp->name, room->name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	check_ants_n(char *s, t_info *info)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i]))
			ERROR_EXIT;
		i++;
	}
	info->ants_n = ft_atoi(s);
	add_line(info, s);
	free(s);
	if (info->ants_n <= 0)
		ERROR_EXIT;
}

int		check_existing(t_info *info, char *room_name, int x, int y)
{
	t_room *temp;

	temp = info->graph_top;
	while (temp)
	{
		if (!ft_strcmp(temp->name, room_name))
			ERROR_EXIT;
		if (temp->x == x && temp->y == y)
			ERROR_EXIT;
		temp = temp->next;
	}
	return (1);
}

void	appendix(t_info *info, char *s)
{
	get_next_line(0, &s);
	if (!ft_strcmp(s, "##end") || ft_strchr(s, '-'))
		ERROR_EXIT;
	while (s[0] == '#')
	{
		free(s);
		get_next_line(0, &s);
	}
	check_room(s, info, 'e');
	free(s);
}

void	check_dashes(char *s, t_info *info)
{
	if (s[0] == '#')
	{
		if (!ft_strcmp(s, "##start"))
		{
			get_next_line(0, &s);
			if (!ft_strcmp(s, "##start") || ft_strchr(s, '-'))
				ERROR_EXIT;
			while (s[0] == '#')
			{
				free(s);
				get_next_line(0, &s);
			}
			check_room(s, info, 's');
			free(s);
		}
		else if (!ft_strcmp(s, "##end"))
			appendix(info, s);
	}
}
