/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:28:40 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/10 13:56:45 by bsausage         ###   ########.fr       */
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

void		free_room_list(t_lem_in *lemin)
{
	// t_room		*tmp;
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
	// tmp = *begin_list;
	// while (tmp)
	// {
	// 	*begin_list = tmp->next;
	// 	ft_memdel((void**)&tmp->name);
	// 	if (NULL != tmp->route)
	// 		ft_memdel((void**)&tmp->route);
	// 	if (NULL != tmp->connections)
	// 		ft_memdel((void**)&tmp->connections);
	// 	ft_memdel((void**)&tmp);
	// 	tmp = *begin_list;
	// }
	// ft_memdel((void**)begin_list);
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

void		free_paths(t_lem_in *lemin)
{
	t_path		**paths;
	t_path		*path;
	t_path		*tmp;
	int			n;

	n = 0;
	path = lemin->path;
	while (path)
	{
		tmp = path->next;
		ft_memdel((void**)&path->name);
		ft_memdel((void**)&path);
		path = tmp;
	}
	if (!lemin->paths)
		return ;
	while (n <= lemin->route_count)
	{
		path = lemin->paths[n];
		while (path)
		{
			tmp = path->next;
			ft_memdel((void**)&path->name);
			ft_memdel((void**)&path);
			path = tmp;
		}
		n++;
	}
	ft_memdel((void**)&lemin->paths);
}

void		free_all(t_lem_in *lemin)
{
	ft_memdel((void**)&lemin->line);
	free_adjacency_matrix(lemin);
	free_hash_map(lemin);
	if (lemin->fifo_nodes)
		ft_memdel((void**)&lemin->fifo_nodes[0]->route);///segmentation fault
	free_room_list(lemin);
	free_paths(lemin);
	ft_memdel((void**)&lemin->array_of_rooms);
	ft_memdel((void**)&lemin->array_of_ants);
	ft_memdel((void**)&lemin->fifo_nodes);
	if (lemin->routes)
		routes_destroy(lemin->routes, &lemin->route_count);
	ft_memdel((void**)&lemin->routes);
	ft_memdel((void**)&lemin->route);
	// if (NULL != lemin->room_list)
	// 	ft_memdel((void**)&lemin->room_list);
	// ft_memdel((void**)&lemin);
}

void		close_program(t_lem_in *lemin, char *error_msg)
{
	//free_all(lemin);
	if (!errno)
		ft_putendl_fd(error_msg, 2);
	else
		perror("Error");
	exit (1);
}
