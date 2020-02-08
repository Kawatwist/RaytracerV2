/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:46:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/08 21:31:21 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void		*clear(SDL_Surface *s)
{
	SDL_FreeSurface(s);
	return (NULL);
}

static SDL_Texture	*get_loading(t_data *data, char *path)
{
	t_tga		*v;
	SDL_Surface	*s;
	SDL_Texture	*t;

	if ((v = load_tga(path)) == NULL)
		return (NULL);
	if ((s = SDL_CreateRGBSurfaceFrom(v->data, v->w, v->h, 32, v->w * 4,
		0xFF00, 0xFF0000, 0xFF000000, 0xFF)) == NULL)
		return (free_tga(v));
	free_tga(v);
	if ((t = SDL_CreateTextureFromSurface(data->window.rend, s)) == NULL)
		return (clear(s));
	SDL_FreeSurface(s);
	return (t);
}

int					loading(t_data *data)
{
	if ((data->load = get_loading(data, "./texture/mayload.tga")) == NULL)
		return (1);
	if ((data->loading = get_loading(data, "./texture/loading.tga")) == NULL)
		return (1);
	if ((data->lolz = get_loading(data, "./texture/test.tga")) == NULL)
		return (1);
	return (0);
}
