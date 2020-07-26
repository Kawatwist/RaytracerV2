/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:35:09 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/26 14:43:26 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_background(t_data *data)
{
	int			pitch;
	void		*pxl;

	SDL_LockTexture(data->menu.background, NULL, &pxl, &pitch);
	ft_memset(pxl, 33, 300 * data->window.y * 4);
	SDL_UnlockTexture(data->menu.background);
}

void	draw_outline(t_data *data)
{
	SDL_Rect	dst;

	dst.x = 299;
	dst.y = 30;
	dst.w = 1;
	dst.h = data->window.y - 30;
	draw_rect(data, dst, 0xffffff);
	dst.x = 0;
	draw_rect(data, dst, 0xffffff);
	dst.w = 300;
	dst.h = 1;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y - 1;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y * 0.55 - 1;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y - 51;
	draw_rect(data, dst, 0xffffff);
}

void	draw_outline_color(t_data *data)
{
	SDL_Rect	dst;

	dst.x = 20;
	dst.y = data->window.y * 0.55 + 180 - 10;
	dst.w = 160;
	dst.h = 20;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y * 0.55 + 210 - 10;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y * 0.55 + 240 - 10;
	draw_rect(data, dst, 0xffffff);
	dst.x = 21;
	dst.w = 159;
	dst.h = 19;
	dst.y = data->window.y * 0.55 + 181 - 10;
	draw_rect(data, dst, 0x3c3c3c);
	dst.y = data->window.y * 0.55 + 211 - 10;
	draw_rect(data, dst, 0x3c3c3c);
	dst.y = data->window.y * 0.55 + 241 - 10;
	draw_rect(data, dst, 0x3c3c3c);
}

void	draw_title_background(t_data *data)
{
	SDL_Rect	dst;

	dst.x = 0;
	dst.y = 31;
	dst.w = 300;
	dst.h = 50;
	draw_rect(data, dst, 0x1965a1);
	dst.x = 0;
	dst.y = data->window.y * 0.55;
	dst.w = 300;
	dst.h = 50;
	draw_rect(data, dst, 0x1965a1);

	dst.x = (data->screen.preview.select_section != 1) ? 0 : 150;
	dst.y = data->window.y - 50;
	dst.w = 150;
	dst.h = 50;
	draw_rect(data, dst, 0x1965a1);
}

void	draw_background_box(t_data *data, int y)
{
	SDL_Rect	dst;

	dst.x = 20;
	dst.y = y + 3;
	dst.w = 210;
	dst.h = 25;
	draw_rect(data, dst, 0x262626);
}
