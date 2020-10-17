/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 12:02:14 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/17 12:34:23 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

long			ft_strtol(const char *str, char **end)
{
	int						i;
	int						sign;
	unsigned long long		result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_is_space(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = str[i++] == '-' ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = result * 10 + (str[i++] - '0');
		if (sign > 0 && result >= (unsigned long long)LONG_MAX)
			return (LONG_MAX);
		if (sign < 0 && result >= (unsigned long long)LONG_MAX + 1)
			return (LONG_MIN);
	}
	if (end)
		*end = (char*)&str[i];
	return (result * sign);
}
