/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_parsing_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:51:50 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/24 12:57:01 by bsausage         ###   ########.fr       */
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
	if (*line == '0' && ft_strlen(line) > 1)
		return (0);
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (0);
		line++;
	}
	return (1);
}

static int	check_first_line(t_lem_in *lemin)
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
		close_program(lemin, "wrong num of ants line");
	return (0);
}

void		get_num_of_ants(t_lem_in *lemin)
{
	long	num;
	char	*end;
	int		gnl;

	while ((gnl = get_next_line(0, &lemin->line)))
	{
		if (gnl <= 0)
			close_program(lemin, "empty file");
		lemin->line_num++;
		add_line_to_farm_list(lemin);
		if (!(check_first_line(lemin)))
			break ;
	}
	if (gnl <= 0)
		ft_exit_lemin("empty file or wrong data");
	end = lemin->line;
	num = ft_strtol(end, &end);
	if (num <= 0 || num > INT_MAX)
		close_program(lemin, "num of ants is <= 0 or > INT_MAX");
	lemin->num_of_ants = num;
	ft_memdel((void**)&lemin->line);
}

void		check_command_line(t_lem_in *lemin)
{
	if (lemin->position == START || lemin->position == END)
		if (!ft_strequ("##start", lemin->line) &&
			!ft_strequ("##end", lemin->line))
			close_program(lemin, "no room after ##start or ##end");
	if (ft_strequ("##start", lemin->line))
	{
		lemin->position = START;
		lemin->start_flag++;
	}
	if (ft_strequ("##end", lemin->line))
	{
		lemin->position = END;
		lemin->end_flag++;
	}
	if (lemin->start_flag > 1)
		close_program(lemin, "more than one ##start command");
	if (lemin->end_flag > 1)
		close_program(lemin, "more than one ##end command");
}
