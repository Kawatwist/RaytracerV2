/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/23 23:34:59 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	looping(t_data *data)
{
	int		err;

	SDL_LockTexture(data->window.txt, NULL,
			&data->window.pxl, &data->window.pitch);
	// sleep(2);
	// thread_poll(data); // PROBLEME DE CONDITION
	// sleep(2);
	if ((err = start_ray(data)) != 0)
		return (err);
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	SDL_UnlockTexture(data->window.txt);
	SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
	SDL_RenderPresent(data->window.rend);
	return (0);
}

int			loop(t_data data)
{
	int		err;

	data.obj.type_index = 0;

	if ((err = init_thread_memory(&data)) != 0)
		return (err);
	if ((err = looping(&data)) != 0)
		return (err);
	while (TRUE)
	{
		input(&data);
		if (data.input.key[SDL_SCANCODE_ESCAPE] || SDL_QuitRequested())
			break ;
		if (data.flag.refresh)
		{
			ft_putstr("\nRefresh Mode Enable\n");
			if ((err = looping(&data)) != 0)
				return (err);
		}
		else
			SDL_Delay(16);
	}
	return (0);
}
