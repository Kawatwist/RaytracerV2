/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:55:54 by luwargni          #+#    #+#             */
/*   Updated: 2020/02/19 18:02:27 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		init_hud(t_data *data)
{
	static char	*tab[] = {CAM_TXT, OEIL_TXT, LIGHT_TXT, SPHERE_TXT, PLAN_TXT,
		CONE_TXT, CYLINDER_TXT, TRINITY_TXT, HUD_TXT};
	t_tga		*tmp;
	int			i;

	i = -1;
	while (++i < 9)
	{
		if ((tmp = load_tga(tab[i])) == NULL)
			return (1);
		data->hud.tmp = SDL_CreateRGBSurfaceFrom(tmp->data, tmp->w, tmp->h, 32,
			tmp->w * 4, 0xFF00, 0xFF0000, 0xFF000000, 0xFF);
		data->hud.texture[i] =
			SDL_CreateTextureFromSurface(data->window.rend, data->hud.tmp);
		SDL_FreeSurface(data->hud.tmp);
		free_tga(tmp);
	}
	create_rgb_txt(data);
	return (0);
}
