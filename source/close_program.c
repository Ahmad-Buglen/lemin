/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:09:47 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/24 14:43:39 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include <stdio.h>
#include <errno.h>

void		ft_exit_lemin(char *const message)
{
	ft_putendl_fd(message, 2);
	exit(1);
}

void		close_program(t_lem_in *lemin, char *error_msg)
{
	if (!errno && lemin->line_num)
	{
		ft_putstr_fd("Error (line ", 2);
		ft_putnbr_fd(lemin->line_num, 2);
		ft_putstr_fd("): ", 2);
		ft_putendl_fd(error_msg, 2);
	}
	else if (!errno)
		ft_putendl_fd(error_msg, 2);
	else
		perror("Error");
	exit(1);
}

void		print_route(t_route *route)
{
	int		i;

	i = -1;
	while (++i < route->size)
	{
		ft_putstr(route->elem[i]->name);
		if (i == route->size - 1)
			write(1, "\n", 1);
		else
			write(1, " -> ", 4);
	}
}

void		print_routes(t_lem_in *lemin)
{
	int		i;

	i = -1;
	write(1, "\nPATHS\n", 8);
	while (++i < lemin->route_count)
		print_route(lemin->routes[i]);
}
