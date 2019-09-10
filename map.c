#include "lem_in.h"

void add_line(t_info *info, char *s)
{
	//printf("ADDED LINE: %s\n", s);
	if (!info->input)
	{
		info->input = new_input(s);
		info->input_top = info->input;
	}
	else
	{
		info->input->next = new_input(s);
		info->input = info->input->next;
	}
}

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
	//printf("%s\n", s);
	add_line(info, s);
	free(s);
	if (info->ants <= 0)
		ERROR_EXIT;
}

int check_existing(t_info *info, char *room_name, int x, int y)
{
	t_room *temp;

	temp = info->graph_top;
	while (temp)
	{
		if (!ft_strcmp(temp->name,room_name))
			ERROR_EXIT;
		if (temp->x == x && temp->y == y)
			ERROR_EXIT;
		temp = temp->next;
	}
	return (1);
}

int	check_room(char *s, t_info *info, char flag)
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
			info->graph = new_room(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
			info->graph_top = info->graph;
		}
		else
		{
			check_existing(info, arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
			info->graph->next = new_room(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
			info->graph = info->graph->next;
		}
		if (flag == 's')
		{
			info->start = info->graph;
			info->s_rooms++;
			//printf("%s\n", s);
			add_line(info, s);
		}
		if (flag == 'e')
		{
			info->end = info->graph;
			info->e_rooms++;
			//printf("%s\n", s);
			add_line(info, s);
		}
		//free(*arr);
		//free(arr);
		free(arr[0]); free(arr[1]); free(arr[2]); free(arr); //free(*arr);
        return (1);
	}
    return (0);
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

void connection_exists(t_info *info, char *room_1, char *room_2)
{
	t_room *temp;
	t_room *temp_adj;

	temp = info->graph_top;
	while (temp)
	{
		if (!ft_strcmp(temp->name, room_1))
		{
			temp_adj = temp->adj_top;
			while (temp_adj)
			{
				if (!ft_strcmp(temp_adj->name, room_2))
					ERROR_EXIT;
				temp_adj = temp_adj->next;
			}
		}
		temp = temp->next;
	}
}

int	check_connection(char *s, t_info *info)
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
		connection_exists(info, arr[0], arr[1]);
		temp = info->graph_top;
		while (temp)
		{
			if (!ft_strcmp(arr[0], temp->name))
			{
				room_found = 1;
				if (!temp->adj_room)
				{
					temp->adj_room = new_room(arr[1], 0, 0);
					temp->adj_top = temp->adj_room;
				}
				else
				{
					temp->adj_room->next = new_room(arr[1], 0, 0);
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
					temp->adj_room = new_room(arr[0], 0, 0);
					temp->adj_top = temp->adj_room;
				}
				else
				{
					temp->adj_room->next = new_room(arr[0], 0, 0);
					temp->adj_room = temp->adj_room->next;
				}
			}
			temp = temp->next;
		}
		if (!room_found)//no corresponding room to this connection
			ERROR_EXIT;
		//ERROR_EXIT;//no such room exists in the graph
		free(arr[0]); free(arr[1]); free(arr); //free(*arr);
        info->sorry = 'c';
        return (1);
	}
    return (0);
}

void	check_line(char *s, t_info *info)
{
    int found_room;
    int found_connection;

    if (s[0] == '\0')
		ERROR_EXIT;
	check_dashes(s, info);
    found_connection = check_connection(s, info);
	found_room = check_room(s, info, '-');
    if (found_room == 1 && info->sorry == 'c')
        ERROR_EXIT;
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
		//printf("%s\n", s);
		add_line(info, s);
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
	//info->input = (t_input*)malloc(sizeof(t_input));
	//if (!info->input)//hueta, but let it be, I don't fucking care
	//	ERROR_EXIT;
	while (check_first_comment(s, info))
		;
	while (get_next_line(0, &s) > 0)
	{
		//printf("%s\n", s);
		add_line(info, s);
		check_line(s, info);
		free(s);
	}
	//printf("\n");
	connect_origins(info);
	return (1);
}