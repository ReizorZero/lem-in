#include "lem_in.h"

t_room	*find_origin(t_info *info, t_room *room)
{
	t_room *temp;

	temp = info->graph_top;
	while (temp)
	{
		if (!ft_strcmp(temp->name, room->name))
			return (temp);
		// else
		// 	printf("temp name: %s, room name: %s\n", temp->name, room->name);
		temp = temp->next;
	}
	return (NULL);
}

void	check_ants_n(char *s, t_info *info)
{
	info->ants = ft_atoi(s);
	printf("%s\n", s);
	if (info->ants <= 0)
		ERROR_EXIT;
}

void	check_room(char *s, t_info *info, char flag)
{
	char	**arr;

	if (!ft_strchr(s, '-') && !(ft_strchr(s, '#')))
	{
		arr = ft_strsplit(s, ' ');
		if (!arr[1] || !arr[2] || arr[3])
			ERROR_EXIT;
		//printf("[%s] [%s] [%s] is a room\n", arr[0], arr[1], arr[2]);
		if (!info->graph)
		{
			info->graph = new_room(arr[0]);
			info->graph_top = info->graph;
		}
		else
		{
			info->graph->next = new_room(arr[0]);
			info->graph = info->graph->next;
		}
		if (flag == 's')
		{
			info->start = info->graph;
			printf("%s\n", s);
		}
		if (flag == 'e')
		{
			info->end = info->graph;
			printf("%s\n", s);
		}
	}
}

void	check_dashes(char *s, t_info *info)
{
	if (s[0] == '#')
	{
		if (!ft_strcmp(s, "##start"))
		{
			get_next_line(0, &s);
			check_room(s, info, 's');
		}
		else if (!ft_strcmp(s, "##end"))
		{
			get_next_line(0, &s);
			check_room(s, info, 'e');
		}
	}
}

void	check_connection(char *s, t_info *info)
{
	char	**arr;
	t_room	*temp;

	if (ft_strchr(s, '-') && !(ft_strchr(s, '#')))
	{
		arr = ft_strsplit(s, '-');
		if (!arr[1] || arr[2])
			ERROR_EXIT;
		//printf("\t[%s]-[%s] is a connection\n", arr[0], arr[1]);
		temp = info->graph_top;
		while (temp)
		{
			if (!ft_strcmp(arr[0], temp->name))
			{
				if (!temp->adj_room)
				{
					temp->adj_room = new_room(arr[1]);
					temp->adj_top = temp->adj_room;
				}
				else
				{
					temp->adj_room->next = new_room(arr[1]);
					temp->adj_room = temp->adj_room->next;
				}
			}
			temp = temp->next;
		}
		//we repeat it to create reverse edge
		temp = info->graph_top;
		while (temp)
		{
			if (!ft_strcmp(arr[1], temp->name))
			{
				if (!temp->adj_room)
				{
					temp->adj_room = new_room(arr[0]);
					temp->adj_top = temp->adj_room;
				}
				else
				{
					temp->adj_room->next = new_room(arr[0]);
					temp->adj_room = temp->adj_room->next;
				}
			}
			temp = temp->next;
		}
		//ERROR_EXIT;//no such room exists in the graph
	}
}

void	check_line(char *s, t_info *info)
{
	if (s[0] == '\0')
		ERROR_EXIT;
	check_dashes(s, info);
	check_room(s, info, '-');
	check_connection(s, info);
}

void	connect_origins(t_info *info)
{
	t_room *temp;
	t_room *temp_adj;

	temp = info->graph_top;
	while (temp)
	{
		temp_adj = temp->adj_top;
		while (temp_adj)
		{
			temp_adj->adj_origin = find_origin(info, temp_adj);
			temp_adj = temp_adj->next;
		}
		temp = temp->next;
	}
}

int		map(t_info *info)
{
	char *s;
	
	get_next_line(0, &s);
	check_ants_n(s, info);
	while (get_next_line(0, &s) > 0)
	{
		printf("%s\n", s);
		check_line(s, info);
	}
	printf("\n");
	connect_origins(info);
	return (1);
}