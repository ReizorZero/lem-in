#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct		s_can
{
	char			*name;
	struct s_can	*next;
	struct s_can	*aside;
}					t_can;

void	print_one_dim(t_can *dat)
{
	t_can *temp;

	temp = dat;
	while (temp)
	{
		printf("[%s]\n", temp->name);
		temp = temp->next;
	}
}

void	print_two_dim(t_can *dat)
{
	t_can *temp;
	t_can *temp_aside;

	temp = dat;
	while (temp)
	{
		printf("[%s]\n\t", temp->name);
		temp_aside = temp->aside;
		while (temp_aside)
		{
			printf("{%s} ", temp_aside->name);
			temp_aside = temp_aside->next;
		}
		printf("\n");
		temp = temp->next;
	}
}

void	delete_dat(t_can *dat, char *wat)
{
	t_can *temp_aside;

	printf("We will now delete: %s from %s\n", wat, dat->name);
	temp_aside = dat->aside;
	while (temp_aside)
	{
		if (!ft_strcmp(temp_aside->name, wat))
		{
			printf("FIRST ELEMENT NA DEREWYAH!\n");
			dat->aside = dat->aside->next;
		}
		else if (temp_aside->next && !ft_strcmp(temp_aside->next->name, wat))
		{
			printf("DJONNI %s NA DEREWYAH!\n", temp_aside->next->name);
			temp_aside->next = temp_aside->next->next;
		}
		temp_aside = temp_aside->next;
	}
}

t_can	*create_dat(char *name)
{
	t_can *dat;

	dat = (t_can*)malloc(sizeof(t_can));
	dat->name = ft_strdup(name);
	dat->next = NULL;
	dat->aside = NULL;
	return (dat);
}

void	performance(t_can *dat)
{
	t_can *temp;
	t_can *temp_aside;

	printf("\nThe performance starts now!\n");
	temp = dat;
	while (temp)
	{
		temp_aside = temp->aside;
		if (!ft_strcmp(temp->name, "4"))
		{
			printf("Found: 4\n");
			while (temp_aside)
			{
				if (!ft_strcmp(temp_aside->name, "3"))
				{
					printf("Found: 3\n");
					delete_dat(temp, temp_aside->name);
					break ;
				}
				temp_aside = temp_aside->next;
			}
		}
		//printf("[.]");
		temp = temp->next;
	}
	printf("\nThe performance ends now!\n");
	printf("\nThe result is:\n");
}

int		main(void)
{
	t_can	*weehaa;
	t_can	*temp;
	t_can	*temp_aside;
	int		i;
	int		j;

	weehaa = create_dat("0");
	i = 1;
	temp = weehaa;
	while (i < 9)
	{
		j = 0;
		temp->next = create_dat(ft_itoa(i));
		temp = temp->next;
		temp->aside = create_dat(ft_itoa(j));
		temp_aside = temp->aside;
		j++;
		while (j < i)
		{
			temp_aside->next = create_dat(ft_itoa(j));
			temp_aside = temp_aside->next;
			j++;
		}
		i++;
	}
	//print_one_dim(weehaa);
	print_two_dim(weehaa);
	performance(weehaa);
	print_two_dim(weehaa);
	return (0);
}
//gcc -Wall -Wextra -Werror trees_cool.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_itoa.c libft/ft_strcmp.c