/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/29 13:49:16 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				check_time(t_data *data)
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

static void			effect(t_data *data)
{
	if (data->flag.video && data->flag.cam_move)
	{
		rot_cam_video(data, &data->obj.camera[data->obj.index[0]]);
	}
}

int					loop(t_data *data)
{
	int		err;

	data->obj.type_index = 0;
	if ((err = init_thread_memory(data)) != 0)
		return (err);
	data->flag.asked = 1;
	create_menu_texture(data);
	while (TRUE)
	{
		
		if (key_check(data, SDL_SCANCODE_BACKSPACE))
			data->screen.interface = HOME;
		check_time(data);
		if (SDL_QuitRequested())
			break ;
		data->screen.screen[data->screen.interface & 0xFF](data);
		input(data);
		effect(data);
		if (signals(data))
			break ;
		if (data->input.key[SDL_SCANCODE_P])
			data->flag.asked = 1;
	}
	return (0);
}
