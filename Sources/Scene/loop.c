/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/24 13:39:11 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			looping(t_data *data)
{
	int		err;

	SDL_LockTexture(data->window.txt, NULL,
			&data->window.pxl, &data->window.pitch);
	printf("avant start_thread\n");
	if ((err = start_thread(data)))//segfault
		return (err);
	post_processing(data);
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	SDL_UnlockTexture(data->window.txt);
	SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
	printf("avant pics_on_screen\n");
	if (data->hud.flag_hud)
		pics_on_screen(data);
	SDL_RenderPresent(data->window.rend);
	return (0);
}

void		check_time(t_data *data)
{
	static Uint32	post = 0;
	static char		cycle = 0;
	Uint32			i;
	void			*pxl;

	if (data->flag.first == 0)
		post = SDL_GetTicks();
	if (SDL_GetTicks() - post > 1000)
		data->flag.time = 1;
	else
		data->flag.time = 0;
	cycle += 1;
	if (data->flag.time == 1)
	{
		SDL_LockTexture(data->window.txt, NULL,
			&data->window.pxl, &data->window.pitch);
		SDL_LockTexture(data->window.oldtxt, NULL,
			&pxl, &data->window.pitch);
		i = -1;
		while (++i < (Uint32)(data->window.x * data->window.y))
			((int *)pxl)[i] = ((int *)data->window.pxl)[i];
		SDL_UnlockTexture(data->window.txt);
		SDL_UnlockTexture(data->window.oldtxt);
	}
	post = SDL_GetTicks();
}

int			sub_loop(t_data *data)
{
	int err;

	if (data->flag.refresh || data->flag.asked)
	{
		ft_putstr("\nRefresh Mode Enable\n");
		printf("avant looping\n");
		if ((err = looping(data)) != 0)// souvent segfault
			return (err);
		data->flag.asked = 0;
	}
	else
		SDL_Delay(16);
	real_time_icon(data);
	return (0);
}

int			loop(t_data data)
{
	int		err;

	data.obj.type_index = 0;
	if ((err = init_thread_memory(&data)) != 0)
		return (err);
	data.flag.asked = 1;
	while (TRUE)
	{
		check_time(&data);
		data.screen.screen[data.screen.interface & 0xFF](&data);
		input(&data);
		SDL_PumpEvents();
		if (data.input.key[SDL_SCANCODE_ESCAPE])
			break ;
		if (data.input.key[SDL_SCANCODE_P])
			data.flag.asked = 1;
		if (key_check(data, SDL_SCANCODE_BACKSPACE))
		data.screen.interface = HOME;
	}
	return (0);
}
