/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:20:56 by bsausage          #+#    #+#             */
/*   Updated: 2020/09/24 17:19:21 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

// void		assign_by_zero_path_len(t_lem_in *lemin)
// {
// 	int		i;

// 	i = 0;
// 	while (i < 100)
// 		lemin->path_len[i++] = 0;
// }

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
	lemin->queue_begin = NULL;
	lemin->queue_end = NULL;
	lemin->path = NULL;

	lemin->nodes = NULL; // ?
	// lemin->path2 = NULL;
	// lemin->path3 = NULL;
	lemin->array_of_ants = NULL;
	assign_null_hash_map(lemin);
	// assign_by_zero_path_len(lemin);
}

int			**init_adjacency_matrix(int n)
{
	int		**matrix;
	int		i;
	int		j;

	i = 0;
	if (!(matrix = (int**)malloc(sizeof(int*) * n)))
		return (NULL);
	while (i < n)
	{
		if (!(matrix[i] = (int*)malloc(sizeof(int) * n)))
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

t_lem_list		**init_array_of_rooms(t_lem_in *lemin)
{
	t_lem_list		**tmp;
	int			n;

	n = 0;
	if (!(tmp = (t_lem_list**)malloc(sizeof(t_lem_list*) * lemin->num_of_rooms)))
		close_program(lemin, "init array of rooms error");
	while (n < lemin->num_of_rooms)
		tmp[n++] = NULL;
	return (tmp);
}

