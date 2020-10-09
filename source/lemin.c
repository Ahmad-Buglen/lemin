/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:28:21 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/09 18:42:17 by dphyliss         ###   ########.fr       */
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
			temp[i] = node1->connections[i];////////!!!!!
		temp[node1->con_size] = node2;
		++node1->con_size;
		ft_memdel((void **)&node1->connections);
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

void connect_node(t_lem_in *lemin, t_room *room1, t_room *room2)
{
	// t_room *node1;
	// t_room *node2;

	// node1 = node_find(lemin, name1);
	// node2 = node_find(lemin, name2);

	if (!room1 || !room2)
	{
		//printf(" not found %s or %s", name1, name2);
		ft_exit_fail("Error 3");
	}
	connect_add(room1, room2);
	connect_add(room2, room1);
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
		printf("%s ", temp[i]->name);
		++i;
	}
	printf("}");
}

void print_rooms(t_room *nodes)
{
	t_room *temp;
			int i;

	temp = nodes;
	while (NULL != temp)
	{
		printf("%s [%d] (%d, %d) type - %d; con_size - %d, index - %d, weight - %d, ", 
			temp->name, temp->index, temp->coords.x, temp->coords.y, temp->type, temp->con_size, temp->index, temp->weight);
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
		temp = temp->next_a;
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

t_route **routes_copy(t_route **routes, int size)
{
	int i;
	t_route **copy;

	if (!(copy = (t_route **)ft_memalloc(sizeof(t_route *) * (size + 1))))
			ft_exit_fail("Error 17");
	i = -1;
	while (++i < size)
		copy[i] = route_copy(routes[i]);
	// copy[i] = NULL;

	return (copy);
}

void	routes_destroy(t_route **routes, int *route_count)
{
	int i;

	i = -1;
	while (NULL != routes[++i])
		ft_memdel((void**)&routes[i]);
	*route_count = 0;
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
	while (++i < lemin->num_of_rooms)
	{
		j = -1;
		while (++j < lemin->array_of_rooms[i]->con_size)
			if (!connection_include(lemin->array_of_rooms[i]->connections[j], lemin->array_of_rooms[i]))
				connection_restore(lemin->array_of_rooms[i]->connections[j], lemin->array_of_rooms[i]);
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
		connect_del(best_route->elem[i], best_route->elem[i + 1]);
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
//*


void route_clean(t_lem_in *lemin)
{
	int	i;

	i = 0;
	while (++i < lemin->num_of_rooms)
		lemin->route[i] = false;
}

void route_mark(t_lem_in *lemin, t_route *route)
{
	int	i;

	i = 0;
	while (++i < route->size - 1)
		lemin->route[route->elem[i]->index] = true;
}

t_bool route_check(t_lem_in *lemin, t_route *route)
{
	int	i;

	i = 0;
	while (++i < route->size - 1)
		if (lemin->route[route->elem[i]->index] == true)
			return (false);
	return (true);
}


//need write route free after dijkstra_search

int fifo_include(t_room **fifo_nodes, t_room *node)
{
	int i;

	i = -1;
	while (NULL != fifo_nodes[++i])
		if (fifo_nodes[i] == node)
			return (1);
	return (0);
}
	
void lemin_init(t_lem_in *lemin)
{
	t_route route;

	lemin->max_route_count = (lemin->start->con_size < lemin->end->con_size) ?
								lemin->start->con_size : lemin->end->con_size;
	// printf("here\n");
	if (!(lemin->fifo_nodes = (t_room **)ft_memalloc(sizeof(t_room *) * lemin->num_of_rooms)))  // node_len != 0 ?
		ft_exit_fail("Error 14");
	if (!(lemin->routes = (t_route **)ft_memalloc(sizeof(t_route *) * (lemin->max_route_count + 1))))
			ft_exit_fail("Error 11");
	if (!(lemin->route = (t_bool *)ft_memalloc(sizeof(t_bool) * (lemin->num_of_rooms + 1))))
			ft_exit_fail("Error 19");
	lemin->fifo_nodes[0] = lemin->start;
	ft_bzero(&route, sizeof(t_route));
	route.elem[route.size++] = lemin->fifo_nodes[0];
	lemin->fifo_nodes[0]->route = route_copy(&route);
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
	if (route_count > 0)
		flow = lemin->routes[lemin->route_count - 1]->size + ants / route_count;
	return (flow);
}

int	route_steps(t_lem_in *lemin)
{
	if (lemin->route_count > 1 &&
			route_flow(lemin, lemin->route_count) >=
				route_flow(lemin, lemin->route_count - 1))
		return (0);
	return (1);
}

void	dijkstra_setup(t_lem_in *lemin)
{
	int	i;
	// t_route route;

	i = 0;
	while (i < lemin->num_of_rooms)
	{
		lemin->array_of_rooms[i]->weight = BIG_INT;
		lemin->array_of_rooms[i]->pass = NO_VISIT;
		if (i != 0 && NULL != lemin->array_of_rooms[i]->route)
			ft_memdel((void **)&lemin->array_of_rooms[i]->route);
		++i;
	}
	ft_bzero(lemin->fifo_nodes + 1, sizeof(lemin->fifo_nodes) * (lemin->num_of_rooms - 1));
	lemin->start->weight = 0;
	// lemin->fifo_nodes[0] = lemin->start;
	// ft_bzero(&route, sizeof(t_route));
	// route.elem[route.size++] = lemin->fifo_nodes[0];
	// lemin->fifo_nodes[i]->route = route_copy(&route);
}

void	dijkstra_search( t_room **fifo_nodes, t_lem_in *lemin)
{
	int i;
	int j;
	int n;
	t_route *temp;

	n = 1;
	i = 0;
	while (n > i)
	{
		j = 0;
		while (fifo_nodes[i]->con_size > j)
		{
				if ((NO_VISIT == fifo_nodes[i]->connections[j]->pass) &&
						(fifo_nodes[i]->weight + 1 <= fifo_nodes[i]->connections[j]->weight))
				{
					fifo_nodes[i]->connections[j]->weight = fifo_nodes[i]->weight + 1;
					if (NULL != fifo_nodes[i]->connections[j]->route)
						ft_memdel((void **)&fifo_nodes[i]->connections[j]->route);
					temp = route_copy(fifo_nodes[i]->route);
					temp->elem[temp->size++] = fifo_nodes[i]->connections[j];
					fifo_nodes[i]->connections[j]->route = temp;
				}
				if (!fifo_include(fifo_nodes, fifo_nodes[i]->connections[j]))
					fifo_nodes[n++] = fifo_nodes[i]->connections[j];
			++j;
		}
		fifo_nodes[i]->pass = VISIT;
		++i;
	}
}

void bhandari_search(t_lem_in *lemin)
{
	while (lemin->route_count < lemin->max_route_count) // max_route_count ? 
	{
		dijkstra_setup(lemin);
		dijkstra_search( lemin->fifo_nodes, lemin);
		if (BIG_INT == lemin->end->weight || !route_steps(lemin))
			break;
		route_inverse(lemin->end->route);
		if (true == route_check(lemin, lemin->end->route))
		{
			route_mark(lemin, lemin->end->route);
			lemin->routes[lemin->route_count++] = route_copy(lemin->end->route);
		}
	}
	route_recovery(lemin);
}
//*/
int main(int argc, char **argv)
{
	t_room *nodes;
	int i;
	t_lem_in	lemin;
//*
	//lemin.vis_flag = (argc == 2 && ft_strequ("-v", argv[1])) ? 1 : 0;
	ft_bzero(&lemin, sizeof(lemin));
	init_values(&lemin);
	get_num_of_ants(&lemin);
	get_rooms(&lemin);
	if (!lemin.start_flag || !lemin.end_flag)
	 	close_program(&lemin, "no start or end room");		
	if (!(lemin.adjacency_matrix = init_adjacency_matrix(lemin.num_of_rooms)))
	 	close_program(&lemin, "init_adjacency_matrix error");
	lemin.array_of_rooms = init_array_of_rooms(&lemin);
	get_links(&lemin);
	if (!check_start_end_links(&lemin))
		close_program(&lemin, "start or/and end room is/are without links");
	if (!lemin.array_of_rooms[lemin.start_index] || !lemin.array_of_rooms[lemin.end_index])
		close_program(&lemin, "start or/and end room is/are without links");
	
	lemin_init(&lemin);
//*/
 	// printf("num of ants = %d\n", lemin.num_of_ants);
 	// print_room_list(lemin.room_list);
 	// print_hash_map(lemin.hash_map);
 	// print_array_of_rooms(&lemin);
 	// print_adjacency_matrix(&lemin);
	// print_ant_farm(&lemin);
 	// print_rooms(lemin.nodes);
//*
	// nodes = NULL;
	// init_middle(&lemin);

	t_route **prev;
	t_route **next;

	// ft_memcmp(const void *s1, const void *s2, size_t n);
	bhandari_search(&lemin);

	if (lemin.num_of_rooms < 1500)
	{
		next = routes_copy(lemin.routes, lemin.route_count);
		prev = NULL;
		while (0 != routes_compare(prev, next) )//&& ++i < CYCLE_SIZE) ? work?)
		{
			routes_destroy(lemin.routes, &lemin.route_count);
			route_clean(&lemin);
			bhandari_search(&lemin);
			if (NULL != prev)
			{
				routes_destroy(prev, &i);
				ft_memdel((void**)&prev);
			}
			prev = next;
			next = routes_copy(lemin.routes, lemin.route_count);
			// write(1, "1 \n", 2);
		}
		routes_destroy(prev, &i);
		ft_memdel((void**)&prev);
		routes_destroy(next, &i);
		ft_memdel((void**)&next);
	}
	//lemin.route_count = duplicate_exclusion(lemin.routes);

	// i = -1;
	// while (++i < lemin.route_count)
	// 	print_route(lemin.routes[i]);
		
//*/
	 
	// lemin_destroy(&lemin);

////////
////////	SOLUTION PRINT FUNCTIONS
////////
	init_path_array(&lemin);
	init_array_of_ants(&lemin);
	flow_distribution(&lemin);	//функция распределения потоков
	print_ant_farm(&lemin);		//вывод фермы
	print_solution(&lemin);		//вывод решения
////////
////////	
	// printf(" routes - %d, steps - %d\n", lemin.route_count, route_flow(&lemin, lemin.route_count));

	free_all(&lemin);
	// printf("\n %lu  ", sizeof(t_lem_in));
	return (1);
}
