/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:08:34 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/17 16:51:35 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			connect_add(t_room *const node1, t_room *const node2)
{
	t_room	**temp;
	int		i;

	if (0 == node1->con_size)
	{
		if (!(node1->connections = (t_room **)\
			ft_memalloc(sizeof(t_room *) * 2)))
			ft_exit_lemin("The system did not allocate memory");
		node1->connections[0] = node2;
		node1->con_size = 1;
	}
	else
	{
		if (!(temp = (t_room **)ft_memalloc(sizeof(t_room *) *\
					(node1->con_size + 2))))
			ft_exit_lemin("The system did not allocate memory");
		i = -1;
		while (++i < node1->con_size)
			temp[i] = node1->connections[i];
		temp[node1->con_size] = node2;
		++node1->con_size;
		ft_memdel((void **)&node1->connections);
		node1->connections = temp;
	}
	node1->connections[node1->con_size] = NULL;
}

void			connect_del(t_room *const node1, t_room *const node2)
{
	int i;

	i = -1;
	while (++i < node1->con_size)
		if (node1->connections[i] == node2)
			break ;
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
	}
}

void			connect_node(t_room *const room1, t_room *const room2)
{
	if (!room1 || !room2)
		ft_exit_lemin("Error 3");
	connect_add(room1, room2);
	connect_add(room2, room1);
}
