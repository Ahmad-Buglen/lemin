/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ant_farm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:45:27 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/17 11:54:46 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

void		add_line_to_farm_list(t_lem_in *lemin)
{
	t_farm		*tmp;
	t_farm		*tmp2;

	if (!(tmp2 = (t_farm*)ft_memalloc(sizeof(t_farm))))
		close_program(lemin, "malloc error");
	if (!(tmp2->line = ft_strdup(lemin->line)))
		close_program(lemin, "malloc error");
	if (!lemin->farm_list)
		lemin->farm_list = tmp2;
	else
	{
		tmp = lemin->farm_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = tmp2;
	}
}

void		print_ant_farm(t_lem_in *lemin)
{
	t_farm		*farm;

	farm = lemin->farm_list;
	while (farm)
	{
		ft_putendl(farm->line);
		farm = farm->next;
	}
}
