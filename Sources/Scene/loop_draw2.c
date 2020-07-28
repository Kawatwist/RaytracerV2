/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_draw2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:46:25 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/26 18:20:25 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	draw_separation(t_data *data, SDL_Rect dst, int nb, int x)
{
	int tmp;

	tmp = 30;
	if (nb > 1)
		nb = tmp / nb;
	dst.x = x;
	dst.w = 1;
	dst.y -= 3;
	dst.h = 33;
	while (tmp > 0)
	{
		if (dst.x != x)
			draw_rect(data, dst, 0xc80a20);
		tmp -= nb;
		dst.x = dst.x + nb;
	}
}

void	draw_button_ext_0(t_data *data, SDL_Rect *dst, unsigned int color)
{
	dst->w = 30;
	dst->h = 30;
	dst->y += 3;
	color = 0xf0451d;
	draw_rect(data, *dst, color);
	dst->y += 30;
	dst->h = 3;
	draw_rect(data, *dst, 0xc80a20);
	dst->h = 33;
	dst->y -= 27;
	dst->h -= 3;
}

void	draw_button_ext_1(t_data *data, SDL_Rect dst, unsigned int color)
{
	color = 0x29cb75;
	draw_rect(data, dst, color);
	dst.y -= 3;
	dst.h = 3;
	color = 0x212121;
	draw_rect(data, dst, color);
}

void	draw_button_ext_2(t_data *data, SDL_Rect dst, unsigned int color)
{
	dst.x += 10;
	color = 0xf6ff00;
	draw_rect(data, dst, color);
	dst.h = 3;
	dst.y -= 3;
	color = 0x212121;
	draw_rect(data, dst, color);
}

void	draw_button_ext_3(t_data *data, SDL_Rect dst, unsigned int color)
{
	dst.x += 20;
	color = 0xffbb00;
	draw_rect(data, dst, color);
	dst.h = 3;
	dst.y -= 3;
	color = 0x212121;
	draw_rect(data, dst, color);
}
