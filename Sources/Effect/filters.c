/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:09:24 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/16 16:20:32 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	filter_negatif(t_data *data, unsigned int i)
{
	while (++i < data->window.x * data->window.y)
		((unsigned int *)data->window.pxl)[i] *= -1;
}

static void	filter_cartoon(t_data *data, unsigned int i)
{
	int					tr;
	int					tg;
	int					tb;

	while (++i < data->window.x * data->window.y)
	{
		tr = (((unsigned char *)data->window.pxl)[(i << 2) + 2] -
			((((unsigned char *)data->window.pxl)[(i << 2) + 2] % 32)));
		tg = (((unsigned char *)data->window.pxl)[(i << 2) + 1] -
			((((unsigned char *)data->window.pxl)[(i << 2) + 1] % 32)));
		tb = (((unsigned char *)data->window.pxl)[(i << 2) + 0] -
			((((unsigned char *)data->window.pxl)[(i << 2) + 0] % 32)));
		((unsigned int *)data->window.pxl)[i] =
			((0xFF << 24) + (tr << 16) + (tg << 8) + tb);
	}
	i = -1;
	cartoon(data, i, tr, tg);
}

static void	filter_sepia(t_data *data, unsigned int i)
{
	int					tr;
	int					tg;
	int					tb;

	while (++i < data->window.x * data->window.y)
	{
		tr = ((0.393 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) +
		(0.769 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) +
		(0.189 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
		tg = ((0.349 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) +
		(0.686 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) +
		(0.168 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
		tb = ((0.272 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) +
		(0.534 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) +
		(0.131 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
		if (tr > 255)
			tr = 255;
		if (tg > 255)
			tg = 255;
		if (tb > 255)
			tb = 255;
		((unsigned int *)data->window.pxl)[i] =
			((0xFF << 24) + (tr << 16) + (tg << 8) + (tb << 0));
	}
}

static void	filter_grey(t_data *data, unsigned int i, int color)
{
	while (++i < data->window.x * data->window.y)
	{
		color = (((unsigned char *)data->window.pxl)[(i << 2) + 1] +
				((unsigned char *)data->window.pxl)[(i << 2) + 2] +
				((unsigned char *)data->window.pxl)[(i << 2) + 3]) / 3;
		((unsigned int *)data->window.pxl)[i] =
		(0xFF << 24) + (color << 16) + (color << 8) + (color << 0);
	}
}

int			post_processing(t_data *data)
{
	unsigned int		i;
	int					color;

	i = -1;
	color = 0;
	if (data->flag.filter == 1)
		filter_grey(data, i, color);
	else if (data->flag.filter == 2)
		filter_sepia(data, i);
	else if (data->flag.filter == 3)
		filter_cartoon(data, i);
	else if (data->flag.filter == 4)
		filter_negatif(data, i);
	return (0);
}
