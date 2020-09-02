/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:25:25 by bsausage          #+#    #+#             */
/*   Updated: 2020/09/01 12:01:31 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		red(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int		green(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int		blue(int rgb)
{
	return (rgb & 0xFF);
}

int		rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
