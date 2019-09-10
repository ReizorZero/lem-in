#include "lem_in.h"

t_room		*new_room(char *name, int x, int y)
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	if (!room)
		return (NULL);
	room->name = ft_strdup(name);
	room->next = NULL;
	room->adj_room = NULL;
	room->c_from = NULL;
	room->adj_origin = NULL;
	room->is_empty = 1;
	room->x = x;
	room->y = y;
	return (room);
}

t_qlist		*new_qlist(t_room *room)
{
	t_qlist *qlist;

	qlist = (t_qlist*)malloc(sizeof(t_qlist));
	if (!qlist)
		return (NULL);
	qlist->actual = room;
	qlist->next = NULL;
	return (qlist);
}

t_path *new_path(t_room *room)
{
	t_path *path;

	path = (t_path*)malloc(sizeof(t_path));
	if (!path)
		return (NULL);
	path->actual = room;
	path->next = NULL;
	path->prev = NULL;
	//path->path_len = 0;
	path->head = NULL;
	return (path);
}

t_path_list *new_path_list(t_path *path)
{
	t_path_list *path_list;

	path_list = (t_path_list*)malloc(sizeof(t_path_list));
	if (!path_list)
		return (NULL);
	path_list->next = NULL;
	path_list->actual_path = path;
	return (path_list);
}

t_info *new_info(void)
{
	t_info *info;

	info = (t_info*)malloc(sizeof(t_info));
	if (!info)
		ERROR_EXIT;
	info->ants = 0;
	info->s_rooms = 0;
	info->e_rooms = 0;
	info->start = NULL;
	info->end = NULL;
	info->graph = NULL;
	info->graph_top = NULL;
	info->paths = NULL;
	info->paths_top = NULL;
	info->paths_n = 0;
	info->max_path_len = 0;
	info->sorry = 0;
	return (info);
}