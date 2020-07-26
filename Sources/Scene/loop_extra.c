/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:03:43 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/26 18:52:39 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_button(t_data *data, int x, int y, t_case c)
{
	SDL_Rect		dst;
	unsigned int	color;

	color = 0;
	dst.x = x;
	dst.y = y;
	draw_button_ext_0(data, &dst, color);
	if (c.i > 1)
	{
		draw_separation(data, dst, c.i, x);
		dst.w = 30 / c.i;
	}
	else
		dst.w = 30;
	if (c.val == 1)
		draw_button_ext_1(data, dst, color);
	else if (c.val == 2)
		draw_button_ext_2(data, dst, color);
	else if (c.val == 3)
		draw_button_ext_3(data, dst, color);
}

int			texture_on_screen_ext(t_data *data, SDL_Rect dst)
{
	void		*pxl;
	int			pitch;

	interface_grey(data);
	show_button(data);
	draw_nbvideo_bg(data);
	SDL_LockTexture(data->screen.preview.texture, NULL,
		&data->screen.preview.pxl, &data->window.pitch);
	SDL_LockTexture(data->menu.background, NULL, &pxl, &pitch);
	ft_memcpy(&(pxl[((int)(data->window.y * 0.55 + 50)) * 300 * 4]),
	data->screen.preview.pxl, 300 * 300 * 4);
	SDL_UnlockTexture(data->menu.background);
	SDL_UnlockTexture(data->screen.preview.texture);
	new_rt(data);
	draw_outline(data);
	SDL_RenderCopy(data->window.rend, data->menu.background, NULL, &dst);
	video_settings(data);
	data->font.str = ft_strdup("Nb Image");
	print_text(data, 10, 4, 20);
	show_txt(data);
	click_button(data);
	return (0);
}

int			texture_on_screen(t_data *data)
{
	SDL_Rect	pos;
	SDL_Rect	dst;

	pos.x = 200;
	pos.y = 30;
	pos.w = data->window.x - 200;
	pos.h = data->window.y - 30;
	SDL_SetRenderDrawColor(data->window.rend, 33, 33, 33, 0);
	//SDL_SetRenderDrawColor(data->window.rend, 0xcc, 0xcc, 0xcc, 0xcc);
	SDL_RenderClear(data->window.rend);
	SDL_RenderCopy(data->window.rend, data->window.txt, &pos, &pos);
	set_background(data);
	draw_title_background(data);
	dst.x = 0;
	dst.y = 0;
	dst.w = 300;
	dst.h = data->window.y;
	texture_on_screen_ext(data, dst);
	return (0);
}

static int	looping(t_data *data)
{
	int		err;

	resize(data);
	SDL_LockTexture(data->window.txt, NULL,
			&data->window.pxl, &data->window.pitch);
	if ((err = start_thread(data)))
		return (err);
	generate_perlin(data);
	post_processing(data);
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	SDL_UnlockTexture(data->window.txt);
	return (0);
}

int			sub_loop(t_data *data)
{
	int err;

	
	if ((data->flag.refresh || data->flag.asked ||
	data->flag.video) && !data->flag.show)
	{
		if ((err = looping(data)) != 0)
			return (err);
		data->flag.asked = 0;
		data->flag.video ? data->flag.video -= 1 : 0;
		if (data->flag.icon == 1)
			real_time_icon(data);
	}
	else
		SDL_Delay(64);
	if (data->hud.flag_hud)
		texture_on_screen(data);
	else
		SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
	SDL_RenderPresent(data->window.rend);
	return (0);
}
