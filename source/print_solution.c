/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:47:12 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/17 11:51:28 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

static void		print_step(t_lem_in *lemin, int i, int *new_line)
{
	if (*new_line)
		write(1, " ", 1);
	else
		*new_line = 1;
	write(1, "L", 1);
	ft_putnbr(i + 1);
	write(1, "-", 1);
	ft_putstr(lemin->array_of_ants[i]->name);
}

void			print_solution(t_lem_in *lemin)
{
	int		i;
	int		new_line;

	write(1, "\n", 1);
	while (lemin->array_of_ants[lemin->num_of_ants - 1]->next)
	{
		i = 0;
		new_line = 0;
		while (i < lemin->num_of_ants)
		{
			if (lemin->array_of_ants[i] && \
				lemin->array_of_ants[i]->index != (int)lemin->end_index && \
				lemin->array_of_ants[i]->next->status == EMPTY)
			{
				lemin->array_of_ants[i]->status = EMPTY;
				lemin->array_of_ants[i] = lemin->array_of_ants[i]->next;
				if (lemin->array_of_ants[i]->index != (int)lemin->end_index)
					lemin->array_of_ants[i]->status = NOT_EMPTY;
				print_step(lemin, i, &new_line);
			}
			i++;
		}
		write(1, "\n", 1);
	}
}

void			start_end_solution(t_lem_in *lemin)
{
	int		i;

	i = 0;
	lemin->route_count = 1;
	init_path_array(lemin);
	add_elem_to_path(lemin, &lemin->paths[0],\
					lemin->end->name, lemin->end_index);
	add_elem_to_path(lemin, &lemin->paths[0],\
					lemin->start->name, lemin->start_index);
	lemin->array_of_ants = (t_path**)ft_memalloc(sizeof(t_path*) *\
							lemin->num_of_ants);
	while (i < lemin->num_of_ants)
		lemin->array_of_ants[i++] = lemin->paths[0];
}
