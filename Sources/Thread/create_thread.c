/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/24 19:57:40 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static	t_point	find_dir(t_thread *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	return (ret);
}

static void		setup_rect(t_data *data, SDL_Rect *og, SDL_Rect *screen, SDL_Rect *lolz)
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

static void		loading_sc(t_data *data, int p)
{
	SDL_Rect	pos;
	SDL_Rect	og;
	SDL_Rect	screen;
	SDL_Rect	lolz;

	pos.x = (p % 6) * 100;
	pos.y = (p / 6) * 100;
	pos.w = 100;
	pos.h = 100;
	setup_rect(data, &og, &screen, &lolz);
	SDL_RenderClear(data->window.rend);
	if (data->flag.first == 0)
		SDL_RenderCopy(data->window.rend, data->load.loading, &screen, NULL);
	else
	{
		SDL_RenderCopy(data->window.rend, data->window.oldtxt, NULL, NULL);
		if (data->hud.flag_hud)
		{
			pics_on_screen(data);
			SDL_RenderCopy(data->window.rend, data->load.lolz, NULL, &lolz);
		}
	}
	SDL_RenderCopy(data->window.rend, data->load.load, &pos, &og);
	SDL_Delay(24);
	if (data->window.rend != NULL)
		SDL_RenderPresent(data->window.rend);
	SDL_Delay(24);
}

int				start_thread(t_data *data)
{
	Uint32			time;
	struct timespec	timeout;
	int				i;
	int				err;
	static int		pos = 0;

	i = -1;
	load_modif(data, data->thread);
	while (++i < 4)
	{
		((t_thread *)data->thread)[i].percent = data->percent;
		((t_thread *)data->thread)[i].bounce = data->bounce;
		((t_thread *)data->thread)[i].len = (data->window.x * data->window.y) >> 2;
		((t_thread *)data->thread)[i].pos = ((t_thread *)data->thread)[i].len * i;
		((t_thread *)data->thread)[i].pxl = &(((unsigned char *)data->window.pxl)[(((t_thread *)data->thread)[i].len * i) << 2]);
		if ((err = pthread_create(&((t_thread*)data->thread)[i].thd, NULL, &thread_function, &((t_thread*)data->thread)[i])) != 0)
			return (err);
	}
	time = SDL_GetTicks();
	i = 0;
	while (i < 4)
	{
		timeout.tv_sec = 0;
		timeout.tv_nsec = 0;
		if (pthread_timedjoin_np(((t_thread *)data->thread)[i].thd, NULL, &timeout) == ETIMEDOUT)
		{
			if (!data->flag.time && SDL_GetTicks() - time > 1000)
				data->flag.time = 1;
			if (SDL_QuitRequested())
				return (stop_execute("", &data));
			if (data->flag.first == 0 || data->flag.time)
			{
				loading_sc(data, pos);
				pos += 1;
				pos > 34 ? pos = 0 : 0;
			}
		}
		else
		{
			data->obj.camera[data->obj.index[0]].pos.direction =
				normalize(find_dir(data->thread, data->window.x >> 1,
				data->window.y >> 1));
			i++;
		}
	}
	SDL_RenderClear(data->window.rend);
	data->flag.first = 1;
	return (0);
}
