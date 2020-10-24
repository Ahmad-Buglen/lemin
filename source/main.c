/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:41:56 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/24 14:34:55 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"

void			lemin_init(t_lem_in *const lemin)
{
	t_route		route;

	lemin->max_route_count = (lemin->start->con_size < lemin->end->con_size) ?
								lemin->start->con_size : lemin->end->con_size;
	if (!(lemin->fifo = (t_room **)ft_memalloc(sizeof(t_room *) *\
						lemin->num_of_rooms)))
		ft_exit_lemin("The system did not allocate memory");
	if (!(lemin->routes = (t_route **)ft_memalloc(sizeof(t_route *) *
																ROUTE_SIZE)))
		ft_exit_lemin("The system did not allocate memory");
	if (!(lemin->route = (t_bool *)ft_memalloc(sizeof(t_bool) *\
						(lemin->num_of_rooms + 1))))
		ft_exit_lemin("The system did not allocate memory");
	route_clean(lemin);
	lemin->fifo[0] = lemin->start;
	ft_bzero(&route, sizeof(t_route));
	route.elem[route.size++] = lemin->fifo[0];
	lemin->start->route = route_copy(&route);
}

void			data_parsing(t_lem_in *const lemin)
{
	lemin->start_index = -1;
	lemin->end_index = -1;
	get_num_of_ants(lemin);
	get_rooms(lemin);
	if (!lemin->start_flag || !lemin->end_flag)
		close_program(lemin, "no start or end room");
	if (!(lemin->adjacency_matrix = init_adjacency_matrix(lemin->num_of_rooms)))
		close_program(lemin, "init_adjacency_matrix error");
	lemin->array_of_rooms = init_array_of_rooms(lemin);
	get_links(lemin);
	if (!check_start_end_links(lemin))
		ft_exit_lemin("start or/and end room is/are without links");
}

void			parse_flags(t_lem_in *lemin, int argc, char **argv)
{
	if (argc == 2 && ft_strequ("-p", argv[1]))
		lemin->p_flag = 1;
	else
	{
		write(2, "Usage:\n", 8);
		write(2, "\t./lem-in [-p] < map\n", 22);
		exit(1);
	}
}

int				main(int argc, char **argv)
{
	t_lem_in	lemin;

	ft_bzero(&lemin, sizeof(lemin));
	if (argc > 1)
		parse_flags(&lemin, argc, argv);
	data_parsing(&lemin);
	if (lemin.adjacency_matrix[lemin.start_index][lemin.end_index])
	{
		print_ant_farm(&lemin);
		print_start_end_solution(&lemin);
	}
	else
	{
		lemin_init(&lemin);
		if (lemin.num_of_rooms < BIG)
			recur_search(&lemin);
		else
			bhandari_search(&lemin);
		get_num_of_paths(&lemin);
		ants_distribution(&lemin);
		print_ant_farm(&lemin);
		print_solution(&lemin);
	}
	free_all(&lemin);
	return (1);
}
