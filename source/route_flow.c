/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:25:32 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/17 16:25:49 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				route_flow(t_lem_in *const lemin, const int route_count)
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

int				route_steps(t_lem_in *const lemin)
{
	if (lemin->route_count > 1 &&
			route_flow(lemin, lemin->route_count) >=
				route_flow(lemin, lemin->route_count - 1))
		return (0);
	return (1);
}
