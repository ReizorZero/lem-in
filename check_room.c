/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:12:46 by rzero             #+#    #+#             */
/*   Updated: 2019/09/17 16:12:48 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_spaces(char *s)
{
	int i;
	int spaces;

	i = 0;
	spaces = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			spaces++;
		i++;
	}
	if (spaces > 2)
		ERROR_EXIT;
}

void	check_digits(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (!ft_isdigit(s1[i]))
			ERROR_EXIT;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		if (!ft_isdigit(s2[i]))
			ERROR_EXIT;
		i++;
	}
}

void	check_flag(char *s, t_info *info, char flag)
{
	if (flag == 's')
	{
		info->start = info->graph;
		info->s_rooms++;
		add_line(info, s);
	}
	if (flag == 'e')
	{
		info->end = info->graph;
		info->e_rooms++;
		add_line(info, s);
	}
}

int		check_room(char *s, t_info *info, char flag)//clean leaks here
{
	char	**arr;

	if (!ft_strchr(s, '-') && !(ft_strchr(s, '#')))
	{
		check_spaces(s);
		arr = ft_strsplit(s, ' ');
		if (!arr[1] || !arr[2] || arr[3] || arr[0][0] == 'L')
			ERROR_EXIT;
		check_digits(arr[1], arr[2]);
		if (!info->graph)
		{
			info->graph = new_room(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
			info->graph_top = info->graph;
		}
		else
		{
			check_existing(info, arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
			info->graph->next = new_room(arr[0],
			ft_atoi(arr[1]), ft_atoi(arr[2]));
			info->graph = info->graph->next;
		}
		check_flag(s, info, flag);
		free(arr[0]); free(arr[1]); free(arr[2]); free(arr);//REMOVE THIS SHIT WITH FUNCTION, THAT DELETES ARRAY
		return (1);
	}
	return (0);
}
