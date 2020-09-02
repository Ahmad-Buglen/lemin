/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 11:58:12 by Alkor             #+#    #+#             */
/*   Updated: 2020/09/02 18:48:22 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"
#include <stdio.h>
#include "vis.h"

int		turn_off(void *param)
{
	(void)param;
	exit(0);
}

int		key_press(int key, t_visual *ptr)
{
	if (key == 53)
		turn_off(ptr);
	return (0);
}

void	hooks(t_visual *ptr)
{
	mlx_hook(ptr->win, 2, 0, key_press, ptr);
	mlx_hook(ptr->win, 17, 0, turn_off, ptr);
	mlx_loop(ptr->mlx);
}

void		put_pixel(t_visual *ptr, int x, int y, int color)
{
	int		i;

	if (x >= 0 && x < IMG_W && y >= 0 && y < IMG_H)
	{
		i = (x * ptr->bits_per_pixel / 8) + (y * ptr->size_line);
		ptr->data_addr[i] = blue(color);
		ptr->data_addr[++i] = green(color);
		ptr->data_addr[++i] = red(color);
	}
}

void	draw_room(t_visual *ptr, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < ptr->room_len)
	{
		j = 0;
		while (j < ptr->room_len)
		{
			put_pixel(ptr, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_ants_farm(t_lem_in *lemin, t_visual *ptr)
{
	int		i;

	i = 0;
	while (i < lemin->num_of_rooms)
	{
		draw_room(ptr, lemin->array_of_rooms[i]->room->coords.x * (ptr->room_len + 5),
					   lemin->array_of_rooms[i]->room->coords.y * (ptr->room_len + 5), WHITE);
		i++;
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 0, 0);
}

void	color_path(t_lem_in *lemin, t_visual *ptr)
{
	t_lem_list	*path;
	int			color;

	path = lemin->path;
	while (path)
	{
		if (path->room->position == START)
			color = RED;
		if (path->room->position == END)
			color = BLUE;
		if (path->room->position == MIDDLE)
			color = GREEN;
		draw_room(ptr, path->room->coords.x * (ptr->room_len + 2),
					   path->room->coords.y * (ptr->room_len + 2), color);
		path = path->next;
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 0, 0);
}

static void		draw_line_values(t_coords *d, t_coords *s, t_coords dot1, t_coords dot2)
{
	d->x = abs(dot2.x - dot1.x);
	d->y = abs(dot2.y - dot1.y);
	s->x = dot1.x < dot2.x ? 1 : -1;
	s->y = dot1.y < dot2.y ? 1 : -1;
}

static void		draw_line(t_visual *ptr, t_coords dot1, t_coords dot2, int color)
{
	t_coords	delta;
	t_coords	sign;
	t_coords	current;
	int		error[2];

	current = dot1;
	draw_line_values(&delta, &sign, dot1, dot2);
	error[0] = delta.x - delta.y;
	while (current.x != dot2.x || current.y != dot2.y)
	{
		put_pixel(ptr, current.x, current.y, color);
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
		{
			error[0] -= delta.y;
			current.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			current.y += sign.y;
		}
	}
}

void	draw_links(t_lem_in *lemin, t_visual *ptr)
{
	int		i;
	int		j;
	t_coords	start;
	t_coords	end;

	i = 0;
	while (i < lemin->num_of_rooms)
	{
		j = 0;
		while (j < lemin->num_of_rooms)
		{
			if (lemin->adjacency_matrix[i][j])
			{
				start.x = lemin->array_of_rooms[i]->room->coords.x * (ptr->room_len + 2) + 2;
				start.y = lemin->array_of_rooms[i]->room->coords.y * (ptr->room_len + 2) + 2;
				end.x = lemin->array_of_rooms[j]->room->coords.x * (ptr->room_len + 2) + 2;
				end.y = lemin->array_of_rooms[j]->room->coords.y * (ptr->room_len + 2) + 2;
				draw_line(ptr, start, end, WHITE);
			}
			j++;
		}
		i++;
	}
}


int		draw(t_lem_in *lemin)
{
	t_visual	ptr;

	printf("vis_flag = %d\n", lemin->vis_flag);
	init_mlx(&ptr);
	ptr.room_len = 5;
	draw_ants_farm(lemin, &ptr);
	draw_links(lemin, &ptr);
	color_path(lemin, &ptr);
	//color_start_end(lemin, &ptr);
	hooks(&ptr);
	return (0);
}
