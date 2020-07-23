/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switchcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 23:47:49 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/23 21:26:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			switchcolor_ext(int h, int color)
{
	color = 0xFF00FF;
	if (h < 300)
		color -= ((int)((300 - h) * 4.25));
	else if (h > 300)
		color -= ((int)((h - 300) * 4.25) << 16);
	return (color);
}

int			switchcolor(int h)
{
	int		color;

	color = 0;
	if (h > 0 && h < 121)
	{
		color = 0xFFFF;
		if (h < 60)
			color -= ((int)((60 - h) * 4.25) << 8);
		else if (h > 60)
			color -= ((int)((h - 60) * 4.25) & 0xFF);
	}
	else if (h < 241)
	{
		color = 0xFFFF00;
		if (h < 180)
			color -= ((int)((180 - h) * 4.25) << 16);
		else if (h > 180)
			color -= ((int)((h - 180) * 4.25) << 8);
	}
	else
		color = switchcolor_ext(h, color);
	return (color);
}
