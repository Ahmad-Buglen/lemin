/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:18:06 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/27 14:18:51 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_count_p(unsigned long long number, const int base)
{
	int				count;

	count = 1;
	while (number / base)
	{
		number /= base;
		count++;
	}
	return (count);
}
