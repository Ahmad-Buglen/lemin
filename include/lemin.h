

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdio.h>

# define SIZE 1024
# define BUFF 1000000


typedef struct  s_coordinates
{
	int         x;
	int         y;
}               t_coordinates;


typedef struct		s_node
{
	char			*name;
	t_coordinates	coordinates;
	int				busy;
	int				pass;
	struct s_node	*next;
	int				con_size;
	struct s_node	**connections;
}					t_node;



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