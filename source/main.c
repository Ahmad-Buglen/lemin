/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:41:56 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/19 15:28:19 by dphyliss         ###   ########.fr       */
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
	get_num_of_ants(lemin);
	get_rooms(lemin);
	if (!lemin->start_flag || !lemin->end_flag)
		close_program(lemin, "no start or end room");
	if (!(lemin->adjacency_matrix = init_adjacency_matrix(lemin->num_of_rooms)))
		close_program(lemin, "init_adjacency_matrix error");
	lemin->array_of_rooms = init_array_of_rooms(lemin);
	get_links(lemin);
	if (!check_start_end_links(lemin))
	{
		lemin->line_num = 0;
		close_program(lemin, "start or/and end room is/are without links");
	}
}

int				main(void)
{
	t_lem_in	lemin;

	ft_bzero(&lemin, sizeof(lemin));
	lemin.start_index = -1;
	lemin.end_index = -1;
	data_parsing(&lemin);
	if (lemin.adjacency_matrix[lemin.start_index][lemin.end_index])
		start_end_solution(&lemin);
	else
	{
		lemin_init(&lemin);
		if (lemin.num_of_rooms < BIG)
			recur_search(&lemin);
		else
			bhandari_search(&lemin);
		init_path_array(&lemin);
		flow_distribution(&lemin);
	}
	print_ant_farm(&lemin);
	print_solution(&lemin);
	free_all(&lemin);
	return (1);
}
