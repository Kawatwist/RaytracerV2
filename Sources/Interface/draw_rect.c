/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 17:57:20 by anboilea          #+#    #+#             */
/*   Updated: 2020/06/22 19:15:21 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "rt.h"

void	draw_rect(t_data *ptr, SDL_Rect dst, unsigned int color)
{
	int			pitch;
	void		*pxl;

    int         x;
    int         y;

	SDL_LockTexture(ptr->menu.background, NULL, &pxl, &pitch);

    y = dst.y;
    while (y <= dst.y + dst.h)
    {
        x = dst.x;
        while (x <= dst.w + dst.x)
        {
            ((int *)pxl)[x + (y * 200)] = color;
            x++;
        }
        y++;
    }

    SDL_UnlockTexture(ptr->menu.background);
}