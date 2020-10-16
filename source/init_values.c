/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:20:56 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/16 13:51:48 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

int			**init_adjacency_matrix(int n)
{
	int		**matrix;
	int		i;

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
