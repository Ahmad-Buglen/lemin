/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:28:21 by dphyliss          #+#    #+#             */
/*   Updated: 2020/09/28 18:57:06 by dphyliss         ###   ########.fr       */
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


void node_add(t_lem_in *lemin, char *name, t_coords coordinates, int type)
{
	t_room *temp;
	t_room *buff;

	if (!(temp = (t_room *)ft_memalloc(sizeof(t_room))))
		ft_exit_fail("Error 1");
	if (!(temp->name_a = ft_strdup(name)))
		ft_exit_fail("Error 2");
	temp->coordinates.x = coordinates.x;
	temp->coordinates.y = coordinates.y;
	if (NULL == lemin->nodes)
	{
		lemin->nodes = temp;
		temp->index_a = lemin->node_len++;
		lemin->last_room = temp;
	}
	else
	{
		// buff = *lemin->nodes;
		// while (NULL != buff->next_a)
		// 	buff = buff->next_a;
		// buff = lemin->last_room;
		lemin->last_room->next_a = temp;
		temp->index_a = lemin->node_len++;
		lemin->last_room = temp;
	}
	temp->next_a = NULL;
	temp->type = type;
}

t_room *node_find(t_lem_in *lemin, char *name)
{
// 	t_room *temp;

// 	temp = nodes;
// 	while (NULL != temp)
// 	{
// 		if (0 == ft_strcmp(name, temp->name_a))
// 			return (temp);
// 		temp = temp->next_a;
// 	}
// 	return (NULL);
	int	i;

	i = -1;
	while (++i < lemin->node_len)
		if (0 == ft_strcmp(name, lemin->map[i]->name_a))
			return (lemin->map[i]);
	return (NULL);
}

void connect_add(t_room *node1, t_room *node2)
{
	t_room **temp;
	int i;

	if (0 == node1->con_size)
	{
		if (!(node1->connections = (t_room **)ft_memalloc(sizeof(t_room *) * 2)))
			ft_exit_fail("Error 4");
		node1->connections[0] = node2;
		node1->con_size = 1;
	}
	else
	{
		if (!(temp = (t_room **)ft_memalloc(sizeof(t_room *) * (node1->con_size + 2))))
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

void connect_del(t_room *node1, t_room *node2)
{
	// t_room *node1;
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

void connect_node(t_lem_in *lemin, char *name1, char *name2)
{
	t_room *node1;
	t_room *node2;

	node1 = node_find(lemin, name1);
	node2 = node_find(lemin, name2);

	if (!node1 || !node2)
	{
		printf(" not found %s or %s", name1, name2);
		ft_exit_fail("Error 3");
	}
	connect_add(node1, node2);
	connect_add(node2, node1);
}

void print_connections(t_room **connections, int con_size)
{
	t_room **temp;
	int i;

	temp = connections;
	i = 0;
	printf("{");
	while (i < con_size)
	{
		printf("%s ", temp[i]->name_a);
		++i;
	}
	printf("}");
}

void free_nodes(t_room *nodes)
{
	t_room *temp;
	t_room *buff;

	temp = nodes;
	while (NULL != temp)
	{
		ft_strdel(&(temp->name_a));
		free(temp->connections);
		temp->connections = NULL;
		buff = temp;
		temp = temp->next_a;
		free(buff);
		buff = NULL;
	}
}

void print_rooms(t_room *nodes)
{
	t_room *temp;
			int i;

	temp = nodes;
	while (NULL != temp)
	{
		printf("%s [%d] (%d, %d) type - %d; con_size - %d, index_a - %d, weight - %d, ", 
			temp->name_a, temp->index_a, temp->coordinates.x, temp->coordinates.y, temp->type, temp->con_size, temp->index_a, temp->weight);
		if (0 != temp->con_size)
		{
			i = 0;
			printf("{");
			while (i < temp->con_size)
			{
				printf("%s ", temp->connections[i]->name_a);
				++i;
			}
			printf("}");
			// print_connections(temp->connections, temp->con_size);
		}
		printf("\n");
		temp = temp->next_a;
	}
}

void print_route(t_route *route)
{
	int i;

	i = -1;
	while (++i < route->size)
		printf("%s ", route->elem[i]->name_a);
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

t_route **routes_copy(t_route **routes, int size)
{
	int i;
	t_route **copy;

	if (!(copy = (t_route **)ft_memalloc(sizeof(t_route *) * (size + 1))))
			ft_exit_fail("Error 17");
	i = -1;
	while (++i < size)
		copy[i] = route_copy(routes[i]);
	copy[i] = NULL;

	return (copy);
}


void	routes_destroy(t_route **routes, int count)
{
	int i;

	i = -1;
	while (++i < count)
	{
		free(routes[i]);
		routes[i] = NULL;
	}
	free(routes);
	routes = NULL;
}


int route_compare(t_route *route_one, t_route *route_two)
{
	int i;

	if (route_one->size != route_two->size)
		return (1);
	// if (0 != ft_memcmp((void *)route_one->elem, (void *) route_two->elem,
	// 				sizeof(route_two->elem) * ROUTE_SIZE))
		// return (1);
	i = 0;
	while (i < route_two->size)
	{
		if (route_one->elem[i] != route_two->elem[i])
			return (1);
		++i;
	}
	return (0);
}

int routes_compare(t_route **prev, t_route **next)
{
	int i;

	i = 0;
	if (NULL == prev || NULL == next)
		return (1);
	while (NULL != prev[i] && NULL != next[i])
	{
		//ft_memcmp((void *) prev[i], (void *) next[i], sizeof(t_route)))
		if (route_compare(prev[i], next[i]))
			return (1);
		++i;
	}
	if (NULL != prev[i] && NULL != next[i])
		return (1);
	return (0);
}

t_room *node_type_find(t_lem_in *lemin, int type) // need rename in node_type_find
{
	int	i;

	i = -1;
	while (++i < lemin->node_len)
		if (type == lemin->map[i]->type)
			return (lemin->map[i]);
	return (NULL);
	// t_room *temp;

	// temp = lemin->nodes;
	// while (NULL != temp)
	// {
	// 	if (start == temp->type)
	// 		return (temp);
	// 	temp = temp->next_a;
	// }
	// return (NULL);
}

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

int node_include(t_route *route, int index)
{
	// t_map *temp;
	int i;

	i = 0;
	while (i < route->size)
	{
		if (index == route->elem[i]->index_a)
			return (1);
		++i;
	}
	return (0);
}

// int node_length(t_room *nodes) //?
// {
// 	t_room *temp;

// 	temp = nodes;
// 	while (NULL != temp->next_a)
// 		temp = temp->next_a;
// 	return (temp->index_a + 1);
// }

int		connection_include(t_room *node1, t_room *node2)
{
	int i;

	i = -1;
	while (++i < node1->con_size)
		if (node1->connections[i] == node2)
			return (1);
	return (0); 
}

void	connection_restore(t_room *node1, t_room *node2)
{
	node1->connections[(node1->con_size)++] = node2; 
}

void	route_recovery(t_lem_in *lemin)
{
	int	i;
	int	j;

	i = -1;
	while (++i < lemin->node_len)
	{
		j = -1;
		while (++j < lemin->map[i]->con_size)
			if (!connection_include(lemin->map[i]->connections[j], lemin->map[i]))
				connection_restore(lemin->map[i]->connections[j], lemin->map[i]);
	}
	// t_room *temp;
	// int i;

	// temp = nodes;
	// while (NULL != temp)
	// {
	// 	i = -1;
	// 	while (++i < temp->con_size)
	// 		if (!connection_include(temp->connections[i], temp))
	// 			connection_restore(temp->connections[i], temp);
	// 	temp = temp->next_a;
	// }
}

void	route_inverse(t_route *best_route)
{
	int i;

	i = -1;
	while (++i < (best_route->size - 1))
	{
		connect_del(best_route->elem[i], best_route->elem[i + 1]);
	}
}

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
				if (node_include(routes[i], routes[j]->elem[n]->index_a))
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
	return (i);
}
//*
void	dijkstra_weight(t_lem_in *lemin)
{
	// t_room *temp;
	int	i;

	i = -1;
	// temp = *nodes;
	while (++i < lemin->node_len)
		lemin->map[i]->weight = BIG_INT;
	// while (NULL != temp)
	// {
	// 	temp->weight = BIG_INT;
	// 	temp = temp->next_a;
	// }
}

t_room **list_to_array(t_lem_in *lemin)
{
	t_room	*temp;
	t_room	**map;
	int		i;

	if (NULL != lemin->nodes)
	{
		if (!(map = (t_room **)ft_memalloc(sizeof(t_room *) * (lemin->node_len + 1))))
			ft_exit_fail("Error 6");
		temp = lemin->nodes;
		i = 0;
		while (NULL != temp)
		{
			map[temp->index_a] = temp;
			temp = temp->next_a;
		}
		return (map);
	}
	return (NULL);
}

void route_mark(t_lem_in *lemin, t_route *route)
{
	int	i;

	i = 0;
	while (++i < route->size - 1)
		lemin->route[route->elem[i]->index_a] = true;
}

t_bool route_check(t_lem_in *lemin, t_route *route)
{
	int	i;

	i = 0;
	while (++i < route->size - 1)
		if (lemin->route[route->elem[i]->index_a] == true)
			return (false);
	return (true);
}


void	nodes_pass(t_lem_in *lemin)
{
	int	i;

	i = -1;
	while (++i < lemin->node_len)
	{
		lemin->map[i]->pass = NO_VISIT;
		if ((NULL != lemin->map[i]->route) && (lemin->map[i]->type != START_A))
		{
			free(lemin->map[i]->route);
			lemin->map[i]->route = NULL;
		}
	}
}
//need write route free after dijkstra_search

int fifo_include(t_room **fifo_nodes, t_room * node)
{
	int i;

	i = -1;
	while (NULL != fifo_nodes[++i])
		if (fifo_nodes[i] == node)
			return (1);
	return (0);
}

	
void	dijkstra_search(t_route *route, t_room **fifo_nodes, t_lem_in *lemin)
{
	int i;
	int j;
	int n;
	int sides;
	t_route *temp;
	// printf("%s \n", node->name_a);
	
	n = 1;
	i = 0;
	route->elem[route->size++] = fifo_nodes[i];
	fifo_nodes[i]->route = route;
	while (n > i)
	{
		j = 0;
		while (fifo_nodes[i]->con_size > j)
		{
			// if (NO_VISIT == fifo_nodes[i]->connections[j]->pass)
			// {
				if ((NO_VISIT == fifo_nodes[i]->connections[j]->pass) &&
						// lemin->route[fifo_nodes[i]->connections[j]->index_a] == false &&
						(fifo_nodes[i]->weight + 1 <= fifo_nodes[i]->connections[j]->weight))
				{
					fifo_nodes[i]->connections[j]->weight = fifo_nodes[i]->weight + 1;
					if (NULL != fifo_nodes[i]->connections[j]->route)
					{
						free(fifo_nodes[i]->connections[j]->route);
						fifo_nodes[i]->connections[j]->route = NULL;
					}
					temp = route_copy(fifo_nodes[i]->route);
					temp->elem[temp->size++] = fifo_nodes[i]->connections[j];
					fifo_nodes[i]->connections[j]->route = temp;
				}
				if (!fifo_include(fifo_nodes, fifo_nodes[i]->connections[j]))
					fifo_nodes[n++] = fifo_nodes[i]->connections[j];
			// }
			++j;
		}
		fifo_nodes[i]->pass = VISIT;
		++i;
	}
}

void lemin_init(t_lem_in *lemin)
{
	// t_lemin *lemin;

	// if (!(lemin = (t_lemin *)ft_memalloc(sizeof(t_lemin))))
	// 		ft_exit_fail("Error 16");
	// lemin->nodes = nodes;
	// lemin->node_len = node_length(*nodes); // ?
	lemin->start = node_type_find(lemin, START_A);
	lemin->end = node_type_find(lemin, END_A);
	lemin->max_route_count = (lemin->start->con_size < lemin->end->con_size) ?
								lemin->start->con_size : lemin->end->con_size;
	if (!(lemin->fifo_nodes = (t_room **)ft_memalloc(sizeof(t_room *) * lemin->node_len)))  // node_len != 0 ?
		ft_exit_fail("Error 14");
	if (!(lemin->routes = (t_route **)ft_memalloc(sizeof(t_route *) * (lemin->max_route_count + 1))))
			ft_exit_fail("Error 11");
	if (!(lemin->route = (t_bool *)ft_memalloc(sizeof(t_bool) * (lemin->node_len + 1))))
			ft_exit_fail("Error 19");
	// return (lemin);
}

void lemin_destroy(t_lem_in *lemin)
{
	free(lemin->fifo_nodes);
	lemin->fifo_nodes = NULL;
	routes_destroy(lemin->routes, lemin->route_count);
	free(lemin->map);
	lemin->map = NULL;
	free(lemin);
	lemin = NULL;
}

int	route_flow(t_lem_in *lemin, int route_count)
{
	int i;
	int flow;
	int ants;

	ants = lemin->num_of_ants;
	flow = 0;
	i = -1;
	while (++i < route_count - 1)
		ants -= lemin->routes[lemin->route_count - 1]->size - lemin->routes[i]->size;
	flow = lemin->routes[lemin->route_count - 1]->size + ants / route_count;
	return (flow);
}

int	route_steps(t_lem_in *lemin)
{
	if (lemin->route_count > 1 && route_flow(lemin, lemin->route_count) >= route_flow(lemin, lemin->route_count - 1))
		return (0);
	return (1);
}

void bhandari_search(t_lem_in *lemin)
{
	t_route *route;

	if (!(route = (t_route *)ft_memalloc(sizeof(t_route))))
			ft_exit_fail("Error 13"); // free?
	lemin->route_count = 0;
	while (lemin->route_count < lemin->max_route_count) // max_route_count ? 
	{
		dijkstra_weight(lemin);
		lemin->start->weight = 0;
		lemin->fifo_nodes[0] = lemin->start;
		dijkstra_search(route, lemin->fifo_nodes, lemin);
		// print_rooms(&nodes);
		if (BIG_INT == lemin->end->weight || !route_steps(lemin))
			break;
		// if (true == route_check(lemin, lemin->end->route))
		// {
			route_inverse(lemin->end->route);
			route_mark(lemin, lemin->end->route);
			lemin->routes[lemin->route_count++] = route_copy(lemin->end->route);
		// }
		ft_bzero(lemin->fifo_nodes, sizeof(lemin->fifo_nodes) * lemin->node_len);
		ft_bzero(route, sizeof(route));
		nodes_pass(lemin);
	}
	route_recovery(lemin);
}
//*/
int main(int argc, char **argv)
{
	t_room *nodes;
	int i;
	nodes = NULL;
	// t_lemin *lemin_a;
	t_lem_in	lemin;
//*
	lemin.vis_flag = (argc == 2 && ft_strequ("-v", argv[1])) ? 1 : 0;
	ft_bzero(&lemin, sizeof(lemin));
	init_values(&lemin);
	lemin.nodes = nodes;
	get_num_of_ants(&lemin);
	get_rooms(&lemin);

	lemin.map = list_to_array(&lemin);
	if (!lemin.start_flag || !lemin.end_flag)
	 	close_program(&lemin, "no start or end room");		
	if (!(lemin.adjacency_matrix = init_adjacency_matrix(lemin.num_of_rooms)))
	 	close_program(&lemin, "init_adjacency_matrix error");
	lemin.array_of_rooms = init_array_of_rooms(&lemin);

	get_links(&lemin);

	if (!lemin.array_of_rooms[lemin.start_index] || !lemin.array_of_rooms[lemin.end_index])
		close_program(&lemin, "start or/and end room is/are without links");
		
	lemin_init(&lemin);
//*/
 	// printf("num of ants = %d\n", lemin.num_of_ants);
 	// print_room_list(lemin.room_list);
 	// print_hash_map(lemin.hash_map);
 	// print_array_of_rooms(&lemin);
 	// print_adjacency_matrix(&lemin);

 	// print_rooms(lemin.nodes);

//*
	// nodes = NULL;
	// init_middle(&lemin);

	// i = -1;
	t_route **prev;
	t_route **next;

//  print_rooms(lemin.nodes);
	// ft_memcmp(const void *s1, const void *s2, size_t n);

	bhandari_search(&lemin);
	if (lemin.node_len < 1500)
	{
		next = routes_copy(lemin.routes, lemin.route_count);
		prev = NULL;
		i = -1;
		while (0 != routes_compare(prev, next) )//&& ++i < CYCLE_SIZE)
		{
			bhandari_search(&lemin);
			prev = next;
			next = routes_copy(lemin.routes, lemin.route_count);
		}
	}
	// lemin.route_count = duplicate_exclusion(lemin.routes);

	i = -1;
	while (++i < lemin.route_count)
	{
		print_route(lemin.routes[i]);
		// free(lemin.routes[i]);
		// lemin.routes[i] = NULL;
	}
	
 	// print_rooms(&nodes);
	printf(" routes - %d, steps - %d\n", lemin.route_count, route_flow(&lemin, lemin.route_count));
//*/
 	// print_rooms(&nodes);
	 
	// lemin_destroy(&lemin);
	free_nodes(nodes);
	return (1);
}
