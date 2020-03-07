/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/25 18:14:07 by luwargni         ###   ########.fr       */
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
	if (data->obj.type_index == 0)
		data->font.str = ft_strjoinfree("Current Cam :\0", ft_itoa(data->obj.index[0]), 2);
	else if (data->obj.type_index == 1)
		data->font.str = ft_strjoinfree("Current Obj :\0", ft_itoa(data->obj.index[1]), 2);
	else
		data->font.str = ft_strjoinfree("Current Light :\0", ft_itoa(data->obj.index[2]), 2);
	print_text(data, 0, 0, 30);
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

int			loop(t_data *data)
{
	int		err;

	data->obj.type_index = 0;
	if ((err = init_thread_memory(data)) != 0)
		return (err);
	data->flag.asked = 1;
	while (TRUE)
	{
		if (key_check(*data, SDL_SCANCODE_BACKSPACE))
			data->screen.interface = HOME;
		check_time(data);
		if (SDL_QuitRequested())
			break;
		data->screen.screen[data->screen.interface & 0xFF](data);
		input(data);
		if (signals(data))
			break;
		if (data->input.key[SDL_SCANCODE_P])
			data->flag.asked = 1;
	}
	return (0);
}
