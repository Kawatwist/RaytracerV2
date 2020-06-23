/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/22 19:15:22 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
void	set_background(t_data *data)
{
	int			pitch;
	void		*pxl;

	SDL_LockTexture(data->menu.background, NULL, &pxl, &pitch);
	ft_memset(pxl, 33, 200 * data->window.y * 4);
	SDL_UnlockTexture(data->menu.background);
}

static int	texture_on_screen(t_data *data)
{
	SDL_Rect	pos;
	SDL_Rect	dst;
	
	/*If Hud*/
	pos.x = 200;
	pos.y = 30;
	pos.w = data->window.x - 200;
	pos.h = data->window.y - 30;
	SDL_SetRenderDrawColor(data->window.rend, 33, 33, 33, 0);
	SDL_RenderClear(data->window.rend);
	SDL_RenderCopy(data->window.rend, data->window.txt, &pos, &pos); // Secu ?
	
	set_background(data);
	
	
	dst.x = 0;
	dst.y = 20;
	dst.w = 50;
	dst.h = 50;
	draw_rect(data, dst, 0xf0451d);
	//0x29cb75
	
	
	dst.x = 100;
	dst.y = 100;
	dst.w = 20;
	dst.h = 20;
	draw_rect(data, dst, 0x29cb75);
	
	dst.x = 150;
	dst.y = 0;
	dst.w = 1;
	dst.h = data->window.y;
	draw_rect(data, dst, 0x29cb75);

	dst.x = 0;
	dst.y = 0;
	dst.w = 200;
	dst.h = data->window.y;
	SDL_RenderCopy(data->window.rend, data->menu.background, NULL, &dst);
	return (0);
}

static int	looping(t_data *data)
{
	int		err;

	resize(data);
	SDL_LockTexture(data->window.txt, NULL,
			&data->window.pxl, &data->window.pitch);
	if ((err = start_thread(data)))//segfault
		return (err);
	post_processing(data);
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	SDL_UnlockTexture(data->window.txt);
	texture_on_screen(data);
	//if (data->hud.flag_hud)
	//	pics_on_screen(data);
	if (data->obj.type_index == 0)
		data->font.str = ft_strjoinfree("Current Cam :\0",
			ft_itoa(data->obj.index[0]), 2);
	else if (data->obj.type_index == 1)
		data->font.str = ft_strjoinfree("Current Obj :\0",
			ft_itoa(data->obj.index[1]), 2);
	else
		data->font.str = ft_strjoinfree("Current Light :\0",
			ft_itoa(data->obj.index[2]), 2);
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

	if (data->flag.refresh || data->flag.asked || data->flag.video)
	{
		ft_putstr("\nRefresh Mode Enable\n");
		printf("avant looping\n");
		if ((err = looping(data)) != 0)// souvent segfault
			return (err);
		data->flag.asked = 0;
		data->flag.video ? data->flag.video -= 1 : 0;
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

static void			effect(t_data *data)
{
	if (data->flag.video)
	{
		rot_cam_video(data, &data->obj.camera[data->obj.index[0]]);
	}
}

int			loop(t_data *data)
{
	int		err;

	data->obj.type_index = 0;
	if ((err = init_thread_memory(data)) != 0)
		return (err);
	data->flag.asked = 1;
	create_menu_texture(data);
	while (TRUE)
	{
		if (key_check(*data, SDL_SCANCODE_BACKSPACE))
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
