#include "lem_in.h"

// void free_qlist(t_qlist **qlist_top)
// {
// 	t_qlist *delete;
// 	t_qlist *current;

// 	current = (*qlist_top);
// 	while (current)
// 	{
// 		delete = current;
// 		current = current->next;
// 		free(delete->actual);
// 		//free(delete->next);//not sure here
// 		free(delete);
// 	}
// 	(*qlist_top) = NULL;
// }

// void	free_input(t_input **current)
// {
// 	t_input	*delete;

// 	if (current)
// 		while ((*current))
// 		{
// 			delete = (*current);
// 			(*current) = (*current)->next;
// 			free(delete);
// 		}
// }

// void	free_rooms(t_room **room)
// {
// 	t_room *delete;
// 	t_room *current;

// 	current = (*room);
// 	while (current)
// 	{
// 		delete = current;
// 		current = current->next;
// 		free(delete->name);
// 		//free(delete->next);//not sure here
// 		//free(delete);
// 	}
// 	(*room) = NULL;
// }

void	free_input(t_input **input)
{
	t_input	*delete;
	t_input	*current;

	current = (*input);
	while (current)
	{
		delete = current;
		current = current->next;
		free(delete->str);
		free(delete);
	}
	(*input) = NULL;
}

void	free_path(t_path **path)
{
	t_path	*delete;

	if (path)
		while ((*path))
		{
			delete = (*path);
			(*path) = (*path)->next;
			free(delete);
		}
}

void	free_paths_list(t_path_list **paths_list)
{
	t_path_list	*delete;

	if (paths_list)
		while ((*paths_list))
		{
			delete = (*paths_list);
			(*paths_list) = (*paths_list)->next;
			free_path(&(delete->actual_path));//deleting the path we have a pointer to
			free(delete);
		}
}

void	free_ants(t_ant **ant)
{
	t_ant	*delete;

	if (ant)
		while ((*ant))
		{
			//printf("DELETED AN ANT\n");
			delete = (*ant);
			(*ant) = (*ant)->next;
			free(delete);
		}
}

void	free_adj_graph(t_room **adj_graph)
{
	t_room	*delete;

	if (adj_graph)
		while ((*adj_graph))
		{
			delete = (*adj_graph);
			(*adj_graph) = (*adj_graph)->next;
			free(delete->name);
			free(delete);
		}
}

void	free_graph(t_room **graph)
{
	t_room	*delete;

	if (graph)
		while ((*graph))
		{
			delete = (*graph);
			(*graph) = (*graph)->next;
			free_adj_graph(&(delete->adj_top));//deleting the path we have a pointer to
			free(delete->name);
			free(delete);
		}
}

void	free_qlist(t_qlist **qlist)
{
	t_qlist	*delete;

	if (qlist)
		while ((*qlist))
		{
			delete = (*qlist);
			(*qlist) = (*qlist)->next;
			free(delete);
		}
}

void	clear_all(t_info **info)//probably, we should free paths after we free rooms/graph_top
{
	//int x = (*info)->ants_n; x++;
	free_input(&((*info)->input_top));
	// t_room	*graph;//del these + SUBLISTS
	free_paths_list(&((*info)->paths_top));
	// t_ant		*ants;//del these
	free_ants(&((*info)->ants_top));
	// t_qlist		*qlist_top;
	free_graph(&((*info)->graph_top));
	free_qlist(&((*info)->qlist_top));
}