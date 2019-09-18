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
		printf("%s\n", temp_inpt->str);
		temp_inpt = temp_inpt->next;
	}
	printf("\n");
}

void	do_the_rest(t_info *info)
{
	distinct_rooms(info, NULL, NULL, NULL);
	if (info->ants_n > 1 && info->paths_n > 1)
		efficiency(info, 0);
	create_ants(info);
	set_ants_delay(info);
	fucking_ants(info);
}

int		main(void)
{
	t_info *info;

	info = new_info();
	if (map(info))
	{
		print_file(info);
		operate(info, NULL, 0);
		do_the_rest(info);
	}
	else
		ERROR_EXIT;
	system("leaks -q lem-in");
	return (0);
}
