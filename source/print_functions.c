/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 11:36:51 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/03 11:37:49 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				n, lemin->array_of_rooms[n]->name, lemin->array_of_rooms[n]->index, lemin->array_of_rooms[n]->level, lemin->array_of_rooms[n]->flag);
		n++;
	}		
}

////////
//////// PRINT ANT FARM FUNCTIONS
////////

void		print_room(t_room *room)
{
	ft_putstr(room->name);
	write(1, " ", 1);
	ft_putnbr(room->coords.x);
	write(1, " ", 1);
	ft_putnbr(room->coords.y);
	write(1, "\n", 1);
}

void		print_room_part(t_lem_in *lemin)
{
	t_room		*room;

	room = lemin->room_list;
	while (room)
	{
		if (room->index == lemin->start_index)
		{
			ft_putendl("##start");
			print_room(room);
		}
		else if (room->index == lemin->end_index)
		{
			ft_putendl("##end");
			print_room(room);
		}
		else
			print_room(room);
		room = room->next;
	}
}

void		print_link(char *room_name_1, char *room_name_2)
{
	ft_putstr(room_name_1);
	write(1, "-", 1);
	ft_putstr(room_name_2);
	write(1, "\n", 1);
}

void		print_link_part(t_lem_in *lemin)
{
	int		i;
	int		j;

	i = 0;
	while (i < lemin->num_of_rooms)
	{
		j = 0;
		while (j < lemin->num_of_rooms)
		{
			if (lemin->adjacency_matrix[i][j] && lemin->adjacency_matrix[j][i])
			{
				print_link(lemin->array_of_rooms[i]->name, lemin->array_of_rooms[j]->name);
				lemin->adjacency_matrix[i][j] = 0;
				lemin->adjacency_matrix[j][i] = 0;
			}
			j++;
		}
		i++;
	}
}

void		print_ant_farm(t_lem_in *lemin)
{
	
	ft_putnbr(lemin->num_of_ants);
	write(1, "\n", 1);
	print_room_part(lemin);
	print_link_part(lemin);	
}