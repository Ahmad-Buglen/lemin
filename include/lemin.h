/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:27:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/17 18:28:36 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h>

# define VISIT		7
# define NO_VISIT	0
# define BIG_INT 	1111111111
# define ROUTE_SIZE 2048
# define HASH_SIZE	10000
# define BIG		1500

typedef enum		e_bool
{
	false,
	true
}					t_bool;

typedef struct		s_coords
{
	int				x;
	int				y;
}					t_coords;

typedef enum
{
	EMPTY,
	NOT_EMPTY
}	t_status;

typedef struct		s_route
{
	int				size;
	struct s_room	*elem[ROUTE_SIZE];
	int				weight;
	int				unique;
}					t_route;

typedef enum
{
	DEFAULT,
	START,
	MIDDLE,
	END
}	t_position;

typedef struct		s_room
{
	char			*name;
	t_coords		coords;
	t_position		position;
	int				index;
	int				pass;
	int				type;
	int				con_size;
	int				weight;
	t_route			*route;
	struct s_room	*next;
	struct s_room	*hash_next;
	struct s_room	**connections;
}					t_room;

typedef struct		s_path
{
	char			*name;
	t_status		status;
	int				index;
	struct s_path	*next;
}					t_path;

typedef struct		s_farm
{
	char			*line;
	struct s_farm	*next;
}					t_farm;

typedef struct		s_lem_in
{
	char			*line;
	t_farm			*farm_list;
	int				line_num;
	t_room			*room_list;
	t_room			*hash_map[HASH_SIZE];
	int				**adjacency_matrix;
	t_room			**array_of_rooms;
	t_path			**array_of_ants;
	t_path			**paths;
	t_position		position;
	int				num_of_ants;
	int				num_of_rooms;
	int				start_flag;
	int				end_flag;
	t_room			*start;
	t_room			*end;
	unsigned int	start_index;
	unsigned int	end_index;
	int				max_route_count;
	t_room			**fifo;
	t_route			**routes;
	int				route_count;
	t_bool			*route;
}					t_lem_in;

t_route				*route_copy(t_route *const route);
void				route_put(t_lem_in *const lemin, t_route *const route);
void				route_clean(t_lem_in *const lemin);
void				route_mark(t_lem_in *const lemin, t_route *const route);
t_bool				route_check(t_lem_in *const lemin, t_route *const route);

/*
**	init and destroy
*/

void				connect_add(t_room *const node1, t_room *const node2);
void				connect_del(t_room *const node1, t_room *const node2);
void				connect_node(t_room *const room1, t_room *const room2);
void				lemin_routes_destroy(t_lem_in *const lemin);
void				routes_destroy(t_route **routes);
void				ft_exit_lemin(char *const message);

/*
**	recursive search
*/

int					node_include(t_route *const route, const int index);
int					*dublicate_map(t_lem_in *const lemin);
int					*copy_map(int *const map_src, const int node_len);
void				recur_route(t_route *const route, t_room *const room,
								int *const map, t_lem_in *const lemin);
void				recur_search(t_lem_in *const lemin);
void				route_sort(t_lem_in *const lemin);
void				routes_complete(t_route **const routes,
								t_lem_in *const lemin, const int number);
int					unique_search(t_route *const *const routes,
								t_lem_in *const lemin);

/*
**	bhandari search
*/

int					fifo_include(t_room *const *const fifo,
								t_room *const node);
void				dijkstra_setup(t_lem_in *const lemin);
void				dijkstra_search(t_room **const fifo, int i, int n);
void				bhandari_search(t_lem_in *const lemin);
int					route_flow(t_lem_in *const lemin, const int route_count);
int					route_steps(t_lem_in *const lemin);
void				route_inverse(t_route *const route);
int					connection_include(t_room *const node1,
										t_room *const node2);
void				connection_restore(t_room *const node1,
										t_room *const node2);
void				route_recovery(t_lem_in *const lemin);

/*
**	init/malloc
*/

int					**init_adjacency_matrix(int n);
t_room				**init_array_of_rooms(t_lem_in *lemin);
void				init_array_of_ants(t_lem_in *lemin);
void				init_path_array(t_lem_in *lemin);
t_room				*room_create_elem(char *name, t_coords coords,
												t_lem_in *lemin);
t_room				*room_push_back(t_room **begin, char *name,
									t_coords coords, t_lem_in *lemin);
void				create_path(t_lem_in *lemin, t_path **path,
											t_route *route);
void				add_elem_to_path(t_lem_in *lemin, t_path **path,
									char *name, int index);
void				add_to_hash_map(t_room **begin, t_room *room);

/*
**	rooms
*/

void				get_rooms(t_lem_in *lemin);
unsigned int		calc_hash_index(char *str);
int					find_room_index(t_lem_in *lemin, char *room_name);

/*
**	links
*/

void				get_links(t_lem_in *lemin);

/*
**	other parsing funcs
*/

long				ft_strtol(const char *str, char **end);
void				add_line_to_farm_list(t_lem_in *lemin);
int					check_num_of_ants_line(char *line);
void				get_num_of_ants(t_lem_in *lemin);
void				check_command_line(t_lem_in *lemin);
int					check_start_end_links(t_lem_in *lemin);

/*
**	free_functions
*/

void				free_all(t_lem_in *lemin);
void				close_program(t_lem_in *lemin, char *error_msg);

/*
**	solution functions
*/

void				print_ant_farm(t_lem_in *lemin);
void				print_solution(t_lem_in *lemin);
void				flow_distribution(t_lem_in *lemin);
void				start_end_solution(t_lem_in *lemin);

/*
**	helper functions
**	contains forbidden functons
**	aren't used in final project's version
*/

void				print_room_list(t_room *room_list);
void				print_hash_map(t_room *hash_map[HASH_SIZE]);
void				print_adjacency_matrix(t_lem_in *lemin);
void				print_array_of_rooms(t_lem_in *lemin);
void				print_routes(t_lem_in *lemin);
void				check_routes(t_lem_in *lemin);

#endif
