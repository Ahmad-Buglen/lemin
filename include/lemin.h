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

# define START_A 1
# define STANDART 2
# define END_A 3
# define VISIT 7
# define NO_VISIT 0
# define BIG_INT 1111111111

# define ROUTE_SIZE 2500
# define CYCLE_SIZE 2



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
	struct s_node	*elem[ROUTE_SIZE];
}					t_route;

typedef struct		s_node
{
	char			*name;
	t_coords		coordinates;
	int				index;
	int				busy;
	int				pass;
	int				type;
	int				con_size;
	int				weight;
	t_route			*route;
	struct s_node	**connections;
	struct s_node	*next;
}					t_node;

typedef struct		s_map
{
	char			*name;
	int				pass;
	struct s_map	*next;
}					t_map;

typedef struct      s_lemin
{
	t_node			**nodes;
	int				max_route_count;
	t_node			*start;
	t_node			*end;
	int 			node_len;
	t_node			**fifo_nodes;
	t_route			**routes;
	int				route_count;
}					t_lemin;


// typedef struct  s_ps
// {
//     t_box       a[SIZE];
//     t_box       b[SIZE];
// 	int         len_a;
// 	int         len_b;
// 	int			oper[BUFF];
// 	int			len_o;
// }               t_ps;



#define HASH_SIZE	10000

// typedef struct		s_coords
// {
//     int				x;
//     int				y;
// }					t_coords;

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
	int				index;
	int				level;
    t_coords		coords;
	t_position		position;
	t_status		status;
	int				flag;
	struct s_room	*next;
}					t_room;

typedef struct			s_lem_list
{
    t_room				*room;
	struct s_lem_list	*next;
}						t_lem_list;

typedef struct      s_lem_in
{
	char			*line;
	t_room			*room_list;
	t_lem_list		*hash_map[HASH_SIZE];
	int				**adjacency_matrix;
	t_lem_list		**array_of_rooms;
	t_lem_list		*path;
	//t_lem_list		*path2;
	//t_lem_list		*path3;
	t_lem_list		*queue_begin;
	t_lem_list		*queue_end;
	t_lem_list		**array_of_ants;
	t_position		position;
	int				path_len[100];
	int				num_of_ants;
	int				num_of_rooms;
	int				start_flag;
	int				end_flag;
	unsigned int	start_index;
	unsigned int	end_index;
	int				vis_flag;
}					t_lem_in;

//init/malloc functions


void				init_min(t_node **nodes);
void 				init_middle(t_node **nodes);

void				connect_node(t_node **nodes, char *name1, char *name2);
void 				node_add(t_node **nodes, char *name, t_coords coordinates, int type);
long				ft_strtol(const char *str, char **end);
t_room				*room_create_elem(char *name, t_coords coords, t_lem_in *lemin);
t_room				*room_push_back(t_room **begin, char *name, t_coords coords, t_lem_in *lemin);
void				add_new_room(t_lem_list **begin_list, char *name, t_coords coords, t_lem_in *lemin);
void				free_room_list(t_room **begin_list);
unsigned int		calc_hash_index(char *str);
void				init_values(t_lem_in *lemin);
void				assign_null_hash_map(t_lem_in *lemim);
int					**init_adjacency_matrix(int n);
t_lem_list			**init_array_of_rooms(t_lem_in *lemin);

int					list_push_front(t_lem_list **begin_list, t_lem_list **end_list, t_room *data);
int					list_push_back(t_lem_list **begin_list, t_lem_list **end_list, t_room *data);
void				remove_begin_list(t_lem_list **begin_list, t_lem_list **end_list);

void				queue_insert(t_lem_in *lemin, t_room *room);
void				queue_remove(t_lem_in *lemin);
void				queue_clear(t_lem_in *lemin);
void				push_to_stack(t_lem_in *lemin, t_room *room);

//rooms

void				get_room_name_coords(t_lem_in *lemin, t_node **nodes);
void				get_rooms(t_lem_in *lemin, t_node **nodes);
int					find_room_index(t_lem_in *lemin, char *room_name);

//links

int					get_links(t_lem_in *lemin, t_node **nodes);
int					parse_links_line(t_lem_in *lemin, t_node **nodes);

//other parsing funcs

int					check_num_of_ants_line(char *line);
void				get_num_of_ants(t_lem_in *lemin);
int					check_command_line(t_lem_in *lemin);

//free_functions

// void				free_adjacency_matrix(t_lem_in *lemin);
// void				free_room_list(t_room **begin_list);
// void				free_hash_map(t_lem_in *lemin);
void				free_all(t_lem_in *lemin);
void				close_program(t_lem_in *lemin, char *error_msg);

//print				functions

void				print_ant_farm(t_lem_in *lemin);

//tmp_functions

void				print_room_list(t_room *room_list);
void				print_hash_map(t_lem_list *hash_map[HASH_SIZE]);
void				print_adjacency_matrix(t_lem_in *lemin);
void				print_array_of_rooms(t_lem_in *lemin);

void				init_array_of_ants(t_lem_in *lemin);
void				find_path_2(t_lem_in *lemin, t_lem_list **path, t_route *route);
void				print_solution(t_lem_in *lemin);

#endif
