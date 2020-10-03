/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:45:58 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/03 11:41:08 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"
#include <limits.h>


// void 				connect_node(t_lem_in *lemin, char *name1, char *name2);

void	check_room_name_coords_line(char **name, t_coords *coords, t_lem_in *lemin)
{
	char	*end;
	size_t	name_len;
	long	x;
	long	y;

	end = ft_strchr(lemin->line, ' ');
	name_len = end - lemin->line;
	if (++end && !ft_isdigit(*end) && *end != '-')
		close_program(lemin, "error: room's coords should contaons only digits");
	if (!(*name = ft_strsub(lemin->line, 0, name_len)))
		close_program(lemin, "malloc error");
	if (ft_strchr(*name, '-'))
		close_program(lemin, "Error: room's name can nor contain -");
	if ((x = ft_strtol(end, &end)) > INT_MAX || x < INT_MIN)
		close_program(lemin, "coords overflow");
	if (++end && !ft_isdigit(*end) && *end != '-')
		close_program(lemin, "error: room's coords should contaons only digits");
	if ((y = ft_strtol(end, &end)) > INT_MAX || y < INT_MIN)
		close_program(lemin, "error: room's coords should contaons only digits");
	if (*end)
		close_program(lemin, "error: room's coords should contaons only digits");
	if ((lemin->start_flag && lemin->position == START) || (lemin->end_flag && lemin->position == END))
		close_program(lemin, "error: more than one start or end room");
	coords->x = x;
	coords->y = y;
}


void		get_room_name_coords(t_lem_in *lemin)
{
	t_coords		coords;
	t_room			*room;
	char			*name;

	name = NULL;
	check_room_name_coords_line(&name, &coords, lemin);
	if (!(room = room_push_back(&lemin->room_list, name, coords, lemin)))
		close_program(lemin, "malloc error");
	
	node_add(lemin,  name,  coords, lemin->position); //dphyliss' function
									//последний аргумент идет из структуры bsausage,
									//числовые значения соответвуют значениям dphyliss

	list_push_front(&lemin->hash_map[calc_hash_index(name)], NULL, room);
	if (lemin->position == START && !lemin->start_flag)
	{
		lemin->start_flag = 1;
		lemin->start_index = lemin->num_of_rooms;
	}
	if (lemin->position == END && !lemin->end_flag)
	{
		lemin->end_flag = 1;
		lemin->end_index = lemin->num_of_rooms;
	}
	lemin->position = MIDDLE;
	lemin->num_of_rooms++;
}

void	get_rooms(t_lem_in *lemin)
{
	int		gnl;
	
	while ((gnl = get_next_line(0, &lemin->line)))
	{
		if (lemin->line[0] == 'L')
			close_program(lemin, "Error: line starts with L character");
		if (lemin->line[0] == '\0')
			close_program(lemin, "Error: lempty line");
		if (lemin->line[0] != '#')
		{
			if (ft_strchr(lemin->line, ' '))
				get_room_name_coords(lemin);
			else
			{
				if (!lemin->num_of_rooms)
					close_program(lemin, "Error: no rooms");
				else
					return ;
			}
		}	
		if (lemin->line[0] == '#' && lemin->line[1] == '#')
		{
			if (!check_command_line(lemin))
				close_program(lemin, "command error");
		}
		ft_memdel((void**)&lemin->line);
	}
	if (gnl <= 0)
		close_program(lemin, "no link part in the file");
}


int		find_room_index(t_lem_in *lemin, char *room_name)
{
	t_lem_list			*room_list;
	unsigned int	hash_index;

	hash_index = calc_hash_index(room_name);
	room_list = lemin->hash_map[hash_index];
	while (room_list)
	{
		if (ft_strequ(room_list->room->name, room_name))
			return (room_list->room->index);
		room_list = room_list->next;
	}
	return (-1);
}
