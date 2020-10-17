/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes_sift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:16:36 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/17 16:57:00 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		routes_destroy(t_route **routes)
{
	int		i;

	i = -1;
	while (NULL != routes[++i])
		ft_memdel((void**)&routes[i]);
	ft_memdel((void**)&routes);
}

void		lemin_routes_destroy(t_lem_in *const lemin)
{
	int		i;

	i = -1;
	while (++i < lemin->route_count)
		ft_memdel((void**)&lemin->routes[i]);
	lemin->route_count = 0;
}

int			unique_search(t_route *const *const routes, t_lem_in *const lemin)
{
	int		i;
	int		j;
	int		temp;

	i = -1;
	temp = 0;
	while (NULL != routes[++i])
	{
		route_put(lemin, routes[i]);
		j = i;
		while (NULL != routes[++j])
			if (true == route_check(lemin, routes[j]))
				route_put(lemin, routes[i]);
		if ((routes[temp]->unique < routes[i]->unique) ||
						(routes[temp]->unique == routes[i]->unique &&
								routes[temp]->weight > routes[i]->weight))
			temp = i;
		route_clean(lemin);
	}
	return (temp);
}

void		routes_complete(t_route **const routes,
								t_lem_in *const lemin, const int number)
{
	int		i;
	int		temp;

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
		if (true == route_check(lemin, routes[i]))
		{
			route_mark(lemin, routes[i]);
			routes[lemin->route_count++] = routes[i];
		}
		else
			ft_memdel((void**)&routes[i]);
	}
	while (i < temp)
		ft_memdel((void**)&routes[i++]);
}

void		route_sort(t_lem_in *const lemin)
{
	int		i;
	int		j;
	t_route	*temp;

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
