/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:47:12 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/24 14:39:40 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

void			print_start_end_solution(t_lem_in *lemin)
{
	int		i;

	i = 1;
	if (lemin->p_flag)
	{
		write(1, "\nPATHS\n", 8);
		ft_putstr(lemin->start->name);
		write(1, " -> ", 4);
		ft_putstr(lemin->end->name);
		write(1, "\n\n", 2);
	}
	while (i <= lemin->num_of_ants)
	{
		write(1, "L", 1);
		ft_putnbr(i++);
		write(1, "-", 1);
		ft_putstr(lemin->end->name);
		write(1, "\n", 1);
	}
}

void			print_step(t_lem_in *lemin, char *name, int ant)
{
	if (lemin->start_flag)
		lemin->start_flag = 0;
	else
		write(1, " ", 1);
	write(1, "L", 1);
	ft_putnbr(ant);
	write(1, "-", 1);
	ft_putstr(name);
}

void			check_ant_position(t_lem_in *lemin, t_route *route, int i)
{
	if (i < route->size)
	{
		if (route->elem[i] == lemin->end && route->elem[i - 1]->ant)
		{
			print_step(lemin, lemin->end->name, route->elem[i - 1]->ant);
			route->elem[i - 1]->ant = 0;
			lemin->end->ant++;
		}
		else if (i == route->size - 2 && route->elem[i]->ant)
		{
			print_step(lemin, lemin->end->name, route->elem[i]->ant);
			route->elem[i]->ant = 0;
			lemin->end->ant++;
		}
		else if (route->elem[i]->ant)
		{
			print_step(lemin, route->elem[i + 1]->name, route->elem[i]->ant);
			route->elem[i + 1]->ant = route->elem[i]->ant;
			route->elem[i]->ant = 0;
		}
	}
}

void			move_ant(t_route *route, t_lem_in *lemin, int *ant, int n)
{
	int		i;

	i = n;
	while (i > 0)
	{
		check_ant_position(lemin, route, i);
		i--;
	}
	if (!i && route->ants && *ant <= lemin->num_of_ants)
	{
		print_step(lemin, route->elem[i + 1]->name, *ant);
		route->elem[i + 1]->ant = *ant;
		route->ants--;
		(*ant)++;
	}
}

void			print_solution(t_lem_in *lemin)
{
	int		ant;
	int		p;
	int		n;
	int		max_n;

	ant = 1;
	n = 0;
	if (lemin->p_flag)
		print_routes(lemin);
	max_n = lemin->routes[lemin->p - 1]->size - 1;
	write(1, "\n", 1);
	while (lemin->end->ant < lemin->num_of_ants)
	{
		p = 0;
		lemin->start_flag = 1;
		while (p < lemin->p && lemin->end->ant < lemin->num_of_ants)
		{
			move_ant(lemin->routes[p], lemin, &ant, n);
			p++;
		}
		write(1, "\n", 1);
		n += n == max_n ? 0 : 1;
	}
}
