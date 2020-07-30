/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:00:55 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/29 16:48:07 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

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
}

static void		init_pos(SDL_Rect *pos, int p)
{
	pos->x = (p % 6) * 100;
	pos->y = (p / 6) * 100;
	pos->w = 100;
	pos->h = 100;
}

static void		loading_sc2(t_data *data)
{
	int i;

	i = -1;
	while (++i < 4)
		while (pthread_mutex_trylock(&((t_thread *)data->thread)[i].mutex))
			;
	data->loading = ((t_thread *)data->thread)[0].loading +
		((t_thread *)data->thread)[1].loading +
		((t_thread *)data->thread)[2].loading +
		((t_thread *)data->thread)[3].loading;
	ft_putnbr(data->loading);
	ft_putstr("%\n");
	if (data->flag.video)
	{
		ft_putstr("frame : ");
		ft_putnbr(data->flag.nb_video - data->flag.video);
		ft_putstr("\t(");
		ft_putnbr((data->flag.nb_video - data->flag.video));
		ft_putchar('/');
		ft_putnbr(data->flag.nb_video);
		ft_putstr(")\n");
	}
}

void			show_advance(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		SDL_UnlockTexture(data->window.txt);
		SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
		SDL_LockTexture(data->window.txt, NULL, &data->window.pxl,
			&data->window.pitch);
		((t_thread *)data->thread)[i].pxl = data->window.pxl;
	}
}

void			loading_sc(t_data *data, int p)
{
	SDL_Rect	pos;
	SDL_Rect	og;
	SDL_Rect	screen;
	SDL_Rect	lolz;
	int			i;

	init_pos(&pos, p);
	loading_sc2(data);
	i = -1;
	if (data->flag.adv)
		show_advance(data);
	while (++i < 4)
		pthread_mutex_unlock(&((t_thread *)data->thread)[i].mutex);
	setup_rect(data, &og, &screen, &lolz);
	!data->flag.adv ? SDL_RenderClear(data->window.rend) : 0;
	if ((!data->flag.first || !data->window.oldtxt) && !data->flag.adv)
		SDL_RenderCopy(data->window.rend, data->load.loading, NULL, NULL);
	else if (!data->flag.adv)
		SDL_RenderCopy(data->window.rend, data->window.oldtxt, NULL, NULL);
	if (data->hud.flag_hud)
		show_hud_loading(data);
	SDL_RenderCopy(data->window.rend, data->load.load, &pos, &og);
	loading_bar(data);
	SDL_RenderPresent(data->window.rend);
	SDL_Delay(64);
}
