/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:36:51 by bsausage          #+#    #+#             */
/*   Updated: 2020/09/02 18:48:19 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
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

void	print_hash_map(t_lem_list *hash_map[HASH_SIZE])
{
	int		i;
	t_lem_list	*list;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (hash_map[i])
		{
			list = hash_map[i];
			while (list)
			{
				printf("i = %d\n", i);
				printf("\tname = %s\tindex = %d\n", list->room->name, list->room->index);
				list = list->next;
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
			printf("n = %u\tname = %s\tindex = %d\tbfs_level = %d\t flag = %d\n",
				n, lemin->array_of_rooms[n]->room->name, lemin->array_of_rooms[n]->room->index, lemin->array_of_rooms[n]->room->level, lemin->array_of_rooms[n]->room->flag);
		n++;
	}		
}
