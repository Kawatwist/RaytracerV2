/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/21 20:14:09 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	looping(t_data *data)
{
	int		err;

	SDL_LockTexture(data->window.txt, NULL,
			&data->window.pxl, &data->window.pitch);
	if ((err = start_thread(data)))//segfault
		return (err);
	post_processing(data);
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	SDL_UnlockTexture(data->window.txt);
	SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
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

static void			parse_line(t_data *data, char *line)
{
	char *ret;

	if ((ret = ft_strstr(line, "o =")) != NULL)
		data->flag.antialiasing = ft_atoi(ret + 4) & 0x2;
}

static int			signals(t_data *data)
{
	char *line;

	line = NULL;
	if (data->input.key[SDL_SCANCODE_ESCAPE])
		return (1);
	if (data->input.key[SDL_SCANCODE_LCTRL] && data->input.key[SDL_SCANCODE_C])
	{
		ft_putstr("^C");
		return (1);
	}
	if (data->input.key[SDL_SCANCODE_LCTRL] && data->input.key[SDL_SCANCODE_Y])
	{
		get_next_line(1, &line);
		parse_line(data, line);
		free(line);
	}
	return (0);
}
#include "thread.h"

static void		preset_cam(t_data *data, int index)
{
	float	coef;

	(data->obj.camera[index]).sc =
		add_vec((data->obj.camera[index]).pos.origin,
			fill_vec(-0.5, -0.5, 0.5));
	if (data->window.x >= data->window.y)
	{
		coef = (float)data->window.x / (float)data->window.y;
		(data->obj.camera[index]).x = fill_vec(coef / data->window.x, 0, 0);
		(data->obj.camera[index]).y = fill_vec(0, 1.0 / data->window.y, 0);
		(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).sc,
			fill_vec((1 - coef) / 2.0, 0, 0));
	}
	else
	{
		coef = (float)data->window.y / (float)data->window.x;
		(data->obj.camera[index]).x = fill_vec(1.0 / data->window.x, 0, 0);
		(data->obj.camera[index]).y = fill_vec(0, coef / data->window.y, 0);
		(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).sc,
			fill_vec(0, (1 - coef) / 2, 0));
	}
}
static int				init_cam(t_data *data)
{
	int			index;
	t_point		direction;
	t_point		base;

	index = 0;
	while (index < data->obj.nb_camera)
	{
		direction = normalize((data->obj.camera[index]).pos.direction);
		base = fill_vec(0, 0, 1);
		preset_cam(data, index);
		data->obj.camera[index].oldpos.origin =
			veccpy(data->obj.camera[index].pos.origin);
		data->obj.camera[index].oldpos.direction =
			veccpy(data->obj.camera[index].pos.direction);
		data->obj.camera[index].oldsc = veccpy(data->obj.camera[index].sc);
		data->obj.camera[index].oldx = veccpy(data->obj.camera[index].x);
		data->obj.camera[index].oldy = veccpy(data->obj.camera[index].y);
		index++;
	}
	return (0);
}

void		resize(t_data *data)
{
	static int	x = 0;
	static int	y = 0;
	int		check[2];

	x = data->window.x;
	y = data->window.y;
	SDL_GetWindowSize(data->window.window, &check[0], &check[1]);
	if (x != check[0] || y != check[1])
	{
		data->window.x = check[0];
		data->window.y = check[1];
		SDL_DestroyTexture(data->window.txt);
		SDL_DestroyTexture(data->window.oldtxt);
	data->window.txt = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
		data->window.y);
	data->window.oldtxt = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
		data->window.y);
		for (int i= 0; i < 4; i++)
		{
			((t_thread *)data->thread)[i].x = check[0];
			((t_thread *)data->thread)[i].y = check[1];
			init_cam(data);
		}
	}
}

int			loop(t_data *data)
{
	int		err;
	int		asked;

	data->obj.type_index = 0;
	if ((err = init_thread_memory(data)) != 0)
		return (err);
	asked = 1;
	while (TRUE)
	{
		resize(data);
		check_time(data);
		if (data->flag.refresh || asked)
		{
			ft_putstr("\nRefresh Mode Enable\n");
			if ((err = looping(data)) != 0)
				return (err);
			asked = 0;
		}
		else
			SDL_Delay(16);
		if (SDL_QuitRequested())
			break;
		input(data);
		if (signals(data))
			break;
		if (data->input.key[SDL_SCANCODE_P])
			asked = 1;
		// real_time_icon(data);
	}
	return (0);
}
