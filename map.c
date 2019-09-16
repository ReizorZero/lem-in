#include "lem_in.h"

void add_line(t_info *info, char *s)
{
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
	info->ants_n = ft_atoi(s);
	add_line(info, s);
	free(s);
	if (info->ants_n <= 0)
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


void	check_dashes(char *s, t_info *info)//REDUCE LENGTH HERE
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
	while (check_first_comment(s, info))
		;
	while (get_next_line(0, &s) > 0)
	{
		add_line(info, s);
		check_line(s, info);
		free(s);
	}
	connect_origins(info);
	if (!info->start || !info->end)
		ERROR_EXIT;
	if (!info->start->adj_top || !info->end->adj_top)
		ERROR_EXIT;
	if (info->s_rooms != 1 || info->e_rooms != 1)
		ERROR_EXIT;
	return (1);
}