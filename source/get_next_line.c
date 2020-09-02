/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:38:43 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/20 12:38:44 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		read_from_str(char **line, char **str)
{
	size_t	i;
	char	*tmp;

	i = ft_strchr(*str, '\n') - *str;
	(*str)[i] = '\0';
	if (!(*line = ft_strdup(*str)))
		return (-1);
	if (!(tmp = ft_strdup(&(*str)[i + 1])))
		return (-1);
	ft_memdel((void**)str);
	if (!(*str = ft_strdup(tmp)))
		return (-1);
	ft_memdel((void**)&tmp);
	return (1);
}

static char		*add_buff(int fd, char **str, int *ret)
{
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	*ret = read(fd, buf, BUFF_SIZE);
	buf[*ret] = '\0';
	tmp = ft_strdup(*str);
	ft_memdel((void**)str);
	*str = ft_strjoin(tmp, buf);
	ft_memdel((void**)&tmp);
	return (*str);
}

int				get_last_line(char **line, char **str)
{
	if (!(*line = ft_strdup(*str)))
		return (-1);
	ft_memdel((void**)str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int				ret;
	static char		*str[FD_MAXSET];

	ret = 1;
	if (!line || fd < 0 || fd >= FD_MAXSET || BUFF_SIZE < 1 ||
		read(fd, NULL, 0) < 0)
		return (-1);
	while (ret > 0)
	{
		if (!str[fd])
		{
			if (!(str[fd] = ft_strnew(0)))
				return (-1);
		}
		if (ft_strchr(str[fd], '\n'))
			return (read_from_str(line, &str[fd]));
		if (!(str[fd] = add_buff(fd, &str[fd], &ret)))
			return (-1);
	}
	if (!ret && *str[fd])
		return (get_last_line(line, &str[fd]));
	if (!ret)
		ft_memdel((void**)&str[fd]);
	return (0);
}
