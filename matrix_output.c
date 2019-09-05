#include <stdio.h>
#include <stdlib.h>

void	print_ordinary(int **arr)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 5)
		{
			printf("%i\t", arr[j][i]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int		main(void)
{
	int **arr;
	int i;
	int j;
	int k;

	i = 0;
	arr = (int**)malloc(sizeof(int*) * 5);
	while (i < 5)
	{
		arr[i] = (int*)malloc(sizeof(int) * 4);
		i++;
	}
	i = 0;
	k = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 4)
		{
			arr[i][j] = k;
			j++;
			k++;
		}
		i++;
	}
	print_ordinary(arr);
	return (0);
}