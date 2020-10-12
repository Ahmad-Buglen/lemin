
/*
	node_len = node_length(nodes);
	start = start_find(&nodes, START_A);
	if (!(best_route = (t_route *)ft_memalloc(sizeof(t_route))))
			ft_exit_fail("Error 9");
	ft_bzero(best_route, sizeof(t_route));
	temp = 0;
	counter = -1;
	status = STANDART;
	routes = NULL;
	if (!(route = (t_route *)ft_memalloc(sizeof(t_route))))
			ft_exit_fail("Error 12");
	// ft_bzero(route, sizeof(t_route));

	while (counter != temp)
	{
		counter = 0;
		recur_route(route_copy(route), start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);
		
		temp = counter;
		while (1)
		{
			counter = 0;
			ft_bzero(best_route, sizeof(t_route));
			recur_route(route_copy(route), start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);

			if (0 == best_route->size)
				break;
			// print_route(best_route);
			route_inverse(&best_route);
		}
//  write(1, "here2\n", 6);
		// print_nodes(&nodes);
		route_recovery(nodes);
		counter = 0;
		recur_route(route_copy(route), start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);
	}

	if (!(routes = (t_route **)ft_memalloc(sizeof(t_route *) * (counter + 1))))
			ft_exit_fail("Error 11");
	

	status = END_A;
	// printf("%d Finish! \n", counter);
	counter = 0;
	recur_route(route_copy(route), start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);
	routes[counter] = NULL;
	if (counter > 2)
	{
	// printf(" duplicate_exclusion! \n");
		duplicate_exclusion(routes);
	}
// write(1, "here\n", 5);
	i = -1;
	while (NULL != routes[++i])
	{
		print_route(routes[i]);
		free(routes[i]);
		routes[i] = NULL;
	}
	free(routes);
	routes = NULL;
	printf("\n%d", i);
//*/	
/*

recur_route(route_copy(route), start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);
		


int *dublicate_map(t_node *nodes, int node_len)
{
	t_node	*temp;
	int	*map;
	int i;

	if (NULL != nodes)
	{
		if (!(map = (int *)ft_memalloc(sizeof(int) * node_len)))
			ft_exit_fail("Error 6");
		temp = nodes;
		i = 0;
		while (NULL != temp)
		{
			map[temp->index] = temp->pass;
			temp = temp->next;
		}
		return (map);
	}
	return (NULL);
}

int *dublicate_map2(int *map_src, int node_len)
{
	int		*map_dest;
	int		 i;

	if (0 != node_len)
	{
		if (!(map_dest = (int *)ft_memalloc(sizeof(int) * node_len)))
			ft_exit_fail("Error 7");
		i = -1;

		ft_memcpy((void *) map_dest, (void *) map_src, sizeof(int) * node_len);
		// while (++i < node_len)
		// 	map_dest[i] = map_src[i];
		return (map_dest);
	}
	return (NULL);
}

void recur_route(t_route * route, t_node *node, int *map, int node_len, t_route **best_route, int *counter, int status, t_route **routes)
{
	int i;
	// int sides;
	
	route->elem[route->size++] = node;
	// if (route->size > 100)
	// 	return;
	// printf("%s \n", node->name);
	if (END_A == node->type)
	{
		printf("%d\n", *counter);
		// printf("%d \nSucсess! ", *counter);
		print_route(route);
		if (END_A == status)
			routes[(*counter)] = route_copy(route);

		++(*counter);
		if (((*best_route)->size == 0) || (route->size < (*best_route)->size))
		{
			free(*best_route);
			*best_route = route_copy(route);
		}
		free(route);
		if (0 < node_len)
			free(map);
		return ;
	}
	// sides = 0;
	i = 0;
	// while (i < node->con_size)
	// {
	// 	if (NO_VISIT == map[node->connections[i]->index])
	// 		++sides;
	// 	++i;
	// }
	// if (sides <= 1)
	// {
	// 	map[node->index] = VISIT;
	// 	i = -1;
	// 	while (++i < node->con_size)
	// 		if (NO_VISIT == map[node->connections[i]->index] && !node_include(route, node->connections[i]->index))
	// 		{
	// 			recur_route(route_copy(route), node->connections[i], map, node_len, best_route, counter, status, routes);
	// 			break ;
	// 		}
	// }
	// else
	// {
		i = -1;
		while (++i < node->con_size)
			if (NO_VISIT == map[node->connections[i]->index] && !node_include(route, node->connections[i]->index) && (route->size < 17))
				recur_route(route_copy(route), node->connections[i], dublicate_map2(map, node_len), node_len, best_route, counter, status, routes);
		map[node->index] = VISIT;
	// }
	//  write(1, "here2\n", 6);
	// printf(" Fail( ");
	// print_route(&route);
	free(route);
	if (0 < node_len)
		free(map);
	return ;
}
*/