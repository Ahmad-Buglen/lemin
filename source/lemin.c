/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:28:21 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/16 18:21:53 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lemin.h"
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
	int i;
 
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
	if (!room1 || !room2)
		ft_exit_fail("Error 3");
	connect_add(room1, room2);
	connect_add(room2, room1);
}

t_route *route_copy(t_route *route)
{
	t_route *copy;

	if (!(copy = (t_route *)ft_memalloc(sizeof(t_route))))
			ft_exit_fail("Error 10");
	ft_memcpy((void *) copy, (void *) route, sizeof(t_route));
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
	return (copy);
}

void	routes_destroy(t_route **routes)
{
	int i;

	i = -1;
	while (NULL != routes[++i])
		ft_memdel((void**)&routes[i]);
	ft_memdel((void**)&routes);
}

void	lemin_routes_destroy(t_lem_in *lemin)
{
	int i;

	i = -1;
	while (++i < lemin->route_count)
		ft_memdel((void**)&lemin->routes[i]);
	lemin->route_count = 0;
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
}

void	route_inverse(t_route *best_route)
{
	int i;

	i = -1;
	while (++i < (best_route->size - 1))
		connect_del(best_route->elem[i], best_route->elem[i + 1]);
}

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

int fifo_include(t_room **fifo, t_room *node)
{
	int i;

	i = -1;
	while (NULL != fifo[++i])
		if (fifo[i] == node)
			return (1);
	return (0);
}
	
void lemin_init(t_lem_in *lemin)
{
	t_route route;

	lemin->max_route_count = (lemin->start->con_size < lemin->end->con_size) ?
								lemin->start->con_size : lemin->end->con_size;
	if (!(lemin->fifo = (t_room **)ft_memalloc(sizeof(t_room *) * lemin->num_of_rooms)))  // num_of_rooms != 0 ?
		ft_exit_fail("Error 14");
	if (!(lemin->routes = (t_route **)ft_memalloc(sizeof(t_route *) * (lemin->num_of_rooms * ROUTE_SIZE + 1)))) // max_route_count
			ft_exit_fail("Error 11");
	if (!(lemin->route = (t_bool *)ft_memalloc(sizeof(t_bool) * (lemin->num_of_rooms + 1))))
			ft_exit_fail("Error 19");
	route_clean(lemin);
	lemin->fifo[0] = lemin->start;
	ft_bzero(&route, sizeof(t_route));
	route.elem[route.size++] = lemin->fifo[0];
	lemin->fifo[0]->route = route_copy(&route);
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
		ants -= lemin->routes[route_count - 1]->size - lemin->routes[i]->size;
	if (route_count > 0)
		flow = lemin->routes[route_count - 1]->size + ants / route_count;
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

	i = 0;
	while (i < lemin->num_of_rooms)
	{
		lemin->array_of_rooms[i]->weight = BIG_INT;
		lemin->array_of_rooms[i]->pass = NO_VISIT;
		if (i != lemin->start->index && NULL != lemin->array_of_rooms[i]->route)
			ft_memdel((void **)&lemin->array_of_rooms[i]->route);
		++i;
	}
	ft_bzero(lemin->fifo + 1, sizeof(lemin->fifo) * (lemin->num_of_rooms - 1));
	lemin->start->weight = 0;
}

// recur_route(route_copy(route), start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);
		

int *dublicate_map(t_lem_in *lemin)
{
	int	*map;
	int i;

		if (!(map = (int *)ft_memalloc(sizeof(int) * (lemin->num_of_rooms + 1))))
			ft_exit_fail("Error 6");
		i = 0;
		while (i < lemin->num_of_rooms)
		{
			map[lemin->array_of_rooms[i]->index] = lemin->array_of_rooms[i]->pass;
			++i;
		}
		return (map);
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

void recur_route(t_route *route, t_room *room, int *map, t_lem_in *lemin)
{
	int i;
	
	route->elem[route->size++] = room;

	// printf("%s ", room->name);
	if (lemin->end == room)
	{
		// print_route(route);
		lemin->routes[lemin->route_count++] = route_copy(route);
		// if (0 < lemin->num_of_rooms)

		ft_memdel((void **)&route);
		ft_memdel((void **)&map);
		return ;
	}
	i = -1;
	while (++i < room->con_size)
		if (NO_VISIT == map[room->connections[i]->index] && !node_include(route, room->connections[i]->index))
		{
			map[room->index] = VISIT;
			recur_route(route_copy(route), room->connections[i], dublicate_map2(map, lemin->num_of_rooms), lemin);
		}
	
	ft_memdel((void **)&route);
	ft_memdel((void **)&map);
	return ;
}

void	dijkstra_search( t_room **fifo, t_lem_in *lemin, int i, int n)
{
	int		j;
	t_route	*temp;

	while (++i < n)
	{
		j = -1;
		while (++j < fifo[i]->con_size)
		{
				if ((NO_VISIT == fifo[i]->connections[j]->pass) &&
					(fifo[i]->weight + 1 <= fifo[i]->connections[j]->weight))
				{
					fifo[i]->connections[j]->weight = fifo[i]->weight + 1;
					if (NULL != fifo[i]->connections[j]->route)
						ft_memdel((void **)&fifo[i]->connections[j]->route);
					temp = route_copy(fifo[i]->route);
					temp->elem[temp->size++] = fifo[i]->connections[j];
					fifo[i]->connections[j]->route = temp;
				}
				if (!fifo_include(fifo, fifo[i]->connections[j]))
					fifo[n++] = fifo[i]->connections[j];
		}
		fifo[i]->pass = VISIT;
	}
}


void bhandari_search(t_lem_in *lemin)
{
	while (lemin->route_count < lemin->max_route_count) // max_route_count ? 
	{
		dijkstra_setup(lemin);
		dijkstra_search(lemin->fifo, lemin, -1, 1);
		if (BIG_INT == lemin->end->weight)
			break;
		route_inverse(lemin->end->route);
		// print_route(lemin->end->route);
		if (true == route_check(lemin, lemin->end->route))
		{
			lemin->routes[lemin->route_count++] = route_copy(lemin->end->route);
			if (!route_steps(lemin))
			{
				lemin->route_count--;
				break;
			}
			route_mark(lemin, lemin->end->route);
		}
	}
	route_recovery(lemin);
}
//*/
void	routes_search(t_lem_in *lemin)
{
	// t_route **prev;
	// t_route **next;

	bhandari_search(lemin);
	// if (lemin->num_of_rooms < 1500)
	// {
	// 	next = routes_copy(lemin->routes, lemin->route_count);
	// 	prev = NULL;
	// 	while (0 != routes_compare(prev, next))
	// 	{
	// 		lemin_routes_destroy(lemin);
	// 		route_clean(lemin);
	// 		bhandari_search(lemin);
	// 		if (NULL != prev)
	// 			routes_destroy(prev);
	// 		prev = next;
	// 		next = routes_copy(lemin->routes, lemin->route_count);
	// 	}
	// 	routes_destroy(prev);
	// 	routes_destroy(next);
	// }
}

int unique_search(t_route **routes, t_lem_in *lemin)
{
	int i;
	int j;
	int	temp;

	i = -1;
	temp = 0;
	while (NULL != routes[++i])
	{
		route_mark(lemin, routes[i]);
		routes[i]->weight += routes[i]->size;
		routes[i]->unique += 1;
		j = i;
		while (NULL != routes[++j])
		{
			if (true == route_check(lemin, routes[j]))
			{
				route_mark(lemin, routes[j]);
				routes[i]->weight += routes[j]->size;
				routes[i]->unique += 1;
			}
		}
		if ((routes[temp]->unique < routes[i]->unique) ||
						(routes[temp]->unique == routes[i]->unique &&
								routes[temp]->weight > routes[i]->weight))
			temp = i;
		route_clean(lemin);
	}
	return (temp);
}

void routes_complete(t_route **routes, t_lem_in *lemin, int number)
{
	int i;
	int temp;
	t_route *buff;

	temp = lemin->route_count;
	lemin->route_count = 0;
	i = 0;
	while (i < number)
		ft_memdel((void**)&routes[i++]);
	i = number;
	route_mark(lemin, routes[i]);
	routes[lemin->route_count++] = routes[i];
	while (NULL != routes[++i])
	{
		// if (i > 1 && !route_steps(lemin))
		// {
		// 	ft_memdel((void**)&routes[--lemin->route_count]);
		// 	break;
		// }
		if (true == route_check(lemin, routes[i]))
		{
			// buff = route_copy(routes[i]);
			// ft_memdel((void**)&routes[i]);
			route_mark(lemin, routes[i]);
			routes[lemin->route_count++] = routes[i];
		}
		else
			ft_memdel((void**)&routes[i]);
	}
	// lemin->route_count = j;

	while (i < temp)
		ft_memdel((void**)&routes[i++]);
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

void	route_sort(t_lem_in *lemin)
{
	int i;
	int j;
	t_route *temp;

	i = 0;
	while (i < lemin->route_count - 1)
	{
		j = 0;
		while (j < lemin->route_count - 1)
		{
			if (lemin->routes[j]->size > lemin->routes[j + 1]->size)
			{
				temp = lemin->routes[j];
				lemin->routes[j] = lemin->routes[j + 1];
				lemin->routes[j + 1] = temp;
			}
			++j;
		}
		++i;
	}
}
void recur_search(t_lem_in *lemin)
{
	t_route route;
	bzero(&route, sizeof(route));
	recur_route(route_copy(&route), lemin->start, dublicate_map(lemin), lemin);
	route_sort(lemin);
	// printf("\n duplicate_exclusion \n");
	
	// print_route(lemin.routes[1]);
	routes_complete(lemin->routes, lemin, unique_search(lemin->routes, lemin));
	
	// lemin.route_count = duplicate_exclusion(lemin.routes);
}


void	data_parsing(t_lem_in *lemin)
{
	get_num_of_ants(lemin);
	get_rooms(lemin);
	if (!lemin->start_flag || !lemin->end_flag)
	 	close_program(lemin, "no start or end room");		
	if (!(lemin->adjacency_matrix = init_adjacency_matrix(lemin->num_of_rooms)))
	 	close_program(lemin, "init_adjacency_matrix error");
	lemin->array_of_rooms = init_array_of_rooms(lemin);
	get_links(lemin);
	if (!check_start_end_links(lemin))
		close_program(lemin, "start or/and end room is/are without links");
}

int main(int argc, char **argv)
{
	t_lem_in	lemin;

	ft_bzero(&lemin, sizeof(lemin));
	data_parsing(&lemin);
	if (lemin.adjacency_matrix[lemin.start_index][lemin.end_index])
		start_end_solution(&lemin);
	else
	{
		lemin_init(&lemin);
		if (lemin.num_of_rooms < BIG) //  || lemin.num_of_rooms > 3000)
			recur_search(&lemin);
		else
			bhandari_search(&lemin);
		// print_routes(&lemin);
		init_path_array(&lemin);
		init_array_of_ants(&lemin);
		flow_distribution(&lemin);	//функция распределения потоков
	}
	print_ant_farm(&lemin);		//вывод фермы
	print_solution(&lemin);		//вывод решения
	// printf("\n %p \n %p", lemin.routes, lemin.routes[0]);
	// printf(" routes - %d, steps - %d\n", lemin.route_count, route_flow(&lemin, lemin.route_count));
	free_all(&lemin);
	return (1);
}
