/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 19:46:59 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/29 13:40:47 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <path.h>

int				initialize_scene(t_data *data)
{
	t_tga		*txt;
	SDL_Surface	*tmp;

	tmp = NULL;
	if ((txt = load_tga(PATH_HOME)) == NULL)
		return (1);
	if (!(tmp = SDL_CreateRGBSurfaceWithFormatFrom(txt->data, txt->w,
			txt->h, txt->data_bpp, txt->w << 2, SDL_PIXELFORMAT_ARGB32)))
		return (5);
	if ((data->screen.scenetxt[0] =
		SDL_CreateTextureFromSurface(data->window.rend, tmp)) == NULL)
		exit(0);
	SDL_FreeSurface(tmp);
	free_tga(txt);
	if ((txt = load_tga(PATH_GRIMOIRE)) == NULL)
		return (1);
	if (!(tmp = SDL_CreateRGBSurfaceWithFormatFrom(txt->data, txt->w,
			txt->h, txt->data_bpp, txt->w << 2, SDL_PIXELFORMAT_ARGB32)))
		return (5);
	if ((data->screen.scenetxt[3] =
		SDL_CreateTextureFromSurface(data->window.rend, tmp)) == NULL)
		exit(0);
	SDL_FreeSurface(tmp);
	free_tga(txt);
	return (0);
}

static int		init_sub(t_data *data)
{
	data->screen.interface = HOME;
	data->screen.screen[HOME] = home_screen;
	data->screen.screen[RUN] = sub_loop;
	if (initialize_scene(data))
		return (5);
	return (0);
}

static int		initialize_sdl_txt(t_data *data)
{
	data->window.txt = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
		data->window.y);
	data->window.oldtxt = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
		data->window.y);
	return (0);
}

static void		initialize_event(t_data *data)
{
	SDL_EventState(SDL_DROPFILE, SDL_DISABLE);
	SDL_PollEvent(&data->input.ev);
	data->input.key = (Uint8 *)SDL_GetKeyboardState(NULL);
	ft_bzero(data->input.oldkey, 282);
}

int				initialize_sdl(t_data *data)
{
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER))
		return (1);
	data->window.window = SDL_CreateWindow("RT", 0, 0, data->window.x,
		data->window.y, SDL_WINDOW_RESIZABLE);
	if (data->window.window == NULL)
		return (2);
	if ((data->window.rend = SDL_CreateRenderer(data->window.window,
			-1, SDL_RENDERER_ACCELERATED)) == NULL)
		return (5);
	initialize_sdl_txt(data);
	if (data->window.txt == NULL || data->window.oldtxt == NULL)
		return (4);
	initialize_event(data);
	SDL_RenderPresent(data->window.rend);
	if (loading(data))
		return (1);
	if ((init_sub(data)) != 0)
		return (5);
	if (init_font(data))
		return (1);
	if (init_preview(data))
		return (1);
	return (0);
}
