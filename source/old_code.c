
// int node_length(t_room *nodes) //?
// {
// 	t_room *temp;

// 	temp = nodes;
// 	while (NULL != temp->next_a)
// 		temp = temp->next_a;
// 	return (temp->index_a + 1);
// }
// void map_free(t_map *map)
// {
// 	t_map *temp;
// 	t_map *buff;

// 	temp = map;
// 	while (NULL != temp)
// 	{
// 		buff = temp;
// 		temp = temp->next;
// 		free(buff);
// 		buff = NULL;
// 	}
// }

// t_room *node_type_find(t_lem_in *lemin, int type) // need rename in node_type_find
// {
// 	int	i;

// 	i = -1;
// 	while (++i < lemin->num_of_rooms)
// 		if (type == lemin->array_of_rooms[i]->type)
// 			return (lemin->array_of_rooms[i]);
// 	return (NULL);
// 	// t_room *temp;

// 	// temp = lemin->nodes;
// 	// while (NULL != temp)
// 	// {
// 	// 	if (start == temp->type)
// 	// 		return (temp);
// 	// 	temp = temp->next_a;
// 	// }
// 	// return (NULL);
// }



// void free_nodes(t_room *nodes)
// {
// 	t_room *temp;
// 	t_room *buff;

// 	temp = nodes;
// 	while (NULL != temp)
// 	{
// 		ft_strdel(&(temp->name));
// 		free(temp->connections);
// 		temp->connections = NULL;
// 		buff = temp;
// 		temp = temp->next_a;
// 		free(buff);
// 		buff = NULL;
// 	}
// }

// t_room *node_find(t_lem_in *lemin, char *name)
// {
// // 	t_room *temp;

// // 	temp = nodes;
// // 	while (NULL != temp)
// // 	{
// // 		if (0 == ft_strcmp(name, temp->name_a))
// // 			return (temp);
// // 		temp = temp->next_a;
// // 	}
// // 	return (NULL);
// 	int	i;

// 	i = -1;
// 	while (++i < lemin->num_of_rooms)
// 		if (0 == ft_strcmp(name, lemin->array_of_rooms[i]->name))
// 			return (lemin->array_of_rooms[i]);
// 	return (NULL);
// }


// void node_add(t_lem_in *lemin, char *name, t_coords coordinates, int type)
// {
// 	t_room *temp;
// 	t_room *buff;

// 	if (!(temp = (t_room *)ft_memalloc(sizeof(t_room))))
// 		ft_exit_fail("Error 1");
// 	if (!(temp->name = ft_strdup(name)))
// 		ft_exit_fail("Error 2");
// 	// temp->coordinates.x = coordinates.x;
// 	// temp->coordinates.y = coordinates.y;
// 	if (NULL == lemin->nodes)
// 	{
// 		lemin->nodes = temp;
// 		temp->index = lemin->node_len++;
// 		lemin->last_room = temp;
// 	}
// 	else
// 	{
// 		// buff = *lemin->nodes;
// 		// while (NULL != buff->next_a)
// 		// 	buff = buff->next_a;
// 		// buff = lemin->last_room;
// 		lemin->last_room->next_a = temp;
// 		temp->index = lemin->node_len++;
// 		lemin->last_room = temp;
// 	}
// 	temp->next_a = NULL;
// 	temp->type = type;
// }


// t_room **list_to_array(t_lem_in *lemin)
// {
// 	t_room	*temp;
// 	t_room	**map;
// 	int		i;

// 	if (NULL != lemin->nodes)
// 	{
// 		if (!(map = (t_room **)ft_memalloc(sizeof(t_room *) * (lemin->node_len + 1))))
// 			ft_exit_fail("Error 6");
// 		temp = lemin->nodes;
// 		i = 0;
// 		while (NULL != temp)
// 		{
// 			map[temp->index] = temp;
// 			temp = temp->next_a;
// 		}
// 		return (map);
// 	}
// 	return (NULL);
// }
/*

int duplicate_exclusion(t_route **routes)
{
	int i;
	int j;
	int n;

	i = -1;
	while (NULL != routes[++i])
	{
		j = i;
		while (NULL != routes[++j])
		{
			n = 0;
			while (++n < routes[j]->size - 1)
				if (node_include(routes[i], routes[j]->elem[n]->index))
				{
					n = routes[i]->size >= routes[j]->size ? i : j;
					ft_memdel((void **)&routes[n]);
					while (NULL != routes[n + 1])
					{
						routes[n] = routes[n + 1];
						++n;
					}
					routes[n] = NULL;
					if (i != 0)
						--i;
					if (j != 1)	
						--j;
					break;
				}
		}
	}
	return (i);
}
*/