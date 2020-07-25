/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:46:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/25 12:11:39 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void		*clear_(SDL_Surface *s, t_tga *v)
{
	SDL_FreeSurface(s);
	free_tga(v);
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
	if ((t = SDL_CreateTextureFromSurface(data->window.rend, s)) == NULL)
		return (clear_(s, v));
	SDL_FreeSurface(s);
	free_tga(v);
	return (t);
}

int					loading(t_data *data)
{
	if (!(data->load.load = get_loading(data, "./Assets/mayload.tga")))
		return (1);
	if (!(data->load.loading = get_loading(data, "./Assets/loading.tga")))
		return (1);
	return (0);
}
