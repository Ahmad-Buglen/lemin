/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:49:42 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/17 11:54:04 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <limits.h>

t_room		*room_create_elem(char *name, t_coords coords, t_lem_in *lemin)
{
	t_room	*room;

	if (!(room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	room->name = name;
	room->coords = coords;
	room->position = lemin->position;
	room->index = lemin->num_of_rooms;
	return (room);
}

t_room		*room_push_back(t_room **begin, char *name,\
							t_coords coords, t_lem_in *lemin)
{
	t_room	*room;

	if (!*begin)
	{
		*begin = room_create_elem(name, coords, lemin);
		return (*begin);
	}
	room = *begin;
	while (room->next)
	{
		if (ft_strequ(room->name, name) ||
			(room->coords.x == coords.x && room->coords.y == coords.y))
			close_program(lemin, "duplacate of name or coords");
		room = room->next;
	}
	if (ft_strequ(room->name, name) ||
			(room->coords.x == coords.x && room->coords.y == coords.y))
		close_program(lemin, "duplacate of name or coords");
	room->next = room_create_elem(name, coords, lemin);
	return (room->next);
}

void		add_to_hash_map(t_room **begin, t_room *room)
{
	t_room		*tmp;

	if (!*begin)
	{
		*begin = room;
		return ;
	}
	tmp = *begin;
	*begin = room;
	(*begin)->hash_next = tmp;
}

t_path		*create_path_elem(t_lem_in *lemin, char *name, int index)
{
	t_path		*elem;

	elem = NULL;
	if (!(elem = (t_path*)ft_memalloc(sizeof(t_path))))
		return (NULL);
	if (!(elem->name = ft_strdup(name)))
		close_program(lemin, "malloc error");
	elem->status = EMPTY;
	elem->index = index;
	elem->next = NULL;
	return (elem);
}

void		add_elem_to_path(t_lem_in *lemin, t_path **path,\
							char *name, int index)
{
	t_path	*tmp;

	if (!path)
		return ;
	if (*path == NULL)
		*path = create_path_elem(lemin, name, index);
	else
	{
		tmp = *path;
		*path = create_path_elem(lemin, name, index);
		(*path)->next = tmp;
	}
}
