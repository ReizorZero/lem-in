#include "lem_in.h"

void	output_paths(t_info *info)//FOR SOME REASONS IT CAN'T BE REMOVED
{
	t_path_list *temp;
	t_path *temp_aside;

	temp = info->paths_top;
	while (temp)
	{
		temp_aside = temp->actual_path;
		while (temp_aside)
		{
			//printf("%s ~~> ", temp_aside->actual->name);
			temp_aside = temp_aside->prev;
		}
		// printf(" | len = %i", temp->path_len);
		// printf("\n");
		// printf("\n");
		temp = temp->next;
	}
	//printf("\n");
}

int	pathscmp(t_path *path1, t_path *path2)
{
	t_path *p1;
	t_path *p2;

	p1 = path1->head;
	p2 = path2->head;
	while (p1 || p2)
	{
		if ((p1 && !p2) || (!p1 && p2))
			return (1);
		if (ft_strcmp(p1->actual->name, p2->actual->name))
			return (1);
		p1 = p1->prev;
		p2 = p2->prev;
	}
	return (0);
}

void	distinct_paths(t_info *info)
{
	t_path_list *temp_pl;
	t_path_list *inn_temp_pl;
	t_path *temp;
	t_path *inn_temp;

	temp_pl = info->paths_top;
	while (temp_pl)//we go through all the paths in the list of found paths
	{
		temp = temp_pl->actual_path->head;
		while (temp)//we go through each room of a current path
		{
			inn_temp_pl = info->paths_top;
			while (inn_temp_pl)//we check occurence of current room in each path
			{
				inn_temp = inn_temp_pl->actual_path->head;
				while (inn_temp)//we finally compare current room with an actual room of current path
				{
					//if (!ft_strcmp(temp->actual->name, inn_temp->actual->name))
					
					//if (!ft_strcmp(temp->actual->name, inn_temp->actual->name) &&
					//ft_strcmp(temp->actual->name, info->start->name))//rooms are same, excluding end-room

					if (!ft_strcmp(temp->actual->name, inn_temp->actual->name))
					{
						// printf("WE NOTICED A DUPLICATION, SIR! LEN_1: %i, LEN_2: %i ", temp_pl->path_len,
						// inn_temp_pl->path_len);
						// printf("@ ROOM: %s ", temp->actual->name);
						if (!pathscmp(temp_pl->actual_path, inn_temp_pl->actual_path) &&
						temp_pl->path_len == inn_temp_pl->path_len)
						{
							//printf("<-- SAME ONE PATH");
						}
						else if (!ft_strcmp(temp->actual->name, info->end->name) &&
						!ft_strcmp(info->end->name, inn_temp->actual->name))
						{
							//printf("+++ THIS IS THE END");
						}
						else if (!ft_strcmp(temp->actual->name, info->start->name) &&
						!ft_strcmp(info->start->name, inn_temp->actual->name))
						{
							//printf("=== THIS IS THE START");
						}
						else
						{
							printf("WE NOTICED A DUPLICATION, SIR! LEN_1: %i, LEN_2: %i ", temp_pl->path_len,
						inn_temp_pl->path_len);
							printf("@ ROOM: %s \n", temp->actual->name);
						}
					}
					//inn_temp = inn_temp->next;
					inn_temp = inn_temp->prev;
				}
				inn_temp_pl = inn_temp_pl->next;
			}
			//temp = temp->next;
			temp = temp->prev;
		}
		temp_pl = temp_pl->next;
	}
}

void	distinct_paths_oldver(t_info *info)
{
	t_path_list *temp_pl;
	t_path_list *inn_temp_pl;
	t_path *temp;
	t_path *inn_temp;

	temp_pl = info->paths_top;
	while (temp_pl)//we go through all the paths in the list of found paths
	{
		temp = temp_pl->actual_path->head;
		while (temp)//we go through each room of a current path
		{
			inn_temp_pl = info->paths_top;
			while (inn_temp_pl)//we check occurence of current room in each path
			{
				inn_temp = inn_temp_pl->actual_path->head;
				while (inn_temp)//we finally compare current room with an actual room of current path
				{
					//if (!ft_strcmp(temp->actual->name, inn_temp->actual->name))
					
					//if (!ft_strcmp(temp->actual->name, inn_temp->actual->name) &&
					//ft_strcmp(temp->actual->name, info->start->name))//rooms are same, excluding end-room

					if (!ft_strcmp(temp->actual->name, inn_temp->actual->name))
					{
						printf("WE NOTICED A DUPLICATION, SIR! LEN_1: %i, LEN_2: %i ", temp_pl->path_len,
						inn_temp_pl->path_len);
						printf("@ ROOM: %s ", temp->actual->name);
						if (!pathscmp(temp_pl->actual_path, inn_temp_pl->actual_path) &&
						temp_pl->path_len == inn_temp_pl->path_len)
						{
							printf("<-- SAME ONE PATH");
						}
						if (!ft_strcmp(temp->actual->name, info->end->name) &&
						!ft_strcmp(info->end->name, inn_temp->actual->name))
						{
							printf("+++ THIS IS THE END");
						}
						if (!ft_strcmp(temp->actual->name, info->start->name) &&
						!ft_strcmp(info->start->name, inn_temp->actual->name))
						{
							printf("=== THIS IS THE START");
						}
						printf("\n");
					}
					//inn_temp = inn_temp->next;
					inn_temp = inn_temp->prev;
				}
				inn_temp_pl = inn_temp_pl->next;
			}
			//temp = temp->next;
			temp = temp->prev;
		}
		temp_pl = temp_pl->next;
	}
}

t_ant *new_ant(int index)
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

t_path *do_fucking_step(t_path *curr_path, t_info *info)
{
	//int x = info->ants; x++;
	if (!curr_path->prev)
	{
		//printf(" {{ants: %i}} ", info->ants);
		info->ants--;
	}
	else
		curr_path = curr_path->prev;
	return (curr_path);
}

void	fucking_ants(t_info *info)
{
	t_ant *ants;
	t_ant *ants_top;
	int ants_n;
	
	ants_n = 1;
	while (ants_n <= info->ants)
	{
		if (!ants)
			ants = new_ant(ants_n);
		else
		{
			ants->next = new_ant(ants_n);
			ants = ants->next;
		}
		if (!ants_top)
			ants_top = ants;
		ants_n++;
	}
	//printf("ANTS MADE: %i\n", ants_n);
	
	//CONNECT ANTS WITH CORRESPONDING PATHS
	t_ant *temp_ant;
	t_path_list *temp_paths;
	int set_delay;
	int delay_value;

	temp_ant = ants_top;
	temp_paths = info->paths_top;
	set_delay = -1;
	delay_value = 0;
	while (temp_ant)
	{
		if (temp_paths)
		{
			temp_ant->ant_path = temp_paths->actual_path;
			temp_paths = temp_paths->next;
		}
		else
		{
			temp_paths = info->paths_top;
			temp_ant->ant_path = temp_paths->actual_path;
			temp_paths = temp_paths->next;
		}
		set_delay++;
		if (set_delay == info->paths_n)
		{
			set_delay = 0;
			delay_value++;
		}
		temp_ant->delay = delay_value;
		temp_ant = temp_ant->next;
	}
	while (info->ants > 0)
	//for (int i = 0; i < info->ants /*+ 2*/ + 3; i++)
	{
		temp_ant = ants_top;
		while (temp_ant)
		{
			if (temp_ant->delay == 0)
				temp_ant->ant_path = do_fucking_step(temp_ant->ant_path, info);
			else
				temp_ant->delay--;
				if (temp_ant->ant_path->actual != info->end)
				{
					if (temp_ant->ant_path->actual != info->start)
					printf("L%i-%s ", temp_ant->index, temp_ant->ant_path->actual->name);
				}
				else if (temp_ant->at_end == 0)
				{
					printf("L%i-%s ", temp_ant->index, temp_ant->ant_path->actual->name);
					temp_ant->at_end = 1;
				}
			temp_ant = temp_ant->next;
		}
		//printf(" [ants: %i] ", info->ants);
		//if (info->ants >= -1)
		//{
			printf("\n");
		//}
	}
	free(ants);
}


// int	pathscmp(t_path *path1, t_path *path2)
// {
// 	t_path *p1;
// 	t_path *p2;

// 	p1 = path1->head;
// 	p2 = path2->head;
// 	while (p1 || p2)
// 	{
// 		if ((p1 && !p2) || (!p1 && p2))
// 			return (1);
// 		if (ft_strcmp(p1->actual->name, p2->actual->name))
// 			return (1);
// 		p1 = p1->prev;
// 		p2 = p2->prev;
// 	}
// 	return (0);
// }

void	operate(t_info *info)
{
	t_path *shortest;
	int shortest_len;

	shortest_len = 0;
	if (!info->start || !info->end)
		ERROR_EXIT;
	if (!info->start->adj_top || !info->end->adj_top)
		ERROR_EXIT;
	if (info->s_rooms != 1 || info->e_rooms != 1)
		ERROR_EXIT;
	while (info->start->adj_top)
	{
		bfs(info);
		shortest = shortest_path(info, &shortest_len);
		if (!shortest)
		{
			info->start->adj_top = NULL;
			break ;
		}
		if (!info->paths)
		{
			info->paths = new_path_list(shortest);
			info->paths->path_len = shortest_len;
			info->paths_n++;
		}
		else
		{
			if (pathscmp(info->paths->actual_path, shortest))
			{
				info->paths->next = new_path_list(shortest);
				info->paths->next->path_len = shortest_len;
				info->paths = info->paths->next;
				info->paths_n++;
			}
			else
				break ;
		}
		//printf("|| %s ||", info->graph_top->next->next->name);
		//if (info->graph_top->next->next->c_from)
			//info->graph_top->next->next->c_from = NULL;
		if (!info->paths_top)
			info->paths_top = info->paths;
	}
	//HERE IS WHERE WE WILL REMOVE PATHS WITH SAME ROOMS: FROM TWO PATHS WITH SAME ROOMS, WE KEEP SHORTER ONE
	distinct_paths(info);
	output_paths(info);
	//printf("paths: %i\n\n", info->paths_n);
	//fucking_ants(info);
}
