/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_font.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:50:48 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/23 15:22:17 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Rect			set_font_pos(char a)
{
	SDL_Rect	pos;

	pos.x = 0;
	pos.y = 0;
	pos.w = 0;
	pos.h = 0;
	if (a >= 'A' && a <= 'Z')
	{
		pos.w = 95;
		pos.h = 100;
		pos.x = ((a - 'A') % 9) * pos.w;
		pos.y = ((a - 'A') / 9) * pos.h;
	}
	else if (a >= 'a' && a <= 'z')
	{
		pos.w = 95;
		pos.h = 100;
		pos.x = ((a - 'a') % 9) * pos.w;
		pos.y = ((a - 'a') / 9) * pos.h;
	}
	return (pos);
}

int			print_text(t_data *data, int x, int y, int size)
{
	int		i;
	SDL_Rect pos;

	i = -1;
	while (data->font.str[++i])
	{
		data->font.pos = set_font_pos(data->font.str[i]);
		pos.w = size;
		pos.h = size;
		pos.x = x + ((pos.w - (size / 3)) * i);
		pos.y = y;
		if (data->font.str[i] < 'a')
			SDL_RenderCopy(data->window.rend, data->font.font_maj, &data->font.pos, &pos);
		else
			SDL_RenderCopy(data->window.rend, data->font.font, &data->font.pos, &pos);
	}
	if (data->font.str)
		free(data->font.str);
	return (0);
}

static SDL_Texture	*load_txt(t_data *data, char *path)
{
	t_tga 		*load;
	SDL_Surface	*s;
	SDL_Texture	*ret;

	ret = NULL;
	load = load_tga(path);
	if (load != NULL && load->data != NULL)
	{
		s = SDL_CreateRGBSurfaceFrom(load->data, load->w, load->h,
			32, load->w * 4, 0xFF00, 0xFF0000, 0xFF000000, 0xFF);
		free_tga(load);
		if (s != NULL)
		{
			ret = SDL_CreateTextureFromSurface(data->window.rend, s);
			SDL_FreeSurface(s);
		}
	}
	return (ret);
}

int					init_font(t_data *data)
{
	if ((data->font.font_maj = load_txt(data, "./texture/maj.tga")) == NULL)
		return (1);
	if ((data->font.font = load_txt(data, "./texture/low.tga")) == NULL)
		return (1);
	return (0);
}
