#include "lem_in.h"

void	output_paths(t_info *info)//REMOVE THEN
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
		printf("\n");
		temp = temp->next;
	}
	printf("\n");
}

void	output_ants(t_info *info)
{
	printf("Printing ants...\n");
	printf("\nants: %i\n", info->ants);
	printf("paths: %i\n\n", info->paths_n);
	printf("max_path_len: %i\n\n", info->max_path_len);

	// //========STUPID DIRECT OUTPUT
	// printf("STUPID DIRECT OUTPUT\n");
	// printf("Lx-%s ", info->paths_top->actual_path->prev->actual->name);
	// printf("Lx-%s\n", info->paths_top->next->actual_path->prev->actual->name);

	// printf("Lx-%s ", info->paths_top->actual_path->prev->prev->actual->name);
	// printf("Lx-%s\n", info->paths_top->next->actual_path->prev->prev->actual->name);

	// printf("Lx-%s ", info->paths_top->actual_path->prev->prev->prev->actual->name);
	// printf("Lx-%s\n", info->paths_top->next->actual_path->prev->prev->prev->actual->name);

	// printf("Lx-%s\n", info->paths_top->next->actual_path->prev->prev->prev->prev->actual->name);
	// printf("Lx-%s\n", info->paths_top->next->actual_path->prev->prev->prev->prev->prev->actual->name);
	// printf("Lx-%s\n", info->paths_top->next->actual_path->prev->prev->prev->prev->prev->prev->actual->name);
	// printf("Lx-%s\n", info->paths_top->next->actual_path->prev->prev->prev->prev->prev->prev->prev->actual->name);
	// //=============

	printf("THE SMARTEST INDIRECT OUTPUT\n");
	int i = 0;
	t_path_list *saved;
	saved = info->paths_top;

	info->paths_top->actual_path = info->paths_top->actual_path->prev;
	//while (i < max_path_len)
	//int a = 1;
	int b = 0;
	while (i < info->max_path_len)
	{
		int a = 1;
		if (info->paths_top->actual_path)//if we have the room
		{
			//int a = 1;
			t_path_list *temp_path;
			temp_path = info->paths_top;
			while (temp_path)
			{
				if (temp_path->actual_path->actual->name)
					printf("L%i-%s ", a, temp_path->actual_path->actual->name);
				temp_path = temp_path->next;
				if (temp_path)
				temp_path->actual_path = temp_path->actual_path->prev;
				a++;
			}
			info->paths_top->actual_path = info->paths_top->actual_path->prev;
			b = a - 1;
			//printf(" [minus ant] ");
			printf("\n");
		}
		else
		{	
			//int b = a;
			// if (!info->paths_top->actual_path)
			// {
			// 	printf("HOLY SHIT, MARY\n");
			// }
			//printf(" [minus ant] ");
			if (!info->paths_top->actual_path && saved->next)
			{
				while (saved->next->actual_path->prev)
				{
					printf("L%i-%s\n", b, saved->next->actual_path->prev->actual->name);
					//printf(" [minus ant] ");
					saved->next->actual_path->prev = saved->next->actual_path->prev->prev;
				}
			}
		}
		//printf(" [minus ant] ");
		i++;
	}
}

void	print_ants_1(t_info *info)
{
	int i;
	int j;

	i = 1;
	j = 1;
	printf("ants: %i\n", info->ants);
	//==============================
	t_path_list *temp;
	t_path *temp_aside;

	temp = info->paths_top;
	while (temp)
	{
		temp_aside = temp->actual_path->prev;
		printf("L%i-%s ", i, temp_aside->actual->name);
		i++;
		temp = temp->next;
	}
	printf("\n");
	i = 1;
	temp = info->paths_top;
	while (temp)
	{
		temp_aside = temp->actual_path->prev->prev;
		printf("L%i-%s ", i, temp_aside->actual->name);
		i++;
		temp = temp->next;
	}
	printf("\n");
	i = 2;
	temp = info->paths_top;
	while (temp)
	{
		temp_aside = temp->actual_path->prev->prev->prev;
		if (temp_aside)
		{
			printf("L%i-%s ", i, temp_aside->actual->name);
			i++;
		}
		temp = temp->next;
	}
	printf("\n");
}

t_path *do_step(t_path *curr_path, t_info *info)
{
	if (!curr_path->prev)
	{
		info->ants--; //info->ants++;
		curr_path = curr_path->head->prev;
		//printf("\n");
	}
	else
		curr_path = curr_path->prev;
	return (curr_path);
}

void	print_ants(t_info *info)
{
	int i;
	//info->ants = 1;

	//i = info->ants - 1;
	//info->ants++; info->ants++;
	t_path_list *temp_paths;
	printf("ants: %i\n", info->ants);
	while (info->ants > 0)
	{
		//i = 1;
		i = info->ants;
		//i = info->ants - 1;
		temp_paths = info->paths_top;
		while (temp_paths)
		{
			temp_paths->actual_path = do_step(temp_paths->actual_path, info);
			printf("L%i-%s\t", i, temp_paths->actual_path->actual->name);
			i--;//i++;

			//printf("L%i-%s\t", info->ants - i, temp_paths->actual_path->actual->name);
			//i--;
			temp_paths = temp_paths->next;
		}
		printf("\n");
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
	//printf("index: %i\n", ant->index);
	ant->next = NULL;
	return (ant);
}

t_path *do_fucking_step(t_path *curr_path, t_info *info)
{
	if (!curr_path->prev)
	{
		//curr_path = curr_path->head->prev;
		//printf("\n");
		info->ants--;
	}
	// else if (curr_path->actual == info->end)
	// {
	// 	return (NULL);	
	// }
	else
		curr_path = curr_path->prev;
	return (curr_path);
}

void	fucking_ants(t_info *info)
{
	t_ant *ants;
	t_ant *ants_top;
	int ants_n;

	//info->ants = 11;
	//info->ants = 7;
	printf("ants: %i\n", info->ants);
	printf("paths: %i\n\n", info->paths_n);
	
	//CREATE ANTS
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
		//printf("ANT: %i\n", temp_ant->index);
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
		//if (set_delay)
		//printf("set_delay: %i\n", set_delay);
		set_delay++;
		if (set_delay == info->paths_n)// + 1)
		{
			set_delay = 0;
			//printf("aha!\n");
			delay_value++;
		}
		//printf("\tdelay_value: %i\n", delay_value);
		temp_ant->delay = delay_value;
		temp_ant = temp_ant->next;
	}

	//PRINT ALL PATHS
	// temp_ant = ants_top;
	// while (temp_ant)
	// {
	// 	printf("ANT: %i\n\t", temp_ant->index);
	// 	while (temp_ant->ant_path)
	// 	{
	// 		printf("%s ", temp_ant->ant_path->actual->name);
	// 		temp_ant->ant_path = temp_ant->ant_path->prev;
	// 	}
	// 	printf("\n");
	// 	temp_ant = temp_ant->next;
	// }

	//PRINT ALL PATHS WITHOUT START-ROOMS
	// temp_ant = ants_top;
	// while (temp_ant)
	// {
	// 	while (temp_ant->ant_path)
	// 	{
	// 		if (temp_ant->ant_path->actual != info->start)
	// 			printf("%s ", temp_ant->ant_path->actual->name);
	// 		temp_ant->ant_path = temp_ant->ant_path->prev;
	// 	}
	// 	printf("\n");
	// 	temp_ant = temp_ant->next;
	// }

	//PRINT ALL LINES WITHOUT START-ROOMS
	//temp_ant = ants_top;
	// while (temp_ant)
	// {
	// 	if (temp_ant->ant_path)
	// 	{
	// 		if (temp_ant->ant_path->actual != info->start)
	// 			printf("%s ", temp_ant->ant_path->actual->name);
	// 		//temp_ant->ant_path = temp_ant->ant_path->prev;
	// 	}
	// 	temp_ant->ant_path = temp_ant->ant_path->prev;
	// 	printf("\n");
	// 	temp_ant = temp_ant->next;
	// }

	while (info->ants > 0)
	{
		temp_ant = ants_top;
		while (temp_ant)
		{
			//if (temp_ant->ant_path->actual != info->end)
			if (temp_ant->delay == 0)
				temp_ant->ant_path = do_fucking_step(temp_ant->ant_path, info);
			else
				temp_ant->delay--;
			//if (temp_ant->delay == 0)
			// {
				//printf("L%i=%s->delay(%i)\t", temp_ant->index, temp_ant->ant_path->actual->name, temp_ant->delay);
				if (temp_ant->ant_path->actual != info->end)
				{
					if (temp_ant->ant_path->actual != info->start)
					//printf("-->");
					printf("L%i-%s\t", temp_ant->index, temp_ant->ant_path->actual->name);
				}
				else if (temp_ant->at_end == 0)
				{
					//if (temp_ant->ant_path->actual != info->start)
					printf("L%i-%s\t", temp_ant->index, temp_ant->ant_path->actual->name);
					temp_ant->at_end = 1;
				}
				//temp_ant = temp_ant->next;
			//}
			// else
			// {
			// 	temp_ant->delay--;
			// }
			temp_ant = temp_ant->next;
		}
		printf("\n");
	}
}

void	operate(t_info *info)
{
	printf("THE MAP IS OK, OPERATING...\n");
	// printf("\nants: %i\n\n", info->ants);
	// printf("GRAPH:\n");
	printf("\nstart: %s\n", info->start->name);
	printf("end: %s\n", info->end->name);
	while (info->start->adj_top)
	{
		bfs(info);
		if (!info->paths)
		{
			info->paths = new_path_list(shortest_path(info));
			info->paths_n++;
		}
		else
		{
			info->paths->next = new_path_list(shortest_path(info));
			info->paths = info->paths->next;
			info->paths_n++;
		}
		if (!info->paths_top)
			info->paths_top = info->paths;
		if (info->max_path_len == 243 || info->max_path_len == 213)
			exit(0);
	}
	output_paths(info);
	//output_ants(info);
	//print_ants(info);
	fucking_ants(info);
}