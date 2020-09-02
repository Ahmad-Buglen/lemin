/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:48:50 by bsausage          #+#    #+#             */
/*   Updated: 2020/09/02 19:54:36 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"

int		parse_links_line(t_lem_in *lemin, t_node **nodes)
{
	char	*end;
	char	*room_name1;
	char	*room_name2;
	size_t	name_len;
	int		room_1;
	int		room_2;

	end = NULL;
	if (!(end = ft_strchr(lemin->line, '-')))
		close_program(lemin, "link error");
	name_len = end - lemin->line;
	if (!(room_name1 = ft_strsub(lemin->line, 0, name_len)))
		close_program(lemin, "malloc error");
	if ((room_1 = find_room_index(lemin, room_name1)) < 0)
		close_program(lemin, "links list contains non-existing room");
	// ft_memdel((void**)&room_name1);
	end++;
	if (!(room_name2 = ft_strdup(end)))
		close_program(lemin, "malloc error");
	if ((room_2 = find_room_index(lemin, room_name2)) < 0)
		close_program(lemin, "links list contains non-existing room");
	// ft_memdel((void**)&room_name2);
	if (lemin->adjacency_matrix[room_1][room_2] == 1 || lemin->adjacency_matrix[room_2][room_1] == 1)
		close_program(lemin, "Error: link duplicate");
	lemin->adjacency_matrix[room_1][room_2] = 1;
	lemin->adjacency_matrix[room_2][room_1] = 1;
	ft_memdel((void**)&lemin->line);
	return (room_1 < 0 || room_1 < 0 ? 0 : 1);

	connect_node(nodes,  room_name1,  room_name2);
}

int		get_links(t_lem_in *lemin, t_node **nodes)
{
	int		gnl;
	
	if (!parse_links_line(lemin, nodes))
		return (0);
	while ((gnl = get_next_line(0, &lemin->line) > 0))
	{
		if (lemin->line[0] == '\0')
			close_program(lemin, "empty line");
		if (ft_strequ(lemin->line, "##start") || ft_strequ(lemin->line, "##end"))
			close_program(lemin, "##start or ##end command in links list");
		if (lemin->line[0] == '#')
		{
			ft_memdel((void**)&lemin->line);
			continue;
		}
		if (!parse_links_line(lemin, nodes))
		{
			ft_memdel((void**)&lemin->line);
			return (0);
		}
	}
	return (gnl == 0 ? 1 : 0);
}
