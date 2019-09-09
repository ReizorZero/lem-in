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
		//printf("\n");
		temp = temp->next;
	}
	//printf("\n");
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
	if (!curr_path->prev)
		info->ants--;
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
	//free(ants_top);//GAVE ME SEGV SOMEHOW
	//DO NOT CHANGE LEAKS AMOUNT
	//free(temp_ant);
	//free(temp_paths);
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
	//free(p1);
	//free(p2);
}

void	operate(t_info *info)
{
	t_path *shortest;

	if (!info->start->adj_top || !info->end->adj_top)
		ERROR_EXIT;
	while (info->start->adj_top)
	{
		bfs(info);
		shortest = shortest_path(info);
		if (!info->paths)
		{
			info->paths = new_path_list(shortest);
			info->paths_n++;
		}
		else
		{
			if (pathscmp(info->paths->actual_path, shortest))
			{
				info->paths->next = new_path_list(shortest);
				info->paths = info->paths->next;
				info->paths_n++;
			}
			else
				break ;
		}
		if (!info->paths_top)
			info->paths_top = info->paths;
	}
	output_paths(info);
	fucking_ants(info);
	//free(shortest);
}