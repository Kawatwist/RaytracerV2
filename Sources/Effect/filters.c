/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:09:24 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/01 02:09:31 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	post_processing(t_data *data)
{
	(void)data;
	int		i;
	int		color;
	int		tr;
	int		tg;
	int		tb;

	i = -1;
	if (data->flag.filter == 1)
	{
		//fonction noir et blanc
		while (++i < data->window.x * data->window.y)
		{
			color = (((unsigned char *)data->window.pxl)[(i << 2) + 1] +
					((unsigned char *)data->window.pxl)[(i << 2) + 2] +
					((unsigned char *)data->window.pxl)[(i << 2) + 3]) / 3;
			((unsigned int *)data->window.pxl)[i] = (0xFF << 24) + (color << 16) + (color << 8) + (color << 0);
		}
	}
	else if (data->flag.filter == 2)
	{
		//fonction sepia
		while (++i < data->window.x * data->window.y)
		{
			tr = ((0.393 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) + (0.769 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) + (0.189 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
			tg = ((0.349 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) + (0.686 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) + (0.168 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
			tb = ((0.272 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) + (0.534 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) + (0.131 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
			if (tr > 255)
				tr = 255;
			if (tg > 255)
				tg = 255;
			if (tb > 255)
				tb = 255;
			((unsigned int *)data->window.pxl)[i] = ((0xFF << 24) + (tr << 16) + (tg << 8) + (tb << 0));
		}
	}
	else if (data->flag.filter == 3)
	{
		// fonction cartoon
		while (++i < data->window.x * data->window.y)
		{
			tr = (((unsigned char *)data->window.pxl)[(i << 2) + 2] - ((((unsigned char *)data->window.pxl)[(i << 2) + 2] % 60)));
			tg = (((unsigned char *)data->window.pxl)[(i << 2) + 1] - ((((unsigned char *)data->window.pxl)[(i << 2) + 1] % 60)));
			tb = (((unsigned char *)data->window.pxl)[(i << 2) + 0] - ((((unsigned char *)data->window.pxl)[(i << 2) + 0] % 60)));
			if (tr < 0)
				tr = 0;
			if (tg < 0)
				tg = 0;
			if (tb < 0)
				tb = 0;
			if (tr > 255)
				tr = 255;
			if (tg > 255)
				tg = 255;
			if (tb > 255)
				tb = 255;
			((unsigned int *)data->window.pxl)[i] = ((0xFF << 24) + (tr << 16) + (tg << 8) + tb);
		}
	}
	return (0);
}
