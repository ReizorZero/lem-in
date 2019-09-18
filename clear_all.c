/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:12:59 by rzero             #+#    #+#             */
/*   Updated: 2019/09/17 16:13:01 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
			(*path) = (*path)->prev;
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
			free_path(&(delete->actual_path));
			free(delete);
		}
}

void	free_ants(t_ant **ant)
{
	t_ant	*delete;

	if (ant)
		while ((*ant))
		{
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
	(*adj_graph) = NULL;
}

void	free_graph(t_room **graph)
{
	t_room	*delete;

	if (graph)
		while ((*graph))
		{
			delete = (*graph);
			(*graph) = (*graph)->next;
			free_adj_graph(&(delete->adj_top));
			free(delete->name);
			free(delete);
		}
	(*graph) = NULL;
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

void	free_lost_rooms(t_qlist **lost)
{
	t_qlist	*delete;

	if (lost)
		while ((*lost))
		{
			delete = (*lost);
			(*lost) = (*lost)->next;
			free(delete->actual->name);
			free(delete->actual);
			free(delete);
		}
	(*lost) = NULL;
}

void	free_qlost(t_qlost **qlost)
{
	t_qlost	*delete;

	if (qlost)
		while ((*qlost))
		{
			delete = (*qlost);
			(*qlost) = (*qlost)->next;
			free(delete);
		}
}

void	clear_all(t_info **info)
{
	free_input(&((*info)->input_top));
	free_paths_list(&((*info)->paths_top));
	free_ants(&((*info)->ants_top));
	free_graph(&((*info)->graph_top));
	free_lost_rooms(&((*info)->lost_top));
	free(*info);
}
