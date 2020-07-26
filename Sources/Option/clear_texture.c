/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:43:03 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/26 17:45:33 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void			clear_texture_main(t_data *data, t_tga **tofree)
{
	int		i;

	i = -1;
	if (tofree != NULL)
	{
		while (++i < data->obj.nb_texture)
			(tofree[i]) != NULL ? free_tga(tofree[i]) : 0;
		if (tofree != NULL)
			free((tofree));
	}
}

void			clear_normal_main(t_data *data, t_tga **tofree)
{
	int		i;

	i = -1;
	if (tofree != NULL)
	{
		while (i++ < data->obj.nb_normal - 1)
			(tofree)[i] != NULL ? free_tga((tofree)[i]) : 0;
		if (data->normal)
			free((tofree));
		i = -1;
		while (i++ < data->obj.nb_normal - 1)
			data->obj.normal[i] != NULL ? free(data->obj.normal[i]) : 0;
		if (data->obj.normal != NULL)
			free(data->obj.normal);
	}
}

void			destroy_text_main(SDL_Texture *t)
{
	if (t != NULL)
	{
		SDL_DestroyTexture(t);
		t = NULL;
	}
}
