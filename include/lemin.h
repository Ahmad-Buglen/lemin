/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 17:12:23 by dphyliss          #+#    #+#             */
/*   Updated: 2020/09/07 17:12:23 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <stdio.h>

// # define START_A 1
// # define STANDART 2
// # define END_A 3
# define VISIT 7
# define NO_VISIT 0
# define BIG_INT 1111111111

# define ROUTE_SIZE 2048
#define HASH_SIZE	10000
#define BIG			1500


typedef enum			e_bool
{
	false = 0,
	true = 1
}						t_bool;

typedef struct  s_coords
{
	int         x;
	int         y;
}               t_coords;

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
	//struct s_room	*next_a;
	
}					t_room;

typedef struct			s_path
{
    char				*name;
	t_status			status;
	int					index;
	struct s_path		*next;
}						t_path;

typedef struct      s_lem_in
{
	char			*line;
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
	t_route			*buff;
}					t_lem_in;

/*
**	init/malloc functions
*/

void				lemin_routes_destroy(t_lem_in *lemin);
void				routes_destroy(t_route **routes);
void				init_min(t_lem_in *lemin);
void 				init_middle(t_lem_in *lemin);
void 				connect_node(t_lem_in *lemin, t_room *room1, t_room *room2);
void 				node_add(t_lem_in *lemin, char *name, t_coords coordinates, int type);

int					**init_adjacency_matrix(int n);
t_room				**init_array_of_rooms(t_lem_in *lemin);
void				init_array_of_ants(t_lem_in *lemin);
void				init_path_array(t_lem_in *lemin);
t_room				*room_create_elem(char *name, t_coords coords, t_lem_in *lemin);
t_room				*room_push_back(t_room **begin, char *name, t_coords coords, t_lem_in *lemin);
void				create_path(t_lem_in *lemin, t_path **path, t_route *route);
void				add_elem_to_path(t_lem_in *lemin, t_path **path, char *name, int index);
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

#endif
