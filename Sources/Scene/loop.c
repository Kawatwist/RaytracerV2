/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/15 16:58:59 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	looping(t_data *data)
{
	int		err;

	printf("Looping [1]\n");
	SDL_LockTexture(data->window.txt, NULL,
			&data->window.pxl, &data->window.pitch);
	printf("Looping [2]\n");
	if ((err = start_thread(data)))
		return (err);
	printf("Looping [3]\n");
	post_processing(data);
	printf("Looping [4]\n");
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	printf("Looping [5]\n");
	SDL_UnlockTexture(data->window.txt);
	printf("Looping [6]\n");
	SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
	printf("Looping [7]\n");
	if (data->hud.flag_icon)
		pics_on_screen(data);
	printf("Looping [8]\n");
	init_hud(data);
	printf("Looping [9]\n");
	SDL_RenderPresent(data->window.rend);
	printf("Looping [10]\n");
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

int			loop(t_data data)
{
	int		err;
	int		asked;

	data.obj.type_index = 0;
	printf("Loop [1]\n");
	if ((err = init_thread_memory(&data)) != 0)
		return (err);
	printf("Loop [2]\n");
	asked = 1;
	while (TRUE)
	{
	printf("Loop [3]\n");
		check_time(&data);
	printf("Loop [4]\n");
		if (data.flag.refresh || asked)
		{
			ft_putstr("\nRefresh Mode Enable\n");
			if ((err = looping(&data)) != 0)
				return (err);
			asked = 0;
		printf("Loop [5]\n");
		}
		else
			SDL_Delay(16);
	printf("Loop [6]\n");
		input(&data);
	printf("Loop [7]\n");
		if (data.input.key[SDL_SCANCODE_ESCAPE] || SDL_QuitRequested())
			break ;
	printf("Loop [8]\n");
		if (data.input.key[SDL_SCANCODE_P])
			asked = 1;
	printf("Loop [9]\n");
		real_time_icon(&data);
	printf("Loop [10]\n");
	}
	return (0);
}
