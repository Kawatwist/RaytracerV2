/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/05 03:57:00 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	post_processing(t_data *data)
{
	(void)data;
	int		i;
	int		color;
	int		tr;
	int		tg;
	int		tb;

	i = -1;
	if (data->flag.filter == 1)
	{
		//fonction noir et blanc
		while (++i < data->window.x * data->window.y)
		{
			color = (((unsigned char *)data->window.pxl)[(i << 2) + 1] +
					((unsigned char *)data->window.pxl)[(i << 2) + 2] +
					((unsigned char *)data->window.pxl)[(i << 2) + 3]) / 3;
			((unsigned int *)data->window.pxl)[i] = (0xFF << 24) + (color << 16) + (color << 8) + (color << 0);
		}
	}
	else if (data->flag.filter == 2)
	{
		//fonction sepia
		while (++i < data->window.x * data->window.y)
		{
			tr = ((0.393 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) + (0.769 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) + (0.189 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
			tg = ((0.349 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) + (0.686 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) + (0.168 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
			tb = ((0.272 * ((unsigned char *)data->window.pxl)[(i << 2) + 1]) + (0.534 * ((unsigned char *)data->window.pxl)[(i << 2) + 2]) + (0.131 * ((unsigned char *)data->window.pxl)[(i << 2) + 3]));
			if (tr > 255)
				tr = 255;
			if (tg > 255)
				tg = 255;
			if (tb > 255)
				tb = 255;
			((unsigned int *)data->window.pxl)[i] = ((0xFF << 24) + (tr << 16) + (tg << 8) + (tb << 0));
		}
	}
	else if (data->flag.filter == 3)
	{
		// fonction cartoon
		while (++i < data->window.x * data->window.y)
		{
			tr = (((unsigned char *)data->window.pxl)[(i << 2) + 2] - ((((unsigned char *)data->window.pxl)[(i << 2) + 2] % 60)));
			tg = (((unsigned char *)data->window.pxl)[(i << 2) + 1] - ((((unsigned char *)data->window.pxl)[(i << 2) + 1] % 60)));
			tb = (((unsigned char *)data->window.pxl)[(i << 2) + 0] - ((((unsigned char *)data->window.pxl)[(i << 2) + 0] % 60)));
			if (tr < 0)
				tr = 0;
			if (tg < 0)
				tg = 0;
			if (tb < 0)
				tb = 0;
			if (tr > 255)
				tr = 255;
			if (tg > 255)
				tg = 255;
			if (tb > 255)
				tb = 255;
			((unsigned int *)data->window.pxl)[i] = ((0xFF << 24) + (tr << 16) + (tg << 8) + tb);
		}
	}
	return (0);
}

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
	SDL_RenderPresent(data->window.rend);
	return (0);
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
		input(&data);
		if (data.input.key[SDL_SCANCODE_ESCAPE] || SDL_QuitRequested())
			break ;
		if (data.input.key[SDL_SCANCODE_P])
			asked = 1;
		if (data.flag.refresh || asked)
		{
			ft_putstr("\nRefresh Mode Enable\n");
			if ((err = looping(&data)) != 0)
				return (err);
			asked = 0;
		}
		else
			SDL_Delay(16);
	}
	return (0);
}
