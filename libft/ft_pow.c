/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:27 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/23 18:52:15 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_pow(unsigned long long number, int grade)
{
	unsigned long long	rezult;

	rezult = 1;
	while (grade)
	{
		if (grade & 1)
			rezult *= number;
		number *= number;
		grade >>= 1;
	}
	return (rezult);
}
