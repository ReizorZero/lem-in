#include "lem_in.h"

void	output_paths(t_info *info)
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
	// int *i;
	// int j;

	// i = (int*)malloc(sizeof(int) * info->paths_n);
	// j = 0;
	// while (j < info->paths_n)
	// {
	// 	i[j] = j + 1;
	// 	j++;
	// }
	// j = 0;
	printf("Printing ants...\n");
	printf("\nants: %i\n", info->ants);
	printf("paths: %i\n\n", info->paths_n);

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
	// printf("SMART INDIRECT OUTPUT\n");
	// while (info->paths_top)//replace with a pointer for the fuck's sake
	// {
	// 	while (info->paths_top->actual_path)
	// 	{
	// 		printf("Lx-%s ", info->paths_top->actual_path->actual->name);
	// 		info->paths_top->actual_path = info->paths_top->actual_path->prev;			
	// 	}
	// 	printf("\n");
	// 	info->paths_top = info->paths_top->next;
	// }

	// printf("EVEN SMARTER INDIRECT OUTPUT\n");
	// t_path_list *temp_path;
	// //while (info->paths_top)//replace with a pointer for the fuck's sake
	// while (info->paths_top->actual_path)//replace with a pointer for the fuck's sake
	// {
	// 	//while (info->paths_top->actual_path)
	// 	temp_path = info->paths_top;
	// 	while (temp_path)
	// 	{
	// 		//printf("Lx-%s ", info->paths_top->actual_path->actual->name);
	// 		printf("Lx-%s ", temp_path->actual_path->actual->name);
	// 		//info->paths_top->actual_path = info->paths_top->actual_path->prev;			
	// 		temp_path->actual_path = temp_path->actual_path->prev;
	// 	}
	// 	printf("\n");
	// 	//info->paths_top = info->paths_top->next;
	// 	info->paths_top->actual_path = info->paths_top->actual_path->prev;
	// }

	printf("THE SMARTEST INDIRECT OUTPUT\n");
	//assume that we already have the precise value of longest path length
	int max_path_len = 7;
	int i = 0;
	
	t_path_list *saved;
	saved = info->paths_top;

	info->paths_top->actual_path = info->paths_top->actual_path->prev;
	while (i < max_path_len)
	{
		if (info->paths_top->actual_path)//if we have the room
		{
			t_path_list *temp_path;
			temp_path = info->paths_top;
			while (temp_path)
			{
				if (temp_path->actual_path->actual->name)
					printf("Lx-%s ", temp_path->actual_path->actual->name);
				temp_path = temp_path->next;
				if (temp_path)
				temp_path->actual_path = temp_path->actual_path->prev;
			}
			info->paths_top->actual_path = info->paths_top->actual_path->prev;
			printf("\n");
		}
		else
		{	
			// if (!info->paths_top->actual_path)
			// {
			// 	printf("HOLY SHIT, MARY\n");
			// }
			if (!info->paths_top->actual_path && saved->next)
			{
				while (saved->next->actual_path->prev)
				{
					printf("Lx-%s\n", saved->next->actual_path->prev->actual->name);
					saved->next->actual_path->prev = saved->next->actual_path->prev->prev;
				}
			}
		}
		i++;
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
	}
	output_paths(info);
	output_ants(info);
}