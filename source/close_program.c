/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:09:47 by bsausage          #+#    #+#             */
/*   Updated: 2020/10/17 17:13:19 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include <errno.h>

void		ft_exit_lemin(char *const message)
{
	ft_putendl(message);
	exit(1);
}

void		close_program(t_lem_in *lemin, char *error_msg)
{
	if (!errno && lemin->line_num)
	{
		ft_putstr_fd("Error (line ", 1);
		ft_putnbr_fd(lemin->line_num, 1);
		ft_putstr_fd("): ", 1);
		ft_putendl_fd(error_msg, 1);
	}
	else if (!errno)
		ft_putendl_fd(error_msg, 1);
	else
		perror("Error");
	exit(1);
}
