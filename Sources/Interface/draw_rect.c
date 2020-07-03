/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 22:21:35 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/03 23:36:52 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "rt.h"

void	draw_rect(t_data *ptr, SDL_Rect dst, unsigned int color)
{
	int			pitch;
	void		*pxl;
	int			x;
	int			y;

	SDL_LockTexture(ptr->menu.background, NULL, &pxl, &pitch);
	y = dst.y;
	while (y < dst.y + dst.h)
	{
		x = dst.x;
		while (x < dst.w + dst.x)
		{
			((int *)pxl)[x + (y * 300)] = color;
			x++;
		}
		y++;
	}
	SDL_UnlockTexture(ptr->menu.background);
}
