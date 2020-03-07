/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_book.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:48:38 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/28 17:19:54 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		front_page(t_data *data, SDL_Rect *pos)
{
	pos->x = (data->window.x / 500.0) * 38.9;
	pos->y = (data->window.y / 500.0) * 427.8;
	pos->w = (data->window.x / 500.0) * 27.8;
	pos->h = (data->window.y / 500.0) * 27.8;
	if ((hitbox(data->input.x, data->input.y, pos)) == 1 &&
	data->screen.page == 1)
		if (data->screen.page == 1)
			data->screen.page = 0;
}

static void		page_turned(t_data *data, SDL_Rect *pos)
{
	pos->x = (data->window.x / 500.0) * 427.8;
	pos->y = (data->window.y / 500.0) * 427.8;
	pos->w = (data->window.x / 500.0) * 27.8;
	pos->h = (data->window.y / 500.0) * 27.8;
	if ((hitbox(data->input.x, data->input.y, pos)) == 1 ||
	data->screen.page == 1)
	{
		if (data->screen.page == 0)
			data->screen.page = 1;
		if (data->screen.page == 1)
		{
			SDL_RenderCopy(data->window.rend, data->screen.scenetxt[3],
				NULL, NULL);
			third_page(data);
			fourth_page(data);
			if ((data->input.button = (int)SDL_GetMouseState(&data->input.x,
			&data->input.y)) == 1 && data->screen.page == 1)
				front_page(data, pos);
			if (key_check(*data, SDL_SCANCODE_LEFT))
				data->screen.page--;
		}
		data->screen.interface = INFO;
	}
}

void			info_book(t_data *data, SDL_Rect *pos)
{
	if (data->screen.page == 0)
	{
		first_page(data);
		second_page(data);
		if (key_check(*data, SDL_SCANCODE_RIGHT))
			data->screen.page++;
	}
	printf("[%d]|| [%d]\n", data->input.x, data->input.y);
	if ((data->input.button = (int)SDL_GetMouseState(&data->input.x,
	&data->input.y)) == 1 || data->screen.page == 1)
		page_turned(data, pos);
}
