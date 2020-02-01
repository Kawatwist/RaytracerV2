/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:55:54 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/01 03:55:48 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		init_hud(t_data *data)
{
	static char *tab[] = {CAM_TXT, LIGHT_TXT, SPHERE_TXT};
	t_tga	*tmp;

	for (int i = 0; i < 3; i++)
	{
		if ((tmp = load_tga(tab[i])) == NULL)
			return (1);
		data->hud.tmp = SDL_CreateRGBSurfaceFrom(tmp->data, tmp->w, tmp->h, 32, tmp->w * 4, 0xFF00, 0xFF0000, 0xFF000000, 0xFF);
		data->hud.iqfow[i] = SDL_CreateTextureFromSurface(data->window.rend, data->hud.tmp);
		SDL_FreeSurface(data->hud.tmp);
		free_tga(tmp);
	}
	return (0);
}
	// SDL_Surface *newsurface;
	// SDL_Texture *Ma_Texture_de_camera;
	// SDL_Rect ICI;
	// SDL_Rect POS;
	// POS.x = 0;
	// POS.y = 0;
	// POS.w = data.window.x;//decoupage de l'image rt
	// POS.h = data.window.y;//decoupage de l'image rt
	// ICI.x = 20;//move icone
	// ICI.y = data.window.y - 80;//move icone
	// ICI.w = 60;//taille icone
	// ICI.h = 60;//taille icone
	// SDL_FreeSurface(newsurface);
