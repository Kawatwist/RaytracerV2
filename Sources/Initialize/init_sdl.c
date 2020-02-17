/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 19:46:59 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/17 08:03:57 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	initialize_sdl_txt(t_data *data)
{
	data->window.txt = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
		data->window.y);
	data->window.oldtxt = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
		data->window.y);
	return (0);
}

int			initialize_sdl(t_data *data)
{
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER))
		return (1);
	data->window.window = SDL_CreateWindow("RT", 500, 500, data->window.x,
		data->window.y, SDL_WINDOW_SHOWN);
	if (data->window.window == NULL)
		return (2);
	if ((data->window.rend = SDL_CreateRenderer(data->window.window,
			-1, SDL_RENDERER_ACCELERATED)) == NULL)
		return (5);
	initialize_sdl_txt(data);
	if (data->window.txt == NULL || data->window.oldtxt == NULL)
		return (4);
    SDL_EventState(SDL_DROPFILE, SDL_DISABLE);
	SDL_PollEvent(&data->input.ev);
	SDL_RenderPresent(data->window.rend);
	if (loading(data) != 0)
		return (1);
	if (init_hud(data) != 0)
		return (1);
	return (0);
}
