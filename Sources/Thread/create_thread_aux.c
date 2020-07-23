/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:10:29 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/23 18:44:49 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		thread_loading_bar(t_data *data)
{
	SDL_Rect	load;
	int			i;

	i = -1;
	while (++i < 4)
	{
		load.x = 300 + (i * 25);
		load.y = data->window.y - 35 -
			(((t_thread *)data->thread)[i].loading * 4);
		load.w = 20;
		load.h = ((t_thread *)data->thread)[i].loading * 4;
		SDL_SetRenderDrawColor(data->window.rend, (25 -
			((t_thread *)data->thread)[i].loading) *
				10, (((t_thread *)data->thread)[i].loading)
				* 10, 0, 0);
		SDL_RenderFillRect(data->window.rend, &load);
	}
	SDL_SetRenderDrawColor(data->window.rend, 0, 0, 0, 0);
}

void			loading_bar(t_data *data)
{
	SDL_Rect	load;

	SDL_SetRenderDrawColor(data->window.rend,
		(100 - data->loading) * 2.5, (data->loading) * 2.5, 0, 0);
	load.x = 300;
	load.y = data->window.y - 30;
	load.w = data->loading;
	load.h = 20;
	SDL_RenderFillRect(data->window.rend, &load);
	thread_loading_bar(data);
	SDL_SetRenderDrawColor(data->window.rend, 0, 0, 0, 0);
}

void			setup_rect(t_data *data, SDL_Rect *og,
	SDL_Rect *screen, SDL_Rect *lolz)
{
	og->x = (data->window.x) - 150;
	og->y = (data->window.y) - 150;
	og->w = 100;
	og->h = 100;
	screen->x = 0;
	screen->y = 0;
	screen->w = (data->window.x);
	screen->h = (data->window.y);
	lolz->x = (data->window.x) - 200;
	lolz->y = (data->window.y) - 200;
	lolz->w = 200;
	lolz->h = 200;
}
