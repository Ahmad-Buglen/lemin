/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:47:12 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/20 09:45:20 by Alkor            ###   ########.fr       */
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

void			print_start_end_solution(t_lem_in *lemin)
{
	int		i;

	i = 1;
	while (i < lemin->num_of_ants)
	{
		write(1, "L", 1);
		ft_putnbr(i++);
		write(1, "-", 1);
		ft_putstr(lemin->end->name);
		write(1, " ", 1);
	}
	write(1, "L", 1);
	ft_putnbr(i);
	write(1, "-", 1);
	ft_putstr(lemin->end->name);
	write(1, "\n", 1);
}
