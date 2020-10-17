/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bhandari_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:14:34 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/17 16:25:21 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			route_inverse(t_route *const route)
{
	int i;

	i = -1;
	while (++i < (route->size - 1))
		connect_del(route->elem[i], route->elem[i + 1]);
}

int				connection_include(t_room *const node1, t_room *const node2)
{
	int i;

	i = -1;
	while (++i < node1->con_size)
		if (node1->connections[i] == node2)
			return (1);
	return (0);
}

void			connection_restore(t_room *const node1, t_room *const node2)
{
	node1->connections[(node1->con_size)++] = node2;
}

void			route_recovery(t_lem_in *const lemin)
{
	int	i;
	int	j;

	i = -1;
	while (++i < lemin->num_of_rooms)
	{
		j = -1;
		while (++j < lemin->array_of_rooms[i]->con_size)
			if (!connection_include(lemin->array_of_rooms[i]->connections[j],\
													lemin->array_of_rooms[i]))
				connection_restore(lemin->array_of_rooms[i]->connections[j],\
				lemin->array_of_rooms[i]);
	}
}

void			bhandari_search(t_lem_in *const lemin)
{
	while (lemin->route_count < lemin->max_route_count)
	{
		dijkstra_setup(lemin);
		dijkstra_search(lemin->fifo, -1, 1);
		if (BIG_INT == lemin->end->weight)
			break ;
		route_inverse(lemin->end->route);
		if (true == route_check(lemin, lemin->end->route))
		{
			lemin->routes[lemin->route_count++] = route_copy(lemin->end->route);
			if (!route_steps(lemin))
			{
				lemin->route_count--;
				break ;
			}
			route_mark(lemin, lemin->end->route);
		}
	}
	route_recovery(lemin);
}
