

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdio.h>

# define SIZE 1024
# define BUFF 1000000
# define START 1
# define STANDART 2
# define END 3
# define VISIT 7
# define NO_VISIT 0


# define ROUTE_SIZE 100


typedef struct  s_coordinates
{
	int         x;
	int         y;
}               t_coordinates;

typedef struct		s_route
{
	int				size;
	struct s_node	*elem[ROUTE_SIZE];
}					t_route;

typedef struct		s_node
{
	char			*name;
	t_coordinates	coordinates;
	int				index;
	int				busy;
	int				pass;
	int				type;
	int				con_size;
	struct s_node	**connections;
	struct s_node	*next;
}					t_node;

typedef struct		s_map
{
	char			*name;
	int				pass;
	struct s_map	*next;
}					t_map;



// typedef struct  s_ps
// {
//     t_box       a[SIZE];
//     t_box       b[SIZE];
// 	int         len_a;
// 	int         len_b;
// 	int			oper[BUFF];
// 	int			len_o;
// }               t_ps;


#endif