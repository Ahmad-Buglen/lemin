/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cinstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:03 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/23 18:46:04 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cinstr(char const *const storage, char const *const desire)
{
	int	i;
	int	j;

	i = 0;
	while (storage[i])
	{
		j = 0;
		while (desire[j])
		{
			if (storage[i] == desire[j])
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}
