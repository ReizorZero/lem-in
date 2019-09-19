/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:30:29 by rzero             #+#    #+#             */
/*   Updated: 2019/09/19 16:30:30 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	beautiful_ants(t_info *info)
{
	t_ant *temp_ant;

	while (info->ants_n > 0)
	{
		temp_ant = info->ants_top;
		while (temp_ant)
		{
			operate_delay(&temp_ant);
			if (temp_ant->ant_path->actual != info->end)
			{
				if (temp_ant->ant_path->actual != info->start)
					printf("🐜[%i]-🏠[%s] ", temp_ant->index,
				temp_ant->ant_path->actual->name);
			}
			else if (temp_ant->at_end == 0)
			{
				printf("🐜[%i]-🏠[%s] ", temp_ant->index,
				temp_ant->ant_path->actual->name);
				temp_ant->at_end = 1;
				remove_ant_index(info->ants_top, temp_ant->index, info);
			}
			temp_ant = temp_ant->next;
		}
		printf("\n🌱 🌿 🍃\n\n");
	}
}

void	output_graph(t_info *info)
{
	t_room *temp;
	t_room *temp_adj;

	temp = info->graph_top;
	while (temp)
	{
		temp_adj = temp->adj_top;
		ft_printf(" 🧔 👩 [%s]\n\t", temp->name);
		while (temp_adj)
		{
			ft_printf("👶 [%s] ", temp_adj->name);
			temp_adj = temp_adj->next;
		}
		ft_printf("\n\n");
		temp = temp->next;
	}
	ft_printf("\n");
}

void	show_help(void)
{
	ft_printf("FLAGS:\n\n--help:\n\tShows help info.\n\n");
	ft_printf("--beautify:\n\tAesthetic output of ants and rooms.\n\n");
	ft_printf("--leaks:\n\tChecks if any leaks are present.\n\n");
	ft_printf("--notext:\n\tRemoves file info from output.\n\n");
	ft_printf("--graph:\n\tShows the graph.\n\n");
	ft_printf("--ty:\n\tShows gratitude.\n");
	exit(0);
}

void	operate_flags(t_info *info, int argc, char **argv)
{
	if (argc > 2)
		ft_printf("One flag at a time, please! Use flag --help to see help.\n");
	else if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "--beautify"))
			info->beautiful_output = 1;
		else if (!ft_strcmp(argv[1], "--leaks"))
			info->output_leaks = 1;
		else if (!ft_strcmp(argv[1], "--notext"))
			info->no_file_output = 1;
		else if (!ft_strcmp(argv[1], "--graph"))
			info->output_graph = 1;
		else if (!ft_strcmp(argv[1], "--ty"))
			info->ty = 1;
		else if (!ft_strcmp(argv[1], "--help"))
			show_help();
		else
		{
			ft_printf("No such flag! Please, use --help flag to see info.\n");
			exit(0);
		}
	}
}
