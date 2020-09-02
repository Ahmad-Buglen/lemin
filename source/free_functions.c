/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:28:40 by bsausage          #+#    #+#             */
/*   Updated: 2020/09/02 18:48:19 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include <errno.h>

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

void		free_room_list(t_room **begin_list)
{
	t_room		*tmp;

	tmp = *begin_list;
	while (tmp)
	{
		*begin_list = tmp->next;
		ft_memdel((void**)&tmp->name);
		ft_memdel((void**)&tmp);
		tmp = *begin_list;
	}
	ft_memdel((void**)begin_list);
}

void		free_list(t_lem_list **begin_list)
{
	t_lem_list		*tmp;

	tmp = *begin_list;
	while (tmp)
	{
		*begin_list = tmp->next;
		ft_memdel((void**)&tmp);
		tmp = *begin_list;
	}
	ft_memdel((void**)begin_list);
}

void		free_hash_map(t_lem_in *lemin)
{
	int		n;
	
	n = 0;
	while (n < HASH_SIZE)
	{
		free_list(&lemin->hash_map[n]);
		n++;
	}
}

void		free_all(t_lem_in *lemin)
{
	ft_memdel((void**)&lemin->line);
	free_adjacency_matrix(lemin);
	free_hash_map(lemin);
	free_list(&lemin->path);
	free_list(&lemin->queue_begin);
	free_room_list(&lemin->room_list);
	ft_memdel((void**)&lemin->array_of_rooms);
	ft_memdel((void**)&lemin->array_of_ants);
}

void		close_program(t_lem_in *lemin, char *error_msg)
{
	free_all(lemin);
	if (!errno)
		ft_putendl_fd(error_msg, 2);
	else
		perror(error_msg);
	exit (1);
}
