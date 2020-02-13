/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icon.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:38:54 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/13 03:57:32 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Set The Black color in alpha
*/

int						real_time_icon(t_data *data)
{
	unsigned int		i;
	SDL_Surface			*icon;

	i = -1;
	printf("Icon [1]\n");
	while (++i < data->window.x * data->window.y)
		((unsigned char *)data->window.pxl)[(i * 4) + 3] = 20 *
		(((unsigned char *)data->window.pxl)[(i * 4) + 1] +
		((unsigned char *)data->window.pxl)[(i * 4) + 2] +
		((unsigned char *)data->window.pxl)[(i * 4)]) > 255 ? 255 :
			10 * (((unsigned char *)data->window.pxl)[(i * 4) + 1] +
		((unsigned char *)data->window.pxl)[(i * 4) + 2] +
		((unsigned char *)data->window.pxl)[(i * 4)]);
	printf("Icon [2]\n");
	if ((icon = SDL_CreateRGBSurfaceFrom(&(data->window.pxl[0]),
		data->window.x, data->window.y, 32,
		data->window.x * 4, 0xFF0000, 0xFF00, 0xFF, 0xFF000000)) == NULL)
		return (1);
	printf("Icon [3]\n");
	printf("%p\n", data->window.window);
	if (data->window.window != NULL)
		SDL_SetWindowIcon(data->window.window, icon);
	printf("Icon [4]\n");
	SDL_FreeSurface(icon);
	printf("Icon [5]\n");
	return (0);
}

SDL_Surface				*icone(void)
{
	t_tga				*icon;
	SDL_Surface			*surface;

	if ((icon = load_tga("./texture/icon.tga")) == NULL)
		return (NULL);
	surface = SDL_CreateRGBSurfaceFrom(icon->data, icon->w, icon->h, 32,
	icon->w * 4, 0xFF00, 0xFF0000, 0xFF000000, 0xFF);
	free_tga(icon);
	return (surface);
}

int						set_icone(t_data *data)
{
	SDL_Surface			*icon;

	if ((icon = icone()) == NULL)
		return (1);
	SDL_SetWindowIcon(data->window.window, icon);
	SDL_FreeSurface(icon);
	return (0);
}
