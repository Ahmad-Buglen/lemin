/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:28:21 by dphyliss          #+#    #+#             */
/*   Updated: 2020/07/20 19:09:00 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/lemin.h"

#include <stdio.h>

void node_add(t_node **nodes, char *name, t_coordinates coordinates, int type)
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
		*nodes = temp;
	else
	{
		buff = *nodes;
		while (NULL != buff->next)
			buff = buff->next;
		buff->next = temp;		
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
		printf("%s (%d, %d) ", temp->name, temp->coordinates.x, temp->coordinates.y);
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

void init(t_node **nodes)
{
	node_add(nodes, "A0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "A1", (t_coordinates){1, 1}, START);
	node_add(nodes, "A2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "A3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "A4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "A5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "A6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "A7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "A8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "A9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "B0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "B9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "C0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "C9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "D0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "D9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "E0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "E9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "F0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "F1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "F2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "F3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "F4", (t_coordinates){1, 1}, END);
	node_add(nodes, "F5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "F6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "F7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "F8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "F9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "G0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "G9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "H0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "H9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "I0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I6", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I7", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I8", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "I9", (t_coordinates){1, 1}, STANDART);

	node_add(nodes, "J0", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "J1", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "J2", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "J3", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "J4", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "J5", (t_coordinates){1, 1}, STANDART);
	node_add(nodes, "J6", (t_coordinates){1, 1}, STANDART);

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
	
}

void print_route(t_route *route)
{
	int i;

	i = -1;
	while (++i < route->size)
		printf("%s ", route->elem[i]->name);
	printf("\n");
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

void recur_route(t_route route, t_node *node)
{
	int i;


	
	route.elem[route.size++] = node;
	// printf("%s \n", node->name);
	if (END == node->type)
	{
		printf("finish");
		print_route(&route);
		return ;
	}
	else
		node->pass = VISIT;
	i = -1;
	while (++i < node->con_size)
		if (NO_VISIT == node->connections[i]->pass)
			recur_route(route, node->connections[i]);	
	return ;
}

int main()
{
	t_node *nodes;
	t_node *start;
	t_route route;

	nodes = NULL;
	init(&nodes);
	start = start_find(&nodes, START);
	ft_bzero(&route, sizeof(route));

	print_nodes(&nodes);
	recur_route(route, start);

	// printf("%.100f", 0.00000000000000000000002);

	return (1);
}