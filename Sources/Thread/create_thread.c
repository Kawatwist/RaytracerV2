/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/18 11:49:27 by lomasse          ###   ########.fr       */
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

static void		thread_loading_bar(t_data *data)
{
	SDL_Rect	load;
	int			i;

	i = -1;
	while (++i < 4)
	{
		load.x = 300 + (i * 25);
		load.y = data->window.y - 35 - (((t_thread *)data->thread)[i].loading * 4);
		load.w = 20;
		load.h = ((t_thread *)data->thread)[i].loading * 4;
		SDL_SetRenderDrawColor(data->window.rend, (25 - ((t_thread *)data->thread)[i].loading) * 10, (((t_thread *)data->thread)[i].loading) * 10, 0, 0); /*! ATTENTION LOADING VAR */
		SDL_RenderFillRect(data->window.rend, &load);
	}
	SDL_SetRenderDrawColor(data->window.rend, 0, 0, 0, 0);
}

static void		loading_bar(t_data *data)
{
	SDL_Rect	load;

	SDL_SetRenderDrawColor(data->window.rend, (100 - data->loading) * 2.5, (data->loading) * 2.5, 0, 0);
	load.x = 300;
	load.y = data->window.y - 30;
	load.w = data->loading;
	load.h = 20;
	SDL_RenderFillRect(data->window.rend, &load);
	thread_loading_bar(data);
	SDL_SetRenderDrawColor(data->window.rend, 0, 0, 0, 0);
}

static void		show_hud_loading(t_data *data)
{
	SDL_Rect	pos;

	pos.x = 300;
	pos.y = 0;
	pos.w = data->window.x - 300;
	pos.h = data->window.y - 0;

	if (data->flag.first == 0 || data->window.oldtxt == NULL)
		SDL_RenderCopy(data->window.rend, data->load.loading, &pos, &pos);
	else
		SDL_RenderCopy(data->window.rend, data->window.oldtxt, &pos, &pos);
	/* Place Hud There */
	texture_on_screen(data);
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
	int i;

	i = -1;
	while (++i < 4)
		while (pthread_mutex_trylock(&((t_thread *)data->thread)[i].mutex))
			;
	data->loading = ((t_thread *)data->thread)[0].loading + ((t_thread *)data->thread)[1].loading + ((t_thread *)data->thread)[2].loading + ((t_thread *)data->thread)[3].loading;
	ft_putnbr(data->loading);
	ft_putstr("%\n");
	if (data->flag.video)
	{
		ft_putstr("frame : ");
		ft_putnbr(data->flag.video / data->flag.nb_video);
		ft_putstr("\t(");
		ft_putnbr((data->flag.nb_video - data->flag.video));
		ft_putchar('/');
		ft_putnbr(data->flag.nb_video);
		ft_putstr(")\n");
	}
	// SDL_UnlockTexture(data->window.txt);
	// SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
	// SDL_LockTexture(data->window.txt, NULL, &data->window.pxl, &data->window.pitch);
	i = 0;
	while (i < 4)
	{
		pthread_mutex_unlock(&((t_thread *)data->thread)[i].mutex);
		i++;
	}
	setup_rect(data, &og, &screen, &lolz);
	SDL_RenderClear(data->window.rend);
	if (data->hud.flag_hud)
		show_hud_loading(data);
	else if (data->flag.first == 0 || data->window.oldtxt == NULL)
		SDL_RenderCopy(data->window.rend, data->load.loading, NULL, NULL);
	else
		SDL_RenderCopy(data->window.rend, data->window.oldtxt, NULL, NULL);
	SDL_RenderCopy(data->window.rend, data->load.load, &pos, &og);
	loading_bar(data);
	SDL_RenderPresent(data->window.rend);
	SDL_Delay(64);
}

static void		light_variance(t_data *data, t_thread *thd)
{
	float	tmp;
	float	change;

	for (int i = 0; i < data->obj.nb_light; i++)
	{
		if (data->obj.light[i].variance != 0)
		{

			change = data->obj.light[i].variance * ((((rand() % 10) - 5.0) / 500.0));
			tmp = data->obj.light[i].intensity + (change / 2);
			tmp > data->obj.light[i].intensitysave + data->obj.light[i].variance ? tmp = data->obj.light[i].intensitysave + data->obj.light[i].variance : 0;
			tmp < data->obj.light[i].intensitysave - data->obj.light[i].variance ? tmp = data->obj.light[i].intensitysave - data->obj.light[i].variance : 0;

			thd[0].obj.light[i].intensity = tmp;
			thd[1].obj.light[i].intensity = tmp;
			thd[2].obj.light[i].intensity = tmp;
			thd[3].obj.light[i].intensity = tmp;
			tmp < 0 ? tmp = 0 : 0;

			tmp = data->obj.light[i].distance + change;
			tmp > data->obj.light[i].distancesave + data->obj.light[i].variance ? tmp = data->obj.light[i].distancesave + data->obj.light[i].variance : 0;
			tmp < data->obj.light[i].distancesave - data->obj.light[i].variance ? tmp = data->obj.light[i].distancesave - data->obj.light[i].variance : 0;
			tmp < 0 ? tmp = 0 : 0;
			thd[0].obj.light[i].distance = tmp;
			thd[1].obj.light[i].distance = tmp;
			thd[2].obj.light[i].distance = tmp;
			thd[3].obj.light[i].distance = tmp;
		}
	}
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
	light_variance(data, data->thread);
	while (++i < 4)
	{
		((t_thread *)data->thread)[i].max_dist = data->max_dist;
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
			if (!data->flag.screen)
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
		}
		else
		{
			data->obj.camera[data->obj.index[0]].pos.direction =
				normalize(find_dir(data->thread, data->window.x >> 1,
				data->window.y >> 1));
			i++;
		}
	}
	if (!data->flag.screen)
		SDL_RenderClear(data->window.rend); // Dosnt need ?
	data->flag.first = 1;
	return (0);
}
