/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/08 04:45:29 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	looping(t_data *data)
{
	int		err;

	SDL_LockTexture(data->window.txt, NULL,
			&data->window.pxl, &data->window.pitch);
	if ((err = start_thread(data)))
		return (err);
	post_processing(data);
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	SDL_UnlockTexture(data->window.txt);
	SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
	if (data->hud.flag_icon)//possibiliter ternaire
		pics_on_screen(data);
	init_hud(data);
	SDL_RenderPresent(data->window.rend);
	return (0);
}

int			real_time_icon(t_data *data)
{
	unsigned int		i;

	i = -1;
	while (++i < data->window.x * data->window.y)
		((unsigned char *)data->window.pxl)[(i * 4) + 3] = 20 * (((unsigned char *)data->window.pxl)[(i * 4) + 1] +
									((unsigned char *)data->window.pxl)[(i * 4) + 2] +
									((unsigned char *)data->window.pxl)[(i * 4)]) > 255 ? 255 :
									 10 * (((unsigned char *)data->window.pxl)[(i * 4) + 1] +
									((unsigned char *)data->window.pxl)[(i * 4) + 2] +
									((unsigned char *)data->window.pxl)[(i * 4)]);
	SDL_Surface  *icon = SDL_CreateRGBSurfaceFrom(&(data->window.pxl[0]), data->window.x, data->window.y, 32,
	data->window.x * 4, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);
	// SECURITY
	SDL_SetWindowIcon(data->window.window, icon);
	SDL_FreeSurface(icon);
	return (0);
}

void		check_time(t_data *data)
{
	static Uint32	post = 0;
	static char		cycle = 0;
	Uint32				i;
	void			*pxl;


	if (data->flag.first == 0)
		post = SDL_GetTicks();
	if (cycle > 0 && SDL_GetTicks() - post > 1000)
		data->flag.time = 1;
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

int			loop(t_data data)
{

	int		err;
	int		asked;

	data.obj.type_index = 0;
	if ((err = init_thread_memory(&data)) != 0)
		return (err);
	asked = 1;
	while (TRUE)
	{
		check_time(&data);
		if (data.flag.refresh || asked)
		{
			ft_putstr("\nRefresh Mode Enable\n");
			if ((err = looping(&data)) != 0)
				return (err);
			asked = 0;
		}
		else
			SDL_Delay(16);
		input(&data);
		if (data.input.key[SDL_SCANCODE_ESCAPE] || SDL_QuitRequested())
			break ;
		if (data.input.key[SDL_SCANCODE_P])
			asked = 1;
		real_time_icon(&data);
	}
	return (0);
}
