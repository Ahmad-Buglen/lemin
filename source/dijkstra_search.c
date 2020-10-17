/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:13:39 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/17 16:51:50 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				fifo_include(t_room *const *const fifo, t_room *const node)
{
	int i;

	i = -1;
	while (NULL != fifo[++i])
		if (fifo[i] == node)
			return (1);
	return (0);
}

void			dijkstra_setup(t_lem_in *const lemin)
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

void			dijkstra_search(t_room **const fifo, int i, int n)
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
