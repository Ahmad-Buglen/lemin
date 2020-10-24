/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:28:40 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/24 10:46:35 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"

void		free_adjacency_matrix(t_lem_in *lemin)
{
	int		n;

	if (!lemin->adjacency_matrix)
		return ;
	n = lemin->num_of_rooms - 1;
	while (n >= 0)
		ft_memdel((void**)&lemin->adjacency_matrix[n--]);
	ft_memdel((void**)&lemin->adjacency_matrix);
}

void		free_room_list(t_lem_in *lemin)
{
	int	i;

	i = 0;
	while (i < lemin->num_of_rooms)
	{
		ft_memdel((void**)&lemin->array_of_rooms[i]->name);
		if (NULL != lemin->array_of_rooms[i]->route)
			ft_memdel((void**)&lemin->array_of_rooms[i]->route);
		if (NULL != lemin->array_of_rooms[i]->connections)
			ft_memdel((void**)&lemin->array_of_rooms[i]->connections);
		ft_memdel((void**)&lemin->array_of_rooms[i]);
		i++;
	}
}

void		free_farm_list(t_farm **begin_list)
{
	t_farm		*tmp;

	if (!begin_list)
		return ;
	tmp = *begin_list;
	while (tmp)
	{
		*begin_list = tmp->next;
		ft_memdel((void**)&tmp->line);
		ft_memdel((void**)&tmp);
		tmp = *begin_list;
	}
	ft_memdel((void**)begin_list);
}

void		free_all(t_lem_in *lemin)
{
	ft_memdel((void**)&lemin->line);
	free_farm_list(&lemin->farm_list);
	free_adjacency_matrix(lemin);
	if (NULL != lemin->start->route)
		ft_memdel((void**)&lemin->start->route);
	free_room_list(lemin);
	ft_memdel((void**)&lemin->array_of_rooms);
	ft_memdel((void**)&lemin->fifo);
	lemin_routes_destroy(lemin);
	ft_memdel((void**)&lemin->routes);
	ft_memdel((void**)&lemin->route);
}
