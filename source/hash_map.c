/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 13:56:21 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/17 20:08:16 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"

unsigned int	calc_hash_index(char *str)
{
	int				i;
	int				tmp;
	unsigned int	hash_index;

	hash_index = 0;
	while (*str)
	{
		i = 0;
		tmp = 0;
		while (*str && i < 4)
		{
			tmp |= (unsigned int)*str;
			if (++i != 4)
				tmp = tmp << 8;
			str++;
		}
		hash_index += tmp;
	}
	return (hash_index % HASH_SIZE);
}

int				find_room_index(t_lem_in *lemin, char *room_name)
{
	t_room				*room_list;
	unsigned int		hash_index;

	hash_index = calc_hash_index(room_name);
	room_list = lemin->hash_map[hash_index];
	while (room_list)
	{
		if (ft_strequ(room_list->name, room_name))
			return (room_list->index);
		room_list = room_list->hash_next;
	}
	return (-1);
}
