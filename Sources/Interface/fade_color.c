/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fade_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:08:36 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/10 01:25:39 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static int		lowest_value(int color)
{
	if ((color & 0xFF) < ((color & 0xFF00) >> 8) &&
		(color & 0xFF) < ((color & 0xFF0000) >> 16))
		return (color & 0xFF);
	if ((color & 0xFF) > ((color & 0xFF00) >> 8) &&
		((color & 0xFF00) >> 8) < ((color & 0xFF0000) >> 16))
		return ((color & 0xFF00) >> 8);
	return ((color & 0xFF0000) >> 16);
}

static int		highest_value(int color)
{
	if ((color & 0xFF) > ((color & 0xFF00) >> 8) &&
		(color & 0xFF) > ((color & 0xFF0000) >> 16))
		return (color & 0xFF);
	if ((color & 0xFF) < ((color & 0xFF00) >> 8) &&
		((color & 0xFF00) >> 8) > ((color & 0xFF0000) >> 16))
		return ((color & 0xFF00) >> 8);
	return ((color & 0xFF0000) >> 16);
}

static float	color_to_pos2(int color)
{
	float	theta;

	if (color & 0xFF00)
		theta = 240 - ((int)((((color & 0xFF00) >> 8) / 255.0) * 60));
	else if (color & 0xFF0000)
		theta = 240 + ((int)((((color & 0xFF0000) >> 16) / 255.0) * 60));
	else
		theta = 240;
	return (theta);
}

static float	color_to_pos3(int color)
{
	float	theta;

	if (color & 0xFF0000)
		theta = 120 - ((int)((((color & 0xFF0000) >> 16) / 255.0) * 60));
	else if (color & 0xFF)
		theta = 120 + ((int)((((color & 0xFF)) / 255.0) * 60));
	else
		theta = 120;
	return (theta);
}

static float	color_to_pos4(int new_color, int color, float theta)
{
	color = ((int)((float)(color & 0xFF) * (255.0 / new_color))) +
	((int)((float)((color & 0xFF00) >> 8) * (255.0 / new_color)) << 8) +
	((int)((float)((color & 0xFF0000) >> 16) * (255.0 / new_color)) << 16);
	if (((color & 0xFF) > ((color & 0xFF00) >> 8) &&
		(color & 0xFF) > ((color & 0xFF0000) >> 16)))
		theta = color_to_pos2(color);
	else if (((color & 0xFF00) >> 8) > ((color & 0xFF0000) >> 16))
		theta = color_to_pos3(color);
	else
	{
		if (color & 0xFF)
			theta = 360 - ((int)((((color & 0xFF)) / 255.0) * 60));
		else if (color & 0xFF00)
			theta = ((int)((((color & 0xFF00) >> 8) / 255.0) * 60));
		else
			theta = 0;
	}
	return (theta);
}

t_point			color_to_pos(int posx, int posy, int color)
{
	t_point	pos;
	float	theta;
	int		new_color;

	theta = 0;
	new_color = lowest_value(color);
	color = ((color & 0xFF) - new_color) + ((((color & 0xFF00) >> 8) -
		new_color) << 8) + ((((color & 0xFF0000) >> 16) - new_color) << 16);
	new_color = highest_value(color);
	if (!new_color)
		theta = 0;
	else
		theta = color_to_pos4(new_color, color, theta);
	pos.x = posx + (102 * cos(rad(theta - 120))) - (0x15 / 2);
	pos.y = posy + (102 * sin(rad(theta - 120))) - (0x15 / 2);
	return (pos);
}
