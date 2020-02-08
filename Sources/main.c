/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:29:35 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/08 04:35:19 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Surface	*icone(void)
{
	t_tga		*icon;
	SDL_Surface	*surface;

	icon = load_tga("./texture/icon.tga");
	surface = SDL_CreateRGBSurfaceFrom(icon->data, icon->w, icon->h, 32, icon->w * 4, 0xFF00, 0xFF0000, 0xFF000000, 0xFF);
	free_tga(icon);
	return (surface);
}

int			main(int argc, char *argv[])
{
	int			value;
	t_data		data;

	if ((value = initialize(&data)) != 0)
		return (stop_main_execute("Error Initalize : ", &data, value));
	if ((value = parsing(&data, argc, argv)) != 0)
		return (stop_main_execute("Error Parsing : ", &data, value));
	if ((value = check_parse(&data)) != 0)
		return (stop_main_execute("Error Parse Check : ", &data, value));
	/*
	**	Cam x = Size De l'ecran demander
	*/
	if ((value = initialize_sdl(&data)) != 0)
		return (value);
	if (*data.texture != NULL)
	{

		SDL_Surface  *icon = icone();
		SDL_SetWindowIcon(data.window.window, icon);
		SDL_FreeSurface(icon);
	}
	if ((value = loop(data)) != 0 && value != 50)
		return (stop_main_execute("Run Stopped : ", &data, value));
	clear_memory(&data);
	ft_putstr("See you soon !\n");
	return (0);
}
