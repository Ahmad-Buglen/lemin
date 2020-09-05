/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:28:21 by dphyliss          #+#    #+#             */
/*   Updated: 2020/09/05 19:43:42 by dphyliss         ###   ########.fr       */
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

void print_nodes(t_node **nodes)
{
	t_node *temp;
			int i;

	temp = *nodes;
	while (NULL != temp)
	{
		printf("%s [%d] (%d, %d) type - %d; con_size - %d ", temp->name, temp->index, temp->coordinates.x, temp->coordinates.y, temp->type, temp->con_size);
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

void init_middle(t_node **nodes)
{
	node_add(nodes, "A0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "A1", (t_coords){1, 1}, START_A);
	node_add(nodes, "A2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "A3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "A4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "A5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "A6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "A7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "A8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "A9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "B0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "B9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "C0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "D0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "E0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "F0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F4", (t_coords){1, 1}, END_A);
	node_add(nodes, "F5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "G0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "H0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "I0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I6", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I7", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I8", (t_coords){1, 1}, STANDART);
	node_add(nodes, "I9", (t_coords){1, 1}, STANDART);

	node_add(nodes, "J0", (t_coords){1, 1}, STANDART);
	node_add(nodes, "J1", (t_coords){1, 1}, STANDART);
	node_add(nodes, "J2", (t_coords){1, 1}, STANDART);
	node_add(nodes, "J3", (t_coords){1, 1}, STANDART);
	node_add(nodes, "J4", (t_coords){1, 1}, STANDART);
	node_add(nodes, "J5", (t_coords){1, 1}, STANDART);
	node_add(nodes, "J6", (t_coords){1, 1}, STANDART);

	connect_node(nodes, "A1", "A2");
	connect_node(nodes, "A2", "A3");
	connect_node(nodes, "A3", "A7");
	connect_node(nodes, "A7", "A0");
	connect_node(nodes, "A0", "B1");
	connect_node(nodes, "B1", "B3");
	connect_node(nodes, "B3", "B6");
	connect_node(nodes, "B6", "B9");
	connect_node(nodes, "B9", "C2");
	connect_node(nodes, "C2", "C3");
	connect_node(nodes, "C3", "C1");
	connect_node(nodes, "C1", "B7");
	connect_node(nodes, "B7", "B4");
	connect_node(nodes, "B4", "B0");
	connect_node(nodes, "B0", "A9");
	connect_node(nodes, "A9", "A5");
	connect_node(nodes, "A5", "A4");
	connect_node(nodes, "A4", "A6");
	connect_node(nodes, "A6", "A8");
	connect_node(nodes, "A8", "B2");
	connect_node(nodes, "B2", "B5");
	connect_node(nodes, "B5", "B8");
		connect_node(nodes, "B8", "F5");
		connect_node(nodes, "F5", "F6");
		connect_node(nodes, "F6", "F8");
		connect_node(nodes, "F8", "E0");
		connect_node(nodes, "E0", "F9");
		connect_node(nodes, "F9", "F7");
		connect_node(nodes, "F7", "F5");
	connect_node(nodes, "B8", "C0");
	connect_node(nodes, "C0", "C4");
	connect_node(nodes, "C4", "C5");
	connect_node(nodes, "C5", "C6");
	connect_node(nodes, "C6", "C7");
		connect_node(nodes, "C7", "E1");
		connect_node(nodes, "E1", "E3");
		connect_node(nodes, "E3", "E5");
		connect_node(nodes, "E5", "E4");
		connect_node(nodes, "E4", "E2");
		connect_node(nodes, "E2", "E1");
		connect_node(nodes, "E2", "E3");
		connect_node(nodes, "E2", "E5");
	connect_node(nodes, "C7", "C8");
	connect_node(nodes, "C8", "C9");
	connect_node(nodes, "C9", "F3");
	connect_node(nodes, "F3", "F4");


	connect_node(nodes, "A1", "D1");
	connect_node(nodes, "D1", "D2");
	connect_node(nodes, "D2", "D3");
	connect_node(nodes, "D3", "D4");
	connect_node(nodes, "D4", "D8");
	connect_node(nodes, "D8", "D9");
	connect_node(nodes, "D9", "F0");
	connect_node(nodes, "F0", "F1");
	connect_node(nodes, "F1", "F2");
	connect_node(nodes, "F2", "F4");


	connect_node(nodes, "A1", "E6");
	connect_node(nodes, "E6", "E7");
	connect_node(nodes, "E7", "E8");
	connect_node(nodes, "E8", "E9");
	connect_node(nodes, "E9", "G1");
	connect_node(nodes, "G1", "G0");
	connect_node(nodes, "G0", "G2");
	connect_node(nodes, "G2", "G3");
	connect_node(nodes, "G3", "G4");
	connect_node(nodes, "G4", "G5");
	connect_node(nodes, "G5", "G6");
	connect_node(nodes, "G6", "G7");
	connect_node(nodes, "G7", "G8");
	connect_node(nodes, "G8", "G9");
	connect_node(nodes, "G9", "F4");


	connect_node(nodes, "A1", "D5");
	connect_node(nodes, "D5", "D6");
	connect_node(nodes, "D6", "D7");

	connect_node(nodes, "A1", "H0");
		connect_node(nodes, "H0", "J6");
	connect_node(nodes, "H0", "H1");
	connect_node(nodes, "H1", "H2");
	connect_node(nodes, "H2", "H3");
	connect_node(nodes, "H3", "H4");
	connect_node(nodes, "H4", "H5");
	connect_node(nodes, "H5", "H6");
	connect_node(nodes, "H6", "H7");
	connect_node(nodes, "H7", "I1");
	connect_node(nodes, "I1", "I3");
	connect_node(nodes, "I3", "I2");
	connect_node(nodes, "I2", "H9");
	connect_node(nodes, "H9", "H8");
	connect_node(nodes, "H8", "I0");
	connect_node(nodes, "I0", "I4");
	connect_node(nodes, "I4", "I5");
	connect_node(nodes, "I5", "I6");
	connect_node(nodes, "I6", "I8");
	connect_node(nodes, "I8", "I7");
	connect_node(nodes, "I7", "I9");
	connect_node(nodes, "I9", "J0");
	connect_node(nodes, "J0", "J1");
		connect_node(nodes, "J1", "F0");
	connect_node(nodes, "J1", "J2");
		connect_node(nodes, "J2", "G7");

	connect_node(nodes, "J5", "J3");
	connect_node(nodes, "J3", "F4");

	connect_node(nodes, "J2", "F4");

	connect_node(nodes, "C4", "D0");
	connect_node(nodes, "D0", "C6");


	// node_add(nodes, "Z1", (t_coords){1, 1}, STANDART);
	// node_add(nodes, "Z2", (t_coords){1, 1}, STANDART);
	// node_add(nodes, "Z3", (t_coords){1, 1}, STANDART);
	// connect_node(nodes, "C0", "Z1");
	// connect_node(nodes, "Z1", "Z2");
	// connect_node(nodes, "Z2", "Z3");
	// connect_node(nodes, "Z3", "C8");
}

void	init_min(t_node **nodes)
{
	node_add(nodes, "A", (t_coords){1, 1}, START_A);
	node_add(nodes, "B", (t_coords){1, 1}, STANDART);
	node_add(nodes, "C", (t_coords){1, 1}, STANDART);
	node_add(nodes, "D", (t_coords){1, 1}, STANDART);
	node_add(nodes, "E", (t_coords){1, 1}, STANDART);
	node_add(nodes, "F", (t_coords){1, 1}, STANDART);
	node_add(nodes, "G", (t_coords){1, 1}, STANDART);
	node_add(nodes, "H", (t_coords){1, 1}, END_A);

	connect_node(nodes, "A", "B");
	connect_node(nodes, "B", "C");
	connect_node(nodes, "C", "D");
	connect_node(nodes, "D", "H");
	connect_node(nodes, "A", "E");
	connect_node(nodes, "E", "D");
	connect_node(nodes, "E", "F");
	connect_node(nodes, "F", "G");
	connect_node(nodes, "G", "H");
	
}

void print_route(t_route *route)
{
	int i;

	i = -1;
	while (++i < route->size)
		printf("%s ", route->elem[i]->name);
	printf("\n");
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

t_node *start_find(t_node **nodes, int start)
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

// t_map
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
/*
int  map_pass(t_map *map, char *name)
{
	t_map *temp;

	temp = map;
	while (NULL != temp)
	{
		if (0 == ft_strcmp(name, temp->name))
			return (temp->pass);
		temp = temp->next;
	}
	ft_exit_fail("Error 8");
	return (1);
}

t_map  *map_find(t_map *map, char *name)
{
	t_map *temp;

	temp = map;
	while (NULL != temp)
	{
		if (0 == ft_strcmp(name, temp->name))
			return (temp);
		temp = temp->next;
	}
	ft_exit_fail("Error 7");
	return (NULL);
}
*/
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

// t_route *dublicate_route(t_route *route)
// {
// 	t_route	*temp;
// 	int		i;

// 	if (!(temp = (t_route *)ft_memalloc(sizeof(t_route))))
// 			ft_exit_fail("Error 5");
// 	ft_bzero(temp, sizeof(t_route));
// 	temp->size = route->size;
// 	i = -1;
// 	while (++i < route->size)
// 		temp->elem[i] = route->elem[i];
// 	return (temp);
// }
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


void recur_route(t_route route, t_node *node, int *map, int node_len, t_route **best_route, int *counter, int status, t_route **routes)
{
	int i;
	int sides;
// write(1, "test", 4);
	route.elem[route.size++] = node;
	// printf("%s \n", node->name);
	if (END_A == node->type)
	{
		// printf(" Sucсess! ");
		// print_route(&route);
		if (END_A == status)
			routes[(*counter)] = route_copy(&route);

		++(*counter);
		if (((*best_route)->size == 0) || (route.size < (*best_route)->size))
		{

		// write(1, "here!", 5);
			// free(best_route);
			*best_route = route_copy(&route);
		}
		// free(map);
		return ;
	}
	sides = 0;
	i = 0;
	while (i < node->con_size)
	{
		if (NO_VISIT == map[node->connections[i]->index])
			++sides;
		++i;
	}

	if (sides <= 1)
	{
		map[node->index] = VISIT;
		i = -1;
		while (++i < node->con_size)
			if (NO_VISIT == map[node->connections[i]->index] && !node_include(&route, node->connections[i]->index))
			{
				recur_route(route, node->connections[i], map, node_len, best_route, counter, status, routes);
				break ;
			}
	}
	else
	{
		i = -1;
		while (++i < node->con_size)
			if (NO_VISIT == map[node->connections[i]->index] && !node_include(&route, node->connections[i]->index))
				recur_route(route, node->connections[i], dublicate_map2(map, node_len), node_len, best_route, counter, status, routes);
		map[node->index] = VISIT;
	}
	// printf(" Fail( ");
	// print_route(&route);

	// free(map);
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
	// init1(t_node *nodes);

int main(int argc, char **argv)
{

	t_node *nodes;
	t_node *start;

	t_node *end;
	t_route route;
	t_route *best_route;
	t_route **routes;

	int node_len;
	int counter;
	int temp;
	int status;
	int i;

	nodes = NULL;



	t_lem_in	lemin;
	
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

 	// printf("num of ants = %d\n", lemin.num_of_ants);
 	// print_room_list(lemin.room_list);
 	// print_hash_map(lemin.hash_map);
 	// print_array_of_rooms(&lemin);
 	// print_adjacency_matrix(&lemin);

 print_nodes(&nodes);


//init_middle(&nodes);
	node_len = node_length(nodes);

	start = start_find(&nodes, START_A);
	//  start = node_find(&nodes, "Z_k1");
	//  end = node_find(&nodes, "Adu3");
	//  end->type = END_A;
	//*	
	if (!(best_route = (t_route *)ft_memalloc(sizeof(t_route))))
			ft_exit_fail("Error 9");

	ft_bzero(best_route, sizeof(t_route));
	ft_bzero(&route, sizeof(t_route));
	temp = 0;
	counter = -1;
	status = STANDART;
	routes = NULL;

	while (counter != temp)
	{
		counter = 0;
		recur_route(route, start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);
		temp = counter;
		while (1)
		{
			// print_nodes(&nodes);
			ft_bzero(best_route, sizeof(t_route));
			recur_route(route, start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);

			if (0 == best_route->size)
				break;
			// print_route(best_route);
			route_inverse(&best_route);
		}

		// print_nodes(&nodes);
		route_recovery(nodes);
		counter = 0;
		recur_route(route, start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);
	}

	if (!(routes = (t_route **)ft_memalloc(sizeof(t_route *) * (counter + 1))))
			ft_exit_fail("Error 11");
	

	status = END_A;
	// printf("%d Finish! \n", counter);
	counter = 0;
	recur_route(route, start, dublicate_map(nodes, node_len), node_len, &best_route, &counter, status, routes);
	routes[counter] = NULL;
		// print_route(routes[1]);
		

	// i = -1;
	// while (NULL != routes[++i])
	// 	print_route(routes[i]);
	
	if (counter > 2)
	{
	// printf(" duplicate_exclusion! \n");
		duplicate_exclusion(routes);
	}
// write(1, "here\n", 5);
	i = -1;
	while (NULL != routes[++i])
		print_route(routes[i]);
	printf("\n%d", i);

//  print_nodes(&nodes);
	// printf("%.100f", 0.00000000000000000000002);


	//*/
	return (1);
}
