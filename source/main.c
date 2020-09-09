/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:41:56 by bsausage          #+#    #+#             */
/*   Updated: 2020/09/09 13:49:59 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"
#include <stdio.h>
#include "vis.h"

// int		calc_bfs_level(t_lem_in *lemin)
// {
// 	unsigned int		i;
// 	unsigned int		j;
// 	int					level;
	
// 	i = lemin->start_index;
// 	list_push_back(&lemin->queue_begin, &lemin->queue_end, lemin->array_of_rooms[i]->room);
// 	while (lemin->queue_begin)
// 	{
// 		j = 0;
// 		i = lemin->queue_begin->room->index;
// 		level = lemin->array_of_rooms[i]->room->level + 1;
// 		while ((int)j < lemin->num_of_rooms)
// 		{
// 			if (lemin->adjacency_matrix[i][j])
// 			{
// 				if (lemin->array_of_rooms[j]->room->level < 0)
// 				{
// 					lemin->array_of_rooms[j]->room->level = level;
// 					list_push_back(&lemin->queue_begin, &lemin->queue_end, lemin->array_of_rooms[j]->room);
// 				}
// 			}
// 			j++;
// 		}
// 		remove_begin_list(&lemin->queue_begin, &lemin->queue_end);
// 	}
// 	return (0);
// }

// void	find_path(t_lem_in *lemin, t_lem_list **path)
// {
// 	t_room		*room;
// 	int			i;
// 	int			j;

// 	i = lemin->end_index;
// 	room = lemin->array_of_rooms[i]->room;
// 	list_push_front(path, NULL, room);
// 	//lemin->path_len[0]++;
// 	while(lemin->array_of_rooms[i]->room->level)
// 	{
// 		j = 0;
// 		while (j < lemin->num_of_rooms)
// 		{
// 			if (lemin->adjacency_matrix[i][j])
// 			{
// 				if (lemin->array_of_rooms[j]->room->level < room->level)
// 					room = lemin->array_of_rooms[j]->room;
// 			}
// 			j++;
// 		}
// 		list_push_front(path, NULL, room);
// 		//lemin->path_len[0]++;
// 		i = room->index;
// 	}
// }

void	find_path_2(t_lem_in *lemin, t_lem_list **path, t_route *route)
{
	t_room		*room;
	int			i;
	int			j;
	int			n = route->size - 1;

	while (n >= 0)
	{
		room = lemin->array_of_rooms[route->elem[n]->index]->room;
		list_push_front(path, NULL, room);
		n--;
	}
}

void	print_solution(t_lem_in *lemin)
{
	int		i;
	int		k;
	
	printf("\n");
	k = 0;
	while (lemin->array_of_ants[lemin->num_of_ants - 1]->next)
	{
		i = 0;
		while (i < lemin->num_of_ants)
		{
			if (lemin->array_of_ants[i] && lemin->array_of_ants[i]->room->index != (int)lemin->end_index && lemin->array_of_ants[i]->next->room->status == EMPTY)
			{
				lemin->array_of_ants[i]->room->status = EMPTY;
				lemin->array_of_ants[i] = lemin->array_of_ants[i]->next;
				if (lemin->array_of_ants[i]->room->index != (int)lemin->end_index)
					lemin->array_of_ants[i]->room->status = NOT_EMPTY;
				printf("L%d-%s ", i + 1, lemin->array_of_ants[i]->room->name);
			}
			i++;
		}
		printf("\b\n");
		k++;
	}
}

// void	init_array_of_ants_2(t_lem_in *lemin, t_route *route)
// {
// 	int		i;

// 	i = 0;
// 	lemin->array_of_ants = (t_route**)malloc(sizeof(t_route*) * lemin->num_of_ants);
// 	while (i < lemin->num_of_ants)
// 		lemin->array_of_ants[i++] = route;
// }

// void	print_solution_2(t_lem_in *lemin)
// {
// 	int		i;
// 	int		k;
// 	int		n = 0;
// 	t_node	*tmp = lemin->array_of_ants[0]->elem;
	
// 	k = 0;
// 	while (lemin->array_of_ants[lemin->num_of_ants - 1]->elem[n]->type != END)
// 	{
// 		i = 0;
// 		while (i < lemin->num_of_ants)
// 		{
// 			if (lemin->array_of_ants[i] && lemin->array_of_ants[i]->elem[n]->type != END && lemin->array_of_ants[i]->elem[n+1]->status == EMPTY)
// 			{
// 				lemin->array_of_ants[i]->elem[n]->status = EMPTY;
// 				lemin->array_of_ants[i] = lemin->array_of_ants[i]->elem[n++];
// 				if (lemin->array_of_ants[i]->elem[n]->index != (int)lemin->end_index)
// 					lemin->array_of_ants[i]->elem[n]->status = NOT_EMPTY;
// 				printf("L%d-%s ", i + 1, lemin->array_of_ants[i]->elem[n]->name);
// 			}
// 			i++;
// 		}
// 		printf("\b\n");
// 		k++;
// 	}
// }

void	init_array_of_ants(t_lem_in *lemin)
{
	int		i;

	i = 0;
	lemin->array_of_ants = (t_lem_list**)malloc(sizeof(t_lem_list*) * lemin->num_of_ants);
	while (i < lemin->num_of_ants)
		lemin->array_of_ants[i++] = lemin->path;
}


// int		main(int argc, char **argv)
// {
// 	t_lem_in	lemin;
	
// 	lemin.vis_flag = (argc == 2 && ft_strequ("-v", argv[1])) ? 1 : 0;
// 	init_values(&lemin);
// 	get_num_of_ants(&lemin);
// 	get_rooms(&lemin);
// 	if (!lemin.start_flag || !lemin.end_flag)
// 		close_program(&lemin, "no start or end room");		
// 	if (!(lemin.adjacency_matrix = init_adjacency_matrix(lemin.num_of_rooms)))
// 		close_program(&lemin, "init_adjacency_matrix error");
// 	if (!(lemin.array_of_rooms = init_array_of_rooms(&lemin)))
// 		close_program(&lemin, "init array of rooms error");
// 	if (!get_links(&lemin))
// 		close_program(&lemin, "link error");
// 	if (!lemin.array_of_rooms[lemin.start_index] || !lemin.array_of_rooms[lemin.end_index])
// 		close_program(&lemin, "start or/and end room is/are without links");
	

// 	calc_bfs_level(&lemin);
// 	find_path(&lemin, &lemin.path);
// 	//find_path(&lemin, &lemin.path2);
// 	init_array_of_ants(&lemin);
// 	printf("num of ants = %d\n", lemin.num_of_ants);
// 	print_room_list(lemin.room_list);
// 	print_hash_map(lemin.hash_map);
// 	print_array_of_rooms(&lemin);
// 	print_adjacency_matrix(&lemin);
// 	printf("num of rooms - %d\n", lemin.num_of_rooms);
// 	print_solution(&lemin);
// 	if (lemin.vis_flag)
// 		draw(&lemin);
// 	free_all(&lemin);
// 	return (0);
// }
