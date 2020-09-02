/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:49:42 by bsausage          #+#    #+#             */
/*   Updated: 2020/09/02 18:47:14 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <limits.h>

t_room		*room_create_elem(char *name, t_coords coords, t_lem_in *lemin)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->name = name;
	room->coords = coords;
	room->position = lemin->position;
	room->index = lemin->num_of_rooms;
	room->status = EMPTY;
	room->next = NULL;
	room->flag = 0;
	if (lemin->position == MIDDLE)
		room->level = -1;
	else
		room->level = lemin->position == START ? 0 : INT_MAX;
	return (room);
}

t_room		*room_push_back(t_room **begin, char *name, t_coords coords, t_lem_in *lemin)
{
	//this functions also checks duplacates of rooms' names and coords
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
		close_program(lemin, "Error: duplacate of name or coords");
		room = room->next;
	}
	if (ft_strequ(room->name, name) ||
			(room->coords.x == coords.x && room->coords.y == coords.y))
		close_program(lemin, "Error: duplacate of name or coords");
	room->next = room_create_elem(name, coords, lemin);
	return (room->next);
}

t_lem_list		*list_elem_create(t_room *data)
{
	t_lem_list		*tmp;

	if (!(tmp = (t_lem_list*)malloc(sizeof(t_lem_list))))
		return (NULL);
	tmp->room = data;
	tmp->next = NULL;
	return (tmp);
}

int			list_push_front(t_lem_list **begin_list, t_lem_list **end_list, t_room *data)
{
	t_lem_list		*tmp;

	if (!(tmp = list_elem_create(data)))
		return (0);
	if (!*begin_list)
	{
		*begin_list = tmp;
		if (end_list)
			*end_list = tmp;
	}
	else
	{
		tmp->next = *begin_list;
		*begin_list = tmp;
	}
	return (1);
}

int			list_push_back(t_lem_list **begin_list, t_lem_list **end_list, t_room *data)
{
	t_lem_list		*tmp;

	if (!(tmp = list_elem_create(data)))
		return (0);
	if (!*begin_list)
	{
		*begin_list = tmp;
		*end_list = tmp;
	}
	else
	{
		(*end_list)->next = tmp;
		*end_list = (*end_list)->next;
	}
	return (1);
}

void			remove_begin_list(t_lem_list **begin_list, t_lem_list **end_list)
{
	t_lem_list		*tmp;
	
	if (!begin_list)
		return ;
	if (*begin_list == *end_list)
		ft_memdel((void**)begin_list);
	else
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		ft_memdel((void**)&tmp);
	}
}
