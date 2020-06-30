/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/06/30 19:39:51 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2020/06/26 19:39:48 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Tableau fini de structure contenant bouton et pointeur de fonction de x cases
** Menu deroulant de la longueur du tableau avec y (taille max d'option affichable avec dimension actuelle)
** z est l 'indice a partir du quel le menu deroulant demarre
** L'option selectioné est égale a l'emplacement actuel cliqué + z
** 
** La valeur de l'emplacement + z est recupérée et transmise au tableau de structure de bouton qui contient 
** aussi un pointeur de fonction
*/
void	set_background(t_data *data)
{
	int			pitch;
	void		*pxl;

	SDL_LockTexture(data->menu.background, NULL, &pxl, &pitch);
	ft_memset(pxl, 33, 200 * data->window.y * 4);
	SDL_UnlockTexture(data->menu.background);
}

void	draw_outline(t_data *data)
{
	SDL_Rect	dst;

	dst.x = 199;
	dst.y = 30;
	dst.w = 1;
	dst.h = data->window.y - 30;
	draw_rect(data, dst, 0xffffff);
	dst.x = 0;
	draw_rect(data, dst, 0xffffff);
	dst.w = 200;
	dst.h = 1;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y - 1;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y * 0.55 - 1;
	draw_rect(data, dst, 0xffffff);
	
}

void	draw_outline_color(t_data *data)
{
	SDL_Rect	dst;

	dst.x = 20;
	dst.y = data->window.y * 0.55 + 180 - 10;
	dst.w = 160;
	dst.h = 20;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y * 0.55 + 210 - 10;
	draw_rect(data, dst, 0xffffff);
	dst.y = data->window.y * 0.55 + 240 - 10;
	draw_rect(data, dst, 0xffffff);
	dst.x = 21;
	dst.w = 159;
	dst.h = 19;
	dst.y = data->window.y * 0.55 + 181 - 10;
	draw_rect(data, dst, 0x3c3c3c);
	dst.y = data->window.y * 0.55 + 211 - 10;
	draw_rect(data, dst, 0x3c3c3c);
	dst.y = data->window.y * 0.55 + 241 - 10;
	draw_rect(data, dst, 0x3c3c3c);
	
}

void	draw_title_background(t_data *data)
{
	SDL_Rect	dst;

	dst.x = 0;
	dst.y = 31;
	dst.w = 200;
	dst.h = 50;
	draw_rect(data, dst, 0x1965a1);

	dst.x = 0;
	dst.y = data->window.y * 0.55;
	dst.w = 200;
	dst.h = 50;
	draw_rect(data, dst, 0x1965a1);	
}

void	draw_background_box(t_data *data)
{
	SDL_Rect	dst;

	dst.x = 0;
	dst.y = 107;
	dst.w = 150;
	dst.h = 25;
	draw_rect(data, dst, 0x262626);
	dst.x = 0;
	dst.y = 107 + 45;
	dst.w = 150;
	dst.h = 25;
	draw_rect(data, dst, 0x262626);
	dst.x = 0;
	dst.y = 107 + 90;
	dst.w = 150;
	dst.h = 25;
	draw_rect(data, dst, 0x262626);
}

void	draw_button(t_data *data, int x, int y, int state)
{
	SDL_Rect		dst;
	unsigned int	color;

	dst.w = 30;
	dst.h = 30;
	dst.x = x;
	dst.y = y;
	if (state == 0)
		color = 0xf0451d;
	else
		color = 0x29cb75;
	draw_rect(data, dst, color);
	if (state == 0)
	{
		dst.y += 30;
		dst.h = 3;
		draw_rect(data, dst, 0xc80a20);
	}	
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
	SDL_SetRenderDrawColor(data->window.rend, 0xcc, 0xcc, 0xcc, 0xcc);
	SDL_RenderClear(data->window.rend);
	SDL_RenderCopy(data->window.rend, data->window.txt, &pos, &pos); // Secu ?
	
	set_background(data);
	draw_title_background(data);
	
	draw_outline_color(data);

	draw_background_box(data);
	draw_button(data, 145, 105, 0);
	draw_button(data, 145, 150, 1);
	draw_button(data, 145, 195, 0);
	//0x29cb75 Rouge foncé 
	//0xf0451d Rouge Clair
	draw_outline(data);
	
	

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
	generate_perlin(data);
	post_processing(data);
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	SDL_UnlockTexture(data->window.txt);
	if (data->hud.flag_hud)
		texture_on_screen(data);
	else
		SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
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
		real_time_icon(data);
	}
	else
		SDL_Delay(16);
	if (data->hud.flag_hud != data->hud.last_hud)
	{
		if (data->hud.flag_hud)
			texture_on_screen(data);
		else
			SDL_RenderCopy(data->window.rend, data->window.txt, NULL, NULL);
		data->hud.last_hud = data->hud.flag_hud;
		SDL_RenderPresent(data->window.rend);
	}
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
