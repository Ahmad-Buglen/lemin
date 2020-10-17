/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:03:52 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/17 17:12:44 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_route		*route_copy(t_route *const route)
{
	t_route *copy;

	if (!(copy = (t_route *)ft_memalloc(sizeof(t_route))))
		ft_exit_lemin("The system did not allocate memory");
	ft_memcpy((void *)copy, (void *)route, sizeof(t_route));
	return (copy);
}

void	route_put(t_lem_in *const lemin, t_route *const route)
{
	route_mark(lemin, route);
	route->weight += route->size;
	route->unique += 1;
}

void		route_clean(t_lem_in *const lemin)
{
	int	i;

	i = 0;
	while (++i < lemin->num_of_rooms)
		lemin->route[i] = false;
}

void		route_mark(t_lem_in *const lemin, t_route *const route)
{
	int	i;

	i = 0;
	while (++i < route->size - 1)
		lemin->route[route->elem[i]->index] = true;
}

t_bool		route_check(t_lem_in *const lemin, t_route *const route)
{
	int	i;

	i = 0;
	while (++i < route->size - 1)
		if (lemin->route[route->elem[i]->index] == true)
			return (false);
	return (true);
}
