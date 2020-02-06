/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 19:46:59 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/06 03:09:42 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			initialize_sdl(t_data *data)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (1);
	data->window.window = SDL_CreateWindow("RT", 500, 500, data->window.x,
		data->window.y, SDL_WINDOW_SHOWN);
	if (data->window.window == NULL)
		return (2);
	data->window.rend = SDL_CreateRenderer(data->window.window,
			-1, SDL_RENDERER_ACCELERATED);
	if (data->window.rend == NULL)
		return (5);
	data->window.txt = SDL_CreateTexture(data->window.rend,
		SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
		data->window.y);
	if (data->window.txt == NULL)
		return (4);
	SDL_PollEvent(&data->input.ev);
	SDL_RenderPresent(data->window.rend);
/*
**	Loading Screen
*/
	t_tga *v;
	v = load_tga("./texture/Load.tga");
	SDL_Surface *s= SDL_CreateRGBSurfaceFrom(v->data, v->w, v->h, 32, v->w * 4, 0xFF00, 0xFF0000, 0xFF000000, 0xFF);
	data->load = SDL_CreateTextureFromSurface(data->window.rend, s);
	SDL_FreeSurface(s);
	free_tga(v);
/*
**
*/
	return (0);
}
