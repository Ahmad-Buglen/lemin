/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 13:56:21 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/16 14:55:29 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemin.h"

unsigned int		calc_hash_index(char *str)
{
	int				i;
	int				tmp;
	unsigned int	hash_index;

	hash_index = 0;
	while (*str)
	{
		i = 0;
		tmp = 0;
		while (*str && i < 4)
		{
			tmp |= (unsigned int)*str;
			if (++i != 4)
				tmp = tmp << 8;
			str++;
		}
		hash_index += tmp;
	}
	return (hash_index % HASH_SIZE);
}

