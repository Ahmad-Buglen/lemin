/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_parsing_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:51:50 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/10 11:21:56 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"
#include <limits.h>

int			check_num_of_ants_line(char *line)
{
	if (!*line)
		return (0);
	if (*line == '0')
		return (0);
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (0);
		line++;
	}
	return (1);
}

static int	cycle_body(t_lem_in *lemin)
{
	if (lemin->line[0] == '\0')
		close_program(lemin, "empty line");
	if (ft_strequ(lemin->line, "##start") ||\
		ft_strequ(lemin->line, "##end"))
		close_program(lemin, "map must starts with num of ants");
	if (lemin->line[0] == '#')
	{
		ft_memdel((void**)&lemin->line);
		return (1);
	}
	if (!check_num_of_ants_line(lemin->line))
		close_program(lemin, "error: wrong num of ants line");
	else
		return (0);
	return (1);
}

void		get_num_of_ants(t_lem_in *lemin)
{
	long	num;
	char	*end;
	int		gnl;

	while ((gnl = get_next_line(0, &lemin->line)))
	{
		if (!cycle_body(lemin))
			break ;
	}
	if (gnl <= 0)
		close_program(lemin, \
		"empty file or map doesn't contain rooms and link part");
	end = lemin->line;
	num = ft_strtol(end, &end);
	if (num <= 0 || num > INT_MAX)
		close_program(lemin, "error msg");
	lemin->num_of_ants = num;
	ft_memdel((void**)&lemin->line);
}

int			check_command_line(t_lem_in *lemin)
{
	if (lemin->start_flag && ft_strequ("start", lemin->line + 2))
		return (0);
	if (lemin->end_flag && ft_strequ("end", lemin->line + 2))
		return (0);
	if (!lemin->start_flag && ft_strequ("start", lemin->line + 2))
		lemin->position = START;
	if (!lemin->end_flag && ft_strequ("end", lemin->line + 2))
		lemin->position = END;
	return (1);
}

void		skip_line(t_lem_in *lemin)
{
	ft_memdel((void**)&lemin->line);
	get_next_line(0, &lemin->line);
}
