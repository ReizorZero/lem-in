/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:13:37 by rzero             #+#    #+#             */
/*   Updated: 2019/09/17 16:13:39 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_file(t_info *info)
{
	t_input *temp_inpt;

	temp_inpt = info->input_top;
	while (temp_inpt)
	{
		ft_printf("%s\n", temp_inpt->str);
		temp_inpt = temp_inpt->next;
	}
	ft_printf("\n");
}

void	do_the_rest(t_info *info)
{
	distinct_rooms(info, NULL, NULL, NULL);
	if (info->ants_n > 1 && info->paths_n > 1)
		efficiency(info, 0);
	create_ants(info);
	set_ants_delay(info);
	if (info->beautiful_output == 1)
		beautiful_ants(info);
	else
		fucking_ants(info);
	if (info->output_leaks == 1)
		system("leaks -q lem-in");
	if (info->ty == 1)
		ft_printf("\n❤️ ❤️ ❤️  THANK YOU!️️ ❤️ ❤️ ❤️\n");
}

int		main(int argc, char **argv)
{
	t_info *info;

	info = new_info();
	operate_flags(info, argc, argv);
	if (map(info))
	{
		if (info->no_file_output == 0)
			print_file(info);
		if (info->output_graph == 1)
			output_graph(info);
		operate(info, NULL, 0);
		do_the_rest(info);
	}
	else
		ERROR_EXIT;
	return (0);
}
