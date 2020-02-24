/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_hud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:15:53 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/24 19:01:09 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static SDL_Surface	*blue(void)
{
	static int	pxl = 0xFF0000FF;

	return (SDL_CreateRGBSurfaceFrom(&pxl, 1, 1, 32, 4,
		0xFF0000, 0xFF00, 0xFF, 0xFF000000));
}

static SDL_Surface	*green(void)
{
	static int	pxl = 0xFF00FF00;

	return (SDL_CreateRGBSurfaceFrom(&pxl, 1, 1, 32, 4,
		0xFF0000, 0xFF00, 0xFF, 0xFF000000));
}

static SDL_Surface	*red(void)
{
	static int	pxl = 0xFFFF0000;

	return (SDL_CreateRGBSurfaceFrom(&pxl, 1, 1, 32, 4,
		0xFF0000, 0xFF00, 0xFF, 0xFF000000));
}

void				create_rgb_txt(t_data *data)
{
	SDL_Surface		*surface;

	surface = red();
	data->hud.rgb[0] =
		SDL_CreateTextureFromSurface(data->window.rend, surface);
	SDL_FreeSurface(surface);
	surface = green();
	data->hud.rgb[1] =
		SDL_CreateTextureFromSurface(data->window.rend, surface);
	SDL_FreeSurface(surface);
	surface = blue();
	data->hud.rgb[2] =
		SDL_CreateTextureFromSurface(data->window.rend, surface);
	SDL_FreeSurface(surface);
}
