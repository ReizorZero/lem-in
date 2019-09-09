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
	info->ants = ft_atoi(s);
	printf("%s\n", s);
	free(s);
	if (info->ants <= 0)
		ERROR_EXIT;
}

void	check_room(char *s, t_info *info, char flag)
{
	char	**arr;
	int i;
	int spaces;

	i = 0;
	spaces = 0;
	if (!ft_strchr(s, '-') && !(ft_strchr(s, '#')))
	{
		while (s[i] != '\0')
		{
			if (s[i] == ' ')
				spaces++;
			i++;
		}
		if (spaces > 2)
			ERROR_EXIT;
		arr = ft_strsplit(s, ' ');
		if (!arr[1] || !arr[2] || arr[3] || arr[0][0] == 'L')
			ERROR_EXIT;
		i = 0;
		while (arr[1][i] != '\0')
		{
			if (!ft_isdigit(arr[1][i]))
				ERROR_EXIT;
			i++;
		}
		i = 0;
		while (arr[2][i] != '\0')
		{
			if (!ft_isdigit(arr[1][i]))
				ERROR_EXIT;
			i++;
		}
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
			info->s_rooms++;
			printf("%s\n", s);
		}
		if (flag == 'e')
		{
			info->end = info->graph;
			info->e_rooms++;
			printf("%s\n", s);
		}
		//free(*arr);
		//free(arr);
		free(arr[0]); free(arr[1]); free(arr[2]); free(arr); //free(*arr);
	}
	// else
	// 	ERROR_EXIT;
}

void	check_dashes(char *s, t_info *info)
{
	if (s[0] == '#')
	{
		if (!ft_strcmp(s, "##start"))
		{
			get_next_line(0, &s);
			//add here another correction to any other cases
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
		{
			get_next_line(0, &s);
			//add here another correction to any other cases
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
	}
}

void	check_connection(char *s, t_info *info)
{
	int i;
	char	**arr;
	t_room	*temp;
	int room_found;
	int defis;

	i = 0;
	defis = 0;
	room_found = 0;
	if (ft_strchr(s, '-') && !(ft_strchr(s, '#')))// && !(ft_strchr(s, ' ')))
	{
		while (s[i] != '\0')
		{
			if (s[i] == '-')
				defis++;
			i++;
		}
		if (defis > 1)
			ERROR_EXIT;
		arr = ft_strsplit(s, '-');
		if (!arr[1] || arr[2])
			ERROR_EXIT;
		//printf("\t[%s]-[%s] is a connection\n", arr[0], arr[1]);
		temp = info->graph_top;
		while (temp)
		{
			if (!ft_strcmp(arr[0], temp->name))
			{
				room_found = 1;
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
		if (!room_found)//no corresponding room to this connection
			ERROR_EXIT;
		//we repeat it to create reverse edge
		room_found = 0;
		temp = info->graph_top;
		while (temp)
		{
			if (!ft_strcmp(arr[1], temp->name))
			{
				room_found = 1;
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
		if (!room_found)//no corresponding room to this connection
			ERROR_EXIT;
		//ERROR_EXIT;//no such room exists in the graph
		free(arr[0]); free(arr[1]); free(arr); //free(*arr);
	}
}

void	check_line(char *s, t_info *info)
{
	char prev;
	
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

int	check_first_comment(char *s, t_info *info)
{
	get_next_line(0, &s);
	if (s[0] == '#')
	{
		if (!ft_strcmp(s, "##start") || !ft_strcmp(s, "##end"))
			ERROR_EXIT;
		printf("%s\n", s);
		free(s);
	}
	else
	{
		check_ants_n(s, info);
		return (0);
	}
	return (1);
}

int		map(t_info *info)
{
	char *s;

	s = NULL;
	while (check_first_comment(s, info))
		;
	while (get_next_line(0, &s) > 0)
	{
		printf("%s\n", s);
		check_line(s, info);
		free(s);
	}
	printf("\n");
	connect_origins(info);
	return (1);
}