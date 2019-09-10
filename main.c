#include "lem_in.h"

void	print_one_dim(t_room *dat)//REMOVE THEN
{
	t_room *temp;

	temp = dat;
	while (temp)
	{
		printf("[%s]\n", temp->name);
		temp = temp->next;
	}
}

void	print_two_dim(t_room *dat)//REMOVE THEN
{
	t_room *temp;
	t_room *temp_aside;

	temp = dat;
	while (temp)
	{
		printf("[%s]\t", temp->name);
		temp_aside = temp->adj_top;
		while (temp_aside)
		{
			printf("{%s} \t", temp_aside->name);
			temp_aside = temp_aside->next;
		}
		printf("\n");
		temp = temp->next;
	}
}

void print_file(t_info *info)
{
	t_input *temp_inpt;

	temp_inpt = info->input_top;
	//printf("shitfuck\n");
	while (temp_inpt)
	{
		printf("%s\n", temp_inpt->str);
		temp_inpt = temp_inpt->next;
	}
	printf("\n");
	//and delete list with input after dat
}

int		main(void)
{
	t_info *info;

	info = new_info();
	if (map(info))
	{
		//print_two_dim(info->graph_top);
		print_file(info);
		operate(info);
		//printf("SUBSTITUTE\n");
	}
	else
		ERROR_EXIT;
	//system("leaks -q lem-in");
	return (0);
}