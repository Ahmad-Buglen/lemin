/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_distribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:12:17 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/20 09:30:12 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"

void			create_path(t_lem_in *lemin, t_path **path, t_route *route)
{
	int		n;

	n = route->size - 1;
	while (n >= 0)
	{
		add_elem_to_path(lemin, path, route->elem[n]->name,\
						route->elem[n]->index);
		n--;
	}
}

void			init_path_array(t_lem_in *lemin)
{
	int i;

	i = 0;
	if (!lemin->route_count || (lemin->routes && !lemin->routes[0]))
	{
		lemin->line_num = 0;
		close_program(lemin, "no ways for ants");
	}
	if (!(lemin->paths = (t_path**)ft_memalloc(sizeof(t_path*) *\
							(lemin->route_count + 1))))
		close_program(lemin, "malloc error");
	if (!(lemin->array_of_ants = (t_path**)ft_memalloc(sizeof(t_path*) *\
							lemin->num_of_ants)))
		close_program(lemin, "malloc error");
}

static void		cycle_body_1(t_lem_in *lemin, int p, int *i, int *diff)
{
	int		k;

	k = 0;
	while (k <= p && *i < lemin->num_of_ants)
	{
		lemin->array_of_ants[(*i)++] = lemin->paths[k++];
	}
	(*diff)--;
}

static void		cycle_body_2(t_lem_in *lemin, int p, int *i)
{
	int		k;

	k = 0;
	while (k <= p && *i < lemin->num_of_ants)
		lemin->array_of_ants[(*i)++] = lemin->paths[k++];
}

void			flow_distribution(t_lem_in *lemin)
{
	int		i;
	int		p;
	int		diff;

	i = 0;
	create_path(lemin, &lemin->paths[0], lemin->routes[0]);
	while (i < lemin->num_of_ants)
	{
		p = 0;
		while (p < lemin->route_count - 1 && i < lemin->num_of_ants)
		{
			create_path(lemin, &lemin->paths[p + 1], lemin->routes[p + 1]);
			diff = lemin->routes[p + 1]->size - lemin->routes[p]->size;
			while (diff > 0 && i < lemin->num_of_ants)
				cycle_body_1(lemin, p, &i, &diff);
			p++;
		}
		if (p == lemin->route_count - 1)
			break ;
	}
	while (i < lemin->num_of_ants)
		cycle_body_2(lemin, p, &i);
}
