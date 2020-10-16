/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:45:58 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/16 11:29:49 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"
#include <limits.h>

void		check_room_name_coords_line(char **name, t_coords *coords,\
									t_lem_in *lemin)
{
	char	*end;
	size_t	name_len;
	long	coord;

	end = ft_strchr(lemin->line, ' ');
	name_len = end - lemin->line;
	if (++end && !ft_isdigit(*end) && *end != '-')
		close_program(lemin, "wrong room's coords");
	if (!(*name = ft_strsub(lemin->line, 0, name_len)))
		close_program(lemin, "malloc error");
	if (ft_strchr(*name, '-'))
		close_program(lemin, "room's name can not contain -");
	if ((coord = ft_strtol(end, &end)) > INT_MAX || coord < INT_MIN)
		close_program(lemin, "coords overflow");
	coords->x = coord;
	if (++end && !ft_isdigit(*end) && *end != '-')
		close_program(lemin, "wrong room's coords");
	if ((coord = ft_strtol(end, &end)) > INT_MAX || coord < INT_MIN)
		close_program(lemin, "room's coords overflow");
	coords->y = coord;
	if (*end)
		close_program(lemin, "wrong room's coords");
	if ((lemin->start_flag && lemin->position == START) ||\
		(lemin->end_flag && lemin->position == END))
		close_program(lemin, "more than one start or end room");
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
	list_push_front(&lemin->hash_map[calc_hash_index(name)], NULL, room);
	if (lemin->position == START && !lemin->start_flag)
	{
		lemin->start_flag = 1;
		lemin->start_index = lemin->num_of_rooms;
		lemin->start = room;
	}
	if (lemin->position == END && !lemin->end_flag)
	{
		lemin->end_flag = 1;
		lemin->end_index = lemin->num_of_rooms;
		lemin->end = room;
	}
	lemin->position = MIDDLE;
	lemin->num_of_rooms++;
}

static int	cycle_body(t_lem_in *lemin)
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
				return (0);
		}
	}
	if (lemin->line[0] == '#' && lemin->line[1] == '#')
	{
		if (!check_command_line(lemin))
			close_program(lemin, "command error");
	}
	ft_memdel((void**)&lemin->line);
	return (1);
}

void		get_rooms(t_lem_in *lemin)
{
	int		gnl;

	while ((gnl = get_next_line(0, &lemin->line)))
	{
		lemin->line_num++;
		if (!cycle_body(lemin))
			return ;
	}
	if (gnl <= 0)
		close_program(lemin, "no link part in the file");
}

int			find_room_index(t_lem_in *lemin, char *room_name)
{
	t_lem_list			*room_list;
	unsigned int		hash_index;

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
