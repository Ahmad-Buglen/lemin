/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:11:14 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/19 15:37:37 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

int				node_include(t_route *const route, const int index)
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

int				*dublicate_map(t_lem_in *const lemin)
{
	int	*map;
	int i;

	if (!(map = (int *)ft_memalloc(sizeof(int) * (lemin->num_of_rooms + 1))))
		ft_exit_lemin("The system did not allocate memory");
	i = 0;
	while (i < lemin->num_of_rooms)
	{
		map[lemin->array_of_rooms[i]->index] = lemin->array_of_rooms[i]->pass;
		++i;
	}
	return (map);
}

int				*copy_map(int *const map_src, const int node_len)
{
	int		*map_dest;

	if (0 != node_len)
	{
		if (!(map_dest = (int *)ft_memalloc(sizeof(int) * node_len)))
			ft_exit_lemin("The system did not allocate memory");
		ft_memcpy((void*)map_dest, (void*)map_src, sizeof(int) * node_len);
		return (map_dest);
	}
	return (NULL);
}

void			recur_route(t_route *const route, t_room *const room,
								int *const map, t_lem_in *const lemin)
{
	int i;

	if ((route->size + 1 == ROUTE_SIZE) ||
			(lemin->route_count + 1 == lemin->num_of_rooms * 5))
		ft_exit_lemin("Error: Oversize rooms or connections");
	route->elem[route->size++] = room;
	if (lemin->end == room)
	{
		lemin->routes[lemin->route_count++] = route;
		ft_memdel((void **)&map);
		return ;
	}
	i = -1;
	while (++i < room->con_size)
		if (NO_VISIT == map[room->connections[i]->index] &&\
			!node_include(route, room->connections[i]->index))
		{
			map[room->index] = VISIT;
			recur_route(route_copy(route), room->connections[i],\
				copy_map(map, lemin->num_of_rooms), lemin);
		}
	ft_memdel((void **)&route);
	ft_memdel((void **)&map);
	return ;
}

void			recur_search(t_lem_in *const lemin)
{
	t_route		route;

	bzero(&route, sizeof(route));
	recur_route(route_copy(&route), lemin->start, dublicate_map(lemin), lemin);
	if (0 == lemin->route_count)
		return ;
	route_sort(lemin);
	routes_complete(lemin->routes, lemin, unique_search(lemin->routes, lemin));
}
