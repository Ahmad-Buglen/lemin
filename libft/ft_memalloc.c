/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:47:11 by dphyliss          #+#    #+#             */
/*   Updated: 2020/10/17 14:47:10 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*point;

	if ((0 == size) ||
			(!(point = (void *)malloc(size))))
		return (NULL);
	ft_memset(point, 0, size);
	return ((void *)point);
}
