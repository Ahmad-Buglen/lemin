/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:36:51 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/24 13:34:30 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	this file contains forbidden functions
**	this code is not used in the final version of the project
*/

#include "lemin.h"
#include "libft.h"
#include <stdio.h>

void	print_room_list(t_room *room_list)
{
	while (room_list)
	{
		printf("\tname = %s\tindex = %d\tx = %d\ty = %d\tposition = %s\n",
				room_list->name, room_list->index, room_list->coords.x, room_list->coords.y,
				room_list->position == START ? "START" : (room_list->position == END ? "END" : "MIDDLE"));
		room_list = room_list->next;
	}
}

void	print_hash_map(t_room *hash_map[HASH_SIZE])
{
	int		i;
	t_room	*list;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (hash_map[i])
		{
			list = hash_map[i];
			while (list)
			{
				printf("i = %d\n", i);
				printf("\tname = %s\tindex = %d\n", list->name, list->index);
				list = list->hash_next;
			}
		}
		i++;
	}
}

void	print_adjacency_matrix(t_lem_in *lemin)
{
	int		i;
	int		j;
	
	i = 0;
	while (i < lemin->num_of_rooms)
	{
		j = 0;
		while ( j < lemin->num_of_rooms)
			printf("%d ", lemin->adjacency_matrix[i][j++]);
		printf("\n");
		i++;
	}
}

void	print_array_of_rooms(t_lem_in *lemin)
{
	int	n;

	n = 0;
	while (n < lemin->num_of_rooms)
	{
		if (!lemin->array_of_rooms[n])
			printf("NULL\n");
		else
			printf("n = %u\tname = %s\tindex = %d\n",
				n, lemin->array_of_rooms[n]->name, lemin->array_of_rooms[n]->index);
		n++;
	}		
}

void	print_route(t_route *route)
{
	int i;

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

void	print_routes(t_lem_in *lemin)
{
	int i;
	
	i = -1;
	write(1, "\nPATHS\n", 8);
	while (++i < lemin->route_count)
		print_route(lemin->routes[i]);
}

void		check_route(t_lem_in *lemin, t_route *route)
{
	int		i;
	
	i = 0;
	while (i < route->size - 1)
	{
		if (!lemin->adjacency_matrix[route->elem[i]->index][route->elem[i + 1]->index])
			close_program(lemin, "algorythm mistake");
		i++;
	}
}

void		check_routes(t_lem_in *lemin)
{
	int		i;

	i = 0;
	while (i < lemin->route_count)
	{
		check_route(lemin, lemin->routes[i]);
		i++;
	}
	write(1, "sucsess\n", 9);
}