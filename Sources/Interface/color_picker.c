/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:05:33 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/10 01:16:09 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			switchcolor(int h)
{
	int		color;

	if (h > 0 && h < 121)
	{
		color = (h * 255 / 120) << 8;
		color += (255 - ((color & 0xFF00) >> 8));
	}
	else if (h < 241)
	{
		color = ((h - 120) * 255 / 120) << 16;
		color += (255 - ((color & 0xFF0000) >> 16)) << 8;
	}
	else
	{
		color = ((h - 240) * 255) / 120;
		color += (255 - (color & 0xFF)) << 16;
	}
	return (color);
}

static int		find_color_chroma(int i, int j)
{
	int		pos;
	float	dot;

	dot = (dot_product(normalize(sub_vec(fill_vec(i, j, 0),
		fill_vec(150, 150, 0))), fill_vec(0, -1, 0)) + 1.0) * 90.0;
	pos = (i <= 150 ? 360 - dot : dot);
	pos += 45;
	pos < 360 ? pos += 360 : 0;
	pos > 360 ? pos -= 360 : 0;
	return (switchcolor(pos));
}

static int		hue_2(int color, float value)
{
	value *= 2.0;
	color = (((color & 0xFF) * value) >= 255 ? 255 :
		((color & 0xFF) * value)) +
		((((color & 0xFF00) >> 8) * value) >= 255 ? 255 << 8 :
			((int)(((color & 0xFF00) >> 8) * value) << 8)) +
		((((color & 0xFF0000) >> 16) * value) >= 255 ? 255 << 16 :
			((int)(((color & 0xFF0000) >> 16) * value) << 16));
	value = (value - 1.0) * 255.0;
	if ((color & 0xFF) < value)
		color = ((int)value) + (color & 0xFFFF00);
	if (((color & 0xFF00) >> 8) < value)
		color = (((int)value) << 8) + (color & 0xFF00FF);
	if (((color & 0xFF0000) >> 16) < value)
		color = (((int)value) << 16) + (color & 0xFFFF);
	return (color);
}

static int		hue(t_data *data, int color)
{
	float	value;

	value = data->screen.preview.slider[0].value;
	if (value == 0.5)
		return (color);
	else if (value < 0.5)
	{
		value *= 2.0;
		color = (((color & 0xFF) * value) < 0 ? 0 :
			((color & 0xFF) * value)) + ((((color & 0xFF00) >> 8) *
				value) < 0 ? 0 : ((int)(((color & 0xFF00) >> 8) *
				value) << 8)) + ((((color & 0xFF0000) >> 16) *
				value) < 0 ? 0 : ((int)(((color & 0xFF0000) >> 16) *
				value) << 16));
	}
	else
		color = hue_2(color, value);
	return (color);
}

float			find_slider_pos(int color)
{
	float value;

	value = (color & 0xFF) + ((color & 0xFF00) >> 8) +
		((color & 0xFF0000) >> 16);
	return ((value / 3.0) / 255.0);
}

void			color_picker(t_data *data)
{
	double	distance;
	int		radius;
	int		radius_min;
	int		i;
	int		j;

	distance = 0.0;
	radius = 120; // 150
	radius_min = 85; // 115 de base avant modif
	i = 0;
	j = 0;
	while (i++ <= 2 * radius)
	{
		j = 0;
		while (j++ <= 2 * radius)
		{
			distance = sqrt((double)(i - radius) * (i - radius) +
									(j - radius) * (j - radius));
			if (distance < radius && distance > radius_min)
				((int *)data->screen.preview.pxl)[30 + i + (( 30 + j) * 300)] =
					hue(data, find_color_chroma(i, j));
		}
	}
}
