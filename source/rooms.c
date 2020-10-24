/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:45:58 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/24 12:56:34 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"
#include <limits.h>

static int	check_ptr(char *end)
{
	int		i;

	i = 0;
	if (end[i] != ' ')
		return (0);
	i++;
	if (end[i] && ft_isdigit(end[i]))
		return (1);
	if (end[i] == '-')
		i++;
	if (end[i] && ft_isdigit(end[i]))
		return (1);
	return (0);
}

void		check_room_name_coords_line(char **name, t_coords *coords,\
									t_lem_in *lemin)
{
	char	*end;
	size_t	name_len;
	long	coord;

	end = ft_strchr(lemin->line, ' ');
	name_len = end - lemin->line;
	if (!(*name = ft_strsub(lemin->line, 0, name_len)))
		close_program(lemin, "malloc error");
	if (ft_strchr(*name, '-'))
		close_program(lemin, "room's name can not contain -");
	if (!check_ptr(end))
		close_program(lemin, "wrong room's coords");
	if ((coord = ft_strtol(end, &end)) > INT_MAX || coord < INT_MIN)
		close_program(lemin, "coords overflow");
	coords->x = coord;
	if (!check_ptr(end))
		close_program(lemin, "wrong room's coords");
	if ((coord = ft_strtol(end, &end)) > INT_MAX || coord < INT_MIN)
		close_program(lemin, "room's coords overflow");
	coords->y = coord;
	if (*end)
		close_program(lemin, "wrong room's coords");
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
	add_to_hash_map(&lemin->hash_map[calc_hash_index(name)], room);
	if (lemin->position == START)
	{
		lemin->start_index = lemin->num_of_rooms;
		lemin->start = room;
	}
	if (lemin->position == END)
	{
		lemin->end_index = lemin->num_of_rooms;
		lemin->end = room;
	}
	lemin->position = MIDDLE;
	lemin->num_of_rooms++;
}

static int	cycle_body(t_lem_in *lemin)
{
	if (lemin->line[0] == 'L')
		close_program(lemin, "line starts with L character");
	if (lemin->line[0] == '\0')
		close_program(lemin, "Empty line");
	if (lemin->line[0] != '#')
	{
		if (ft_strchr(lemin->line, ' '))
			get_room_name_coords(lemin);
		else if (!ft_strchr(lemin->line, '-'))
			close_program(lemin, "wrong room line");
		else
		{
			if (!lemin->num_of_rooms)
				close_program(lemin, "room part doesn't exist or wrong line");
			else
				return (0);
		}
	}
	if (lemin->line[0] == '#')
		check_command_line(lemin);
	ft_memdel((void**)&lemin->line);
	return (1);
}

void		get_rooms(t_lem_in *lemin)
{
	int		gnl;

	while ((gnl = get_next_line(0, &lemin->line)))
	{
		lemin->line_num++;
		add_line_to_farm_list(lemin);
		if (!cycle_body(lemin))
		{
			if (lemin->start_index == (unsigned int)-1 ||\
				lemin->end_index == (unsigned int)-1)
				close_program(lemin, "no start or end room");
			return ;
		}
	}
	if (gnl <= 0)
		close_program(lemin, "no link part in the file");
}
