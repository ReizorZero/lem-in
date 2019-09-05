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

int		main(void)
{
	t_info *info;

	info = new_info();
	if (map(info))
		operate(info);
	else
		ERROR_EXIT;
	//system("leaks -q lem-in");
	return (0);
}