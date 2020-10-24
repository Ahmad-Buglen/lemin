/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_distribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:12:17 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/24 11:09:30 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		get_num_of_paths(t_lem_in *lemin)
{
	int		i;
	int		diff;

	if (!lemin->route_count || (lemin->routes && !lemin->routes[0]))
		ft_exit_lemin("no ways for ants");
	lemin->p = 1;
	if (lemin->route_count == 1)
		return ;
	i = 1;
	diff = 0;
	while (i < lemin->route_count)
	{
		diff += (lemin->routes[i]->size - lemin->routes[i - 1]->size) * i;
		if (lemin->num_of_ants <= diff + i)
			return ;
		lemin->p++;
		i++;
	}
}

void		ants_distribution(t_lem_in *lemin)
{
	int		ants;
	int		p;
	int		max_p;
	int		rem;
	int		div;

	p = 0;
	ants = lemin->num_of_ants;
	max_p = lemin->p - 1;
	while (p < lemin->p && ants)
	{
		lemin->routes[p]->ants = lemin->routes[max_p]->size -
									lemin->routes[p]->size + 1;
		ants -= lemin->routes[p]->ants;
		p++;
	}
	div = ants / lemin->p;
	rem = ants % lemin->p;
	p = 0;
	while (p < lemin->p)
		lemin->routes[p++]->ants += div;
	p = 0;
	while (rem--)
		lemin->routes[p++]->ants++;
}
