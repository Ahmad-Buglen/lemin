/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 09:46:07 by bsausage          #+#    #+#             */
/*   Updated: 2020/09/01 12:03:51 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

static void	error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void		init_mlx(t_visual *ptr)
{
	if (!(ptr->mlx = mlx_init()))
		error("mlx init error");
	if (!(ptr->win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT,
						"Lem-in vizualizer by bsausage")))
		error("windows init error");
	if (!(ptr->img = mlx_new_image(ptr->mlx, IMG_W, IMG_H)))
		error("image init error");
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_per_pixel),
										&(ptr->size_line), &(ptr->endian));
}

// t_visual	*init_ptr(void)
// {
// 	t_visual	*ptr;

// 	if (!(ptr = (t_visual *)malloc(sizeof(t_visual))))
// 		error("init error");
// 	return (ptr);
// }
