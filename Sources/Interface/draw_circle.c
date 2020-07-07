/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:06:58 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/07 21:33:10 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_circle	setup_circle(t_point pos, int color, long int radius,
		void *pxl)
{
	t_circle circle;

	circle.pxl = pxl;
	circle.x = pos.x;
	circle.y = pos.y;
	circle.color = color;
	circle.r_inside = ((Uint64)radius) & 0xFFFFFFFF;
	circle.r_outside = ((Uint64)radius) >> 32;
	return (circle);
}

void		draw_circle(t_circle circle)
{
	int		i;
	int		j;
	float	distance;

	i = 0;
	while (i++ <= 2 * circle.r_outside)
	{
		j = 0;
		while (j++ <= 2 * circle.r_outside)
		{
			distance = sqrt((double)(i - circle.r_outside)
				* (i - circle.r_outside) + (j - circle.r_outside)
				* (j - circle.r_outside));
			if (distance < circle.r_outside && distance > circle.r_inside)
				((int *)circle.pxl)[i + ((j + circle.y) * 300)
					+ circle.x] = circle.color;
		}
	}
}
