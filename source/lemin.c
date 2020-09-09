/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:28:21 by dphyliss          #+#    #+#             */
/*   Updated: 2020/09/09 19:57:48 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/lemin.h"

#include <stdio.h>

#include <limits.h>

long			ft_strtol(const char *str, char **end)
{
	int						i;
	int						sign;
	unsigned long long		result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_is_space(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = str[i++] == '-' ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = result * 10 + (str[i++] - '0');
		if (sign > 0 && result >= (unsigned long long)LONG_MAX)
			return (LONG_MAX);
		if (sign < 0 && result >= (unsigned long long)LONG_MAX + 1)
			return (LONG_MIN);
	}
	if (end)
		*end = (char*)&str[i];
	return (result * sign);
}


void node_add(t_node **nodes, char *name, t_coords coordinates, int type)
{
	t_node *temp;
	t_node *buff;

	if (!(temp = (t_node *)ft_memalloc(sizeof(t_node))))
		ft_exit_fail("Error 1");
	if (!(temp->name = ft_strdup(name)))
		ft_exit_fail("Error 2");
	temp->coordinates.x = coordinates.x;
	temp->coordinates.y = coordinates.y;
	if (NULL == *nodes)
	{
		*nodes = temp;
		temp->index = 0;
	}
	else
	{
		buff = *nodes;
		while (NULL != buff->next)
			buff = buff->next;
		buff->next = temp;
		temp->index = buff->index + 1;
	}
	temp->next = NULL;
	temp->type = type;
}

t_node *node_find(t_node **nodes, char *name)
{
	t_node *temp;

	temp = *nodes;
	while (NULL != temp)
	{
		if (0 == ft_strcmp(name, temp->name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void connect_add(t_node *node1, t_node *node2)
{
	t_node **temp;
	int i;

	if (0 == node1->con_size)
	{
		if (!(node1->connections = (t_node **)ft_memalloc(sizeof(t_node *) * 2)))
			ft_exit_fail("Error 4");
		node1->connections[0] = node2;
		node1->con_size = 1;
	}
	else
	{
		if (!(temp = (t_node **)ft_memalloc(sizeof(t_node *) * (node1->con_size + 2))))
			ft_exit_fail("Error 5");
		// ft_memcpy(temp, node1->connections, sizeof(node1->connections));
		i = -1;
		while (++i < node1->con_size)
			temp[i] = node1->connections[i];
		temp[node1->con_size] = node2;
		++node1->con_size;
		free(node1->connections);
		node1->connections = temp;
	}
	node1->connections[node1->con_size] = NULL;
}

void connect_del(t_node *node1, t_node *node2)
{
	// t_node *node1;
	int i;

	// node1 = node_find(nodes, name1);
	i = -1;
	while (++i < node1->con_size)
		if (node1->connections[i] == node2)
			break;
	if (i == (node1->con_size - 1))
		node1->connections[--(node1->con_size)] = NULL;
	else
	{
		while (i < node1->con_size)
		{
			node1->connections[i] = node1->connections[i + 1];
			i++;
		}
		--(node1->con_size);
		/* code */
	}

	// node1->connections[node1->con_size] = NULL;
}

void connect_node(t_node **nodes, char *name1, char *name2)
{
	t_node *node1;
	t_node *node2;

	node1 = node_find(nodes, name1);
	node2 = node_find(nodes, name2);

	if (!node1 || !node2)
	{
		printf(" not found %s or %s", name1, name2);
		ft_exit_fail("Error 3");
	}
	connect_add(node1, node2);
	connect_add(node2, node1);
}

void print_connections(t_node **connections, int con_size)
{
	t_node **temp;
	int i;

	temp = connections;
	i = 0;
	printf("{");
	while (i < con_size)
	{
		printf("%s ", temp[i]->name);
		++i;
	}
	printf("}");
}

void free_nodes(t_node **nodes)
{
	t_node *temp;
	t_node *buff;

	temp = *nodes;
	while (NULL != temp)
	{
		ft_strdel(&(temp->name));
		free(temp->connections);
		temp->connections = NULL;
		buff = temp;
		temp = temp->next;
		free(buff);
		buff = NULL;
	}
}

void print_nodes(t_node **nodes)
{
	t_node *temp;
			int i;

	temp = *nodes;
	while (NULL != temp)
	{
		printf("%s [%d] (%d, %d) type - %d; con_size - %d, index - %d, weight - %d, ", 
			temp->name, temp->index, temp->coordinates.x, temp->coordinates.y, temp->type, temp->con_size, temp->index, temp->weight);
		if (0 != temp->con_size)
		{
			i = 0;
			printf("{");
			while (i < temp->con_size)
			{
				printf("%s ", temp->connections[i]->name);
				++i;
			}
			printf("}");
			// print_connections(temp->connections, temp->con_size);
		}
		printf("\n");
		temp = temp->next;
	}
}

void print_route(t_route *route)
{
	int i;

	i = -1;
	while (++i < route->size)
		printf("%s ", route->elem[i]->name);
	printf(" size - %d;\n", route->size);
}

t_route *route_copy(t_route *route)
{
	t_route *copy;

	if (!(copy = (t_route *)ft_memalloc(sizeof(t_route))))
			ft_exit_fail("Error 10");
		
	ft_memcpy((void *) copy, (void *) route, sizeof(t_route));
	// copy->size = route->size;
	return (copy);
}

t_node *start_find(t_node **nodes, int start) // need rename in node_type_find
{
	t_node *temp;

	temp = *nodes;
	while (NULL != temp)
	{
		if (start == temp->type)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void map_free(t_map *map)
{
	t_map *temp;
	t_map *buff;

	temp = map;
	while (NULL != temp)
	{
		buff = temp;
		temp = temp->next;
		free(buff);
		buff = NULL;
	}
}

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

int node_include(t_route *route, int index)
{
	// t_map *temp;
	int i;

	i = 0;
	while (i < route->size)
	{
		if (index == route->elem[i]->index)
			return (1);
		++i;
	}
	return (0);
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

int node_length(t_node *nodes)
{
	t_node *temp;

	temp = nodes;
	while (NULL != temp->next)
		temp = temp->next;
	return (temp->index + 1);
}

int		connection_include(t_node *node1, t_node *node2)
{
	int i;

	i = -1;
	while (++i < node1->con_size)
		if (node1->connections[i] == node2)
			return (1);
	return (0); 
}

void	connection_restore(t_node *node1, t_node *node2)
{
	node1->connections[(node1->con_size)++] = node2; 
}

void	route_recovery(t_node *nodes)
{
	t_node *temp;
	int i;

	temp = nodes;
	while (NULL != temp)
	{
		i = -1;
		while (++i < temp->con_size)
			if (!connection_include(temp->connections[i], temp))
				connection_restore(temp->connections[i], temp);
		temp = temp->next;
	}
}

void	route_inverse(t_route **best_route)
{
	int i;

	i = -1;
	while (++i < ((*best_route)->size - 1))
	{
		connect_del((*best_route)->elem[i], (*best_route)->elem[i + 1]);
	}
}

void duplicate_exclusion(t_route **routes)
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
					free(routes[n]);
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
}
//*
void	dijkstra_weight(t_node **nodes)
{
	t_node *temp;

	temp = *nodes;
	while (NULL != temp)
	{
		temp->weight = MAX_INT;
		temp = temp->next;
	}
}

//need write route free after dijkstra_search


void	dijkstra_search(t_route *route, t_node *node, int *map, int node_len)
{
	int i;
	int sides;
	t_route *temp;
	route->elem[route->size++] = node;
	// printf("%s \n", node->name);
	
	i = 0;
	while (i < node->con_size)
	{
		if (NO_VISIT == map[node->connections[i]->index])
		{
			if (node->weight + 1 < node->connections[i]->weight)
			{
				node->connections[i]->weight = node->weight + 1;
				if (NULL != node->connections[i]->route)
				{
					free(node->connections[i]->route);
					node->connections[i]->route = NULL;
				}
				temp = route_copy(route);
				temp->elem[temp->size++] = node->connections[i];
				node->connections[i]->route = temp;
			}
		}
		++i;
	}
	i = 0;
	while (i < node->con_size)
	{
		if (NO_VISIT == map[node->connections[i]->index] && !node_include(route, node->connections[i]->index) ) // maybe ? && (route->size < 100)
			dijkstra_search(route_copy(route), node->connections[i], dublicate_map2(map, node_len), node_len);
		++i;
	}
	node->pass = VISIT;
	free(route);
	route = NULL;
	if (0 < node_len) //<
		free(map);
}
//*/
int main(int argc, char **argv)
{
	t_node *nodes;
	t_node *start;
	t_node *end;
	t_route *route;
	t_route *best_route;
	t_route **routes;
	t_node *buff;
	int node_len;
	int counter;
	int temp;
	int status;
	int i;
	nodes = NULL;
	t_lem_in	lemin;
//*
	lemin.vis_flag = (argc == 2 && ft_strequ("-v", argv[1])) ? 1 : 0;
	init_values(&lemin);
	get_num_of_ants(&lemin);
	get_rooms(&lemin, &nodes);
	if (!lemin.start_flag || !lemin.end_flag)
	 	close_program(&lemin, "no start or end room");		
	if (!(lemin.adjacency_matrix = init_adjacency_matrix(lemin.num_of_rooms)))
	 	close_program(&lemin, "init_adjacency_matrix error");
	lemin.array_of_rooms = init_array_of_rooms(&lemin);
	get_links(&lemin, &nodes);
	if (!lemin.array_of_rooms[lemin.start_index] || !lemin.array_of_rooms[lemin.end_index])
		close_program(&lemin, "start or/and end room is/are without links");
//*/
 	// printf("num of ants = %d\n", lemin.num_of_ants);
 	// print_room_list(lemin.room_list);
 	// print_hash_map(lemin.hash_map);
 	// print_array_of_rooms(&lemin);
 	// print_adjacency_matrix(&lemin);

 	print_nodes(&nodes);

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

//*
	// nodes = NULL;
	// init_middle(&nodes);
	dijkstra_weight(&nodes);
	node_len = node_length(nodes);
	buff = start_find(&nodes, START);
	buff->weight = 0;
	if (!(route = (t_route *)ft_memalloc(sizeof(t_route))))
			ft_exit_fail("Error 13");
	dijkstra_search(route, buff, dublicate_map(nodes, node_len), node_len);
	buff = start_find(&nodes, END);
	print_route(buff->route);
	printf("\n %d", buff->route->size);
//*/

 	// print_nodes(&nodes);
	free_nodes(&nodes);
	return (1);
}
