/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:20:13 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/18 17:29:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			loop(t_data data)
{
	int		err;

	data.obj.type_index = 0;
	while (TRUE)
	{
		input(&data);
		if (data.input.key[SDL_SCANCODE_ESCAPE] || SDL_QuitRequested())
			break ;
		SDL_LockTexture(data.window.txt, NULL,
		&data.window.pxl, &data.window.pitch);
		if ((err = start_ray(&data)) != 0)
			return (err);
		data.percent++;
		if (data.percent > 99)
			data.percent = 0;
		SDL_UnlockTexture(data.window.txt);
		SDL_RenderCopy(data.window.rend, data.window.txt, NULL, NULL);
		SDL_RenderPresent(data.window.rend);
	}
	return (0);
}
