/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ant_farm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:45:27 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/10 11:02:35 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

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
		if (room->index == (int)lemin->start_index)
		{
			ft_putendl("##start");
			print_room(room);
		}
		else if (room->index == (int)lemin->end_index)
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
				print_link(lemin->array_of_rooms[i]->name,\
							lemin->array_of_rooms[j]->name);
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
