#include "lem_in.h"

/*
void	output_paths(t_info *info)//REMOVE WHEN NOT NEEDED
{
	t_path_list *temp;
	t_path *temp_aside;

	temp = info->paths_top;
	while (temp)
	{
		temp_aside = temp->actual_path;
		while (temp_aside)
		{
			printf("%s ~~> ", temp_aside->actual->name);
			temp_aside = temp_aside->prev;
		}
		//printf(" | id = %i | len = %i\n", temp->id, temp->path_len);

		printf(" | id = %i | len = %i\n\n", temp->id, temp->path_len);
		
		//printf(" | id = %i\n\n", temp->id);
		//printf(" | len = %i", temp->path_len);
		//printf("\n");
		//printf("\n");
		temp = temp->next;
	}
	//printf("\n");
}
*/

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

int remove_ant_index(t_ant *ants_top, int index, t_info *info)
{
	t_ant *temp;
	t_ant *del;

	temp = ants_top;
	while (temp)
	{
		if (temp == ants_top && temp->index == index)//head of the list
		{
			info->ants_n--;
			del = ants_top;
			ants_top = ants_top->next;//AND CLEAN THE FUCKING LEAKS, SON!
			return (1);
		}
		else if (temp->next && temp->next->index == index)
		{
			info->ants_n--;
			del = temp->next;
			free(del);
			temp->next = temp->next->next;//CLEAN THE FUCKING LEAKS HERE AS WELL, SON!
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int remove_path_id(t_info *info, int id)
{
	t_path_list *temp;
	t_path_list *del;

	temp = info->paths_top;
	while (temp)
	{
		if (temp == info->paths_top && temp->id == id)//head of the list
		{
			info->paths_top = info->paths_top->next;//AND CLEAN THE FUCKING LEAKS, SON!
			info->paths_n--;
			return (1);
		}
		else if (temp->next && temp->next->id == id)
		{
			info->paths_n--;
			del = temp->next;
			free_path(&(del->actual_path));//I dunno does that even work
			free(del);
			temp->next = temp->next->next;//CLEAN THE FUCKING LEAKS HERE AS WELL, SON!
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	distinct_rooms(t_info *info)
{
	t_room *temp_room;
	t_path_list *temp_pl;
	t_path *temp_path;
	t_path_list *last_path;
	int occ;

	temp_room = info->graph_top;
	while (temp_room)//we go through all the rooms
	{
		occ = 0;
		temp_pl = info->paths_top;
		last_path = NULL;
		while (temp_pl)//we go through all the paths
		{
			temp_path = temp_pl->actual_path->head;
			while (temp_path)//we go through all the rooms in this path
			{
				if (!ft_strcmp(temp_room->name, temp_path->actual->name)
				&& ft_strcmp(temp_room->name, info->start->name)
				&& ft_strcmp(temp_room->name, info->end->name))
				{
					if (!last_path)
					last_path = temp_pl;//we mark the path, if it has the room - it's first occurance (once)
					else
					{
						(temp_pl->path_len >= last_path->path_len) ? remove_path_id(info, temp_pl->id) :
						remove_path_id(info, last_path->id);
					}
					occ++;
				}
				temp_path = temp_path->prev;
			}
			temp_pl = temp_pl->next;
		}
		temp_room = temp_room->next;
	}
}

t_path *do_fucking_step(t_ant *ant)//, t_info *info)
{
	//int x = info->ants_n; x++;
	// if (!ant->ant_path->prev)
	// {
	// 	//printf(" {{ants: %i}} ", info->ants);
	// 	//printf(" [remove ant %i] ", ant->index);
	// 	//remove_ant_index(ant->index);
	// 	//info->ants--;
	// }
	// else
	if (ant->ant_path->prev)
		ant->ant_path = ant->ant_path->prev;
	//printf(" {{ants: %i}} ", info->ants);
	return (ant->ant_path);
}

void	create_ants(t_info *info)
{
	int ants_n;
	
	ants_n = 1;
	while (ants_n <= info->ants_n)
	{
		if (!info->ants)
			info->ants = new_ant(ants_n);
		else
		{
			info->ants->next = new_ant(ants_n);
			info->ants = info->ants->next;
		}
		if (!info->ants_top)
			info->ants_top = info->ants;
		ants_n++;
	}
}

void set_ants_delay(t_info *info)
{
	t_ant *temp_ant;
	t_path_list *temp_paths;
	int set_delay;
	int delay_value;

	temp_ant = info->ants_top;
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
}

void	fucking_ants(t_info *info)
{
	t_ant *temp_ant;

	create_ants(info);
	set_ants_delay(info);
	while (info->ants_n > 0)
	{
		temp_ant = info->ants_top;
		while (temp_ant)
		{
			if (temp_ant->delay == 0)
				temp_ant->ant_path = do_fucking_step(temp_ant);
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
				remove_ant_index(info->ants_top, temp_ant->index, info);
			}
			temp_ant = temp_ant->next;
		}
			printf("\n");
	}
}

void	operate(t_info *info)
{
	t_path *shortest;
	int shortest_len;

	shortest_len = 0;
	while (info->start->adj_top)
	{
		bfs(info);//<--LEEKS
		//free_qlist(&((info)->qlist_top));
		//system("leaks -q lem-in");
		//ERROR_EXIT;
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
			info->paths->id = info->paths_n;
		}
		else
		{
			if (pathscmp(info->paths->actual_path, shortest))
			{
				info->paths->next = new_path_list(shortest);
				info->paths->next->path_len = shortest_len;
				info->paths = info->paths->next;
				info->paths_n++;
				info->paths->id = info->paths_n;
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
	//free_qlist(&((info)->qlist_top));
	// system("leaks -q lem-in");
	// ERROR_EXIT;
	distinct_rooms(info);
	fucking_ants(info);
}
