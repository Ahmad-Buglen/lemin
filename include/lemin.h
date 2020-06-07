

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdio.h>

# define SIZE 1024
# define BUFF 1000000



typedef struct		s_node
{
	char			*name;
	int				coor_x;
	int				coor_y;
	int				busy;
	int				pass;
	struct s_node	*next;
	int				con_size;
	struct s_node	*connections[];
}					t_node;


// typedef struct  s_box
// {
// 	int         number;
// 	int         index;
// 	int			bool;
// 	int			weight;
// }               t_box;

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