/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:20:56 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/10 15:48:20 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

void		init_values(t_lem_in *lemin)
{
	lemin->line = NULL;
	lemin->room_list = NULL;
	lemin->num_of_ants = 0;
	lemin->num_of_rooms = 0;
	lemin->position = MIDDLE;
	lemin->start_flag = 0;
	lemin->end_flag = 0;
	lemin->adjacency_matrix = NULL;
	lemin->start_index = 0;
	lemin->end_flag = 0;
	lemin->paths = NULL;
	lemin->array_of_ants = NULL;
	lemin->fifo_nodes = NULL;
	lemin->routes = NULL;
	assign_null_hash_map(lemin);
}

int			**init_adjacency_matrix(int n)
{
	int		**matrix;
	int		i;
	int		j;

	i = 0;
	if (!(matrix = (int**)ft_memalloc(sizeof(int*) * n)))
		return (NULL);
	while (i < n)
	{
		if (!(matrix[i] = (int*)ft_memalloc(sizeof(int) * n)))
		{
			while (i >= 0)
				ft_memdel((void**)&matrix[i--]);
			return (NULL);
		}
		j = 0;
		while (j < n)
			matrix[i][j++] = 0;
		i++;
	}
	return (matrix);
}

t_room		**init_array_of_rooms(t_lem_in *lemin)
{
	t_room		**tmp;
	t_room		*list;
	int			n;

	n = 0;
	if (!(tmp = (t_room**)ft_memalloc(sizeof(t_room*) * \
				(lemin->num_of_rooms + 1))))
		close_program(lemin, "init array of rooms error");
	list = lemin->room_list;
	while (list)
	{
		tmp[n++] = list;
		list = list->next;
	}
	return (tmp);
}
