/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:48:50 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/10 11:32:05 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"

void	get_names(t_lem_in *lemin, int *room_1, int *room_2)
{
	char	*end;
	char	*room_name;
	size_t	name_len;

	end = NULL;
	if (!(end = ft_strchr(lemin->line, '-')))
		close_program(lemin, "link error");
	name_len = end - lemin->line;
	if (!(room_name = ft_strsub(lemin->line, 0, name_len)))
		close_program(lemin, "malloc error");
	if ((*room_1 = find_room_index(lemin, room_name)) < 0)
		close_program(lemin, "links list contains non-existing room");
	ft_memdel((void**)&room_name);
	end++;
	if (!(room_name = ft_strdup(end)))
		close_program(lemin, "malloc error");
	if ((*room_2 = find_room_index(lemin, room_name)) < 0)
		close_program(lemin, "links list contains non-existing room");
	ft_memdel((void**)&room_name);
}

int		parse_links_line(t_lem_in *lemin)
{
	int		room_1;
	int		room_2;

	get_names(lemin, &room_1, &room_2);
	if (lemin->adjacency_matrix[room_1][room_2] == 1 ||\
		lemin->adjacency_matrix[room_2][room_1] == 1)
		close_program(lemin, "Error: link duplicate");
	lemin->adjacency_matrix[room_1][room_2] = 1;
	lemin->adjacency_matrix[room_2][room_1] = 1;
	ft_memdel((void**)&lemin->line);
	connect_node(lemin, lemin->array_of_rooms[room_1],\
				lemin->array_of_rooms[room_2]);
	return (room_1 < 0 || room_1 < 0 ? 0 : 1);
}

int		get_links(t_lem_in *lemin)
{
	int		gnl;

	if (!parse_links_line(lemin))
		close_program(lemin, "link error");
	while ((gnl = get_next_line(0, &lemin->line) > 0))
	{
		if (lemin->line[0] == '\0')
			close_program(lemin, "empty line");
		if (ft_strequ(lemin->line, "##start") ||\
			ft_strequ(lemin->line, "##end"))
			close_program(lemin, "##start or ##end command in links list");
		if (lemin->line[0] == '#')
		{
			ft_memdel((void**)&lemin->line);
			continue;
		}
		if (!parse_links_line(lemin))
		{
			ft_memdel((void**)&lemin->line);
			close_program(lemin, "link error");
		}
	}
	if (gnl < 0)
		close_program(lemin, "link error");
	return (1);
}

int		check_start_end_links(t_lem_in *lemin)
{
	int		i;
	int		start;
	int		end;

	start = 0;
	end = 0;
	i = 0;
	while (i < lemin->num_of_rooms)
	{
		if (lemin->adjacency_matrix[lemin->start_index][i++])
		{
			start = 1;
			break ;
		}
	}
	i = 0;
	while (i < lemin->num_of_rooms)
	{
		if (lemin->adjacency_matrix[lemin->end_index][i++])
		{
			end = 1;
			break ;
		}
	}
	return (start * end);
}
