#include "lem_in.h"

float	calc_efficiency(t_info *info, int id_n)//CHECK IF WE HAVE ADDITIONAL LEAKS HERE, THOUGH THERE SHOULD NOT BE ANY
{
	float eff;
	float ants_n;
	float paths_l_sum;
	float paths_n;
	t_path_list *temp_pl;

	ants_n = (float)info->ants_n;
	paths_l_sum = 0;
	paths_n = (float)id_n;

	temp_pl = info->paths_top;
	while (temp_pl && temp_pl->id <= id_n)
	{
		paths_l_sum += temp_pl->path_len;
		temp_pl = temp_pl->next;
	}
	//printf("len_sum is: %f; ", paths_l_sum);
	eff = (ants_n + paths_l_sum - 1) / paths_n;
	//printf("eff is: %f\n", eff);
	return (eff);
}

void	remove_ineff_paths(t_info *info, int id_n)
{
	int id_from;

	//id_from = id_n + 1;
	//printf("\n");
	// while (id_from <= info->paths_n)
	// {
	// 	remove_path_id(info, id_from);
	// 	printf("REMOVED PATH WITH ID: %i\n", id_from);
	// 	id_from++;
	// }

	id_from = info->paths_n;
	while (id_from > id_n)
	{
		remove_path_id(info, id_from);
		//printf("REMOVED PATH WITH ID: %i\n", id_from);
		id_from--;
	}
}

void	efficiency(t_info *info)
{
	float *effs;
	int n_eff_id;
	float max_eff;
	int i;


	i = 0;
	effs = (float*)malloc(sizeof(float) * info->paths_n);//FREE MEMORY HERE
	//printf("%i\n", info->paths_n);
	while (i < info->paths_n)
	{
		//printf("efficiency of %i paths\n", i + 1);
		effs[i] = calc_efficiency(info, i + 1);
		i++;
	}
	i = 0;
	n_eff_id = 0;
	max_eff = effs[0];
	while (i < info->paths_n)
	{
		if (max_eff > effs[i])
		{
			max_eff = effs[i];
			n_eff_id = i + 1;
		}
		i++;
	}
	//printf("\nOPTIMAL EFFICIENT N OF PATHS ID: up to %i\n", n_eff_id);
	//free array of effs!!!
	remove_ineff_paths(info, n_eff_id);
}