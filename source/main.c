/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:41:56 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/16 16:46:20 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"

void		check_route(t_lem_in *lemin, t_route *route)
{
	int		i;
	
	i = 0;
	while (i < route->size - 1)
	{
		if (!lemin->adjacency_matrix[route->elem[i]->index][route->elem[i + 1]->index])
			close_program(lemin, "algorythm mistake");
		i++;
	}
}

void		check_routes(t_lem_in *lemin)
{
	int		i;

	i = 0;
	while (i < lemin->route_count)
	{
		check_route(lemin, lemin->routes[i]);
		i++;
	}
	write(1, "sucsess\n", 9);
}
