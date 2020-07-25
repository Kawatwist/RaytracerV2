/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_font.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:50:48 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/25 12:08:53 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			special_characters(char a, SDL_Rect *pos)
{
	unsigned int count;

	if (a == '"' || a == '*')
		count = (a == '"') ? 1 : 2;
	if (a == '.' || a == '-')
		count = (a == '.') ? 0 : 3;
	else if (a == ':' || a == ' ')
		count = (a == ':') ? 4 : 5;
	pos->w = 110;
	pos->h = 115;
	pos->x = ((58 + count - '9') % 9) * pos->w;
	pos->y = 880 + (((58 + count - '9') / 9) * pos->h);
}

SDL_Rect			set_font_pos(char a)
{
	SDL_Rect	pos;

	ft_bzero(&pos, sizeof(SDL_Rect));
	pos.w = 110;
	pos.h = 115;
	if (a >= 'A' && a <= 'Z')
	{
		pos.x = ((a - 'A') % 9) * pos.w;
		pos.y = ((a - 'A') / 9) * pos.h;
	}
	else if (a >= 'a' && a <= 'z')
	{
		pos.x = ((a - 'a') % 9) * pos.w;
		pos.y = 385 + (((a - 'a') / 9) * pos.h);
	}
	else if (a >= '0' && a <= '9')
	{
		pos.x = ((a - '0') % 9) * pos.w;
		pos.y = 765 + (((a - '0') / 9) * pos.h);
	}
	else if (a == '.' || a == '"' || a == '*' ||
		a == ' ' || a == '-' || a == ':')
		special_characters(a, &pos);
	return (pos);
}

int					print_text(t_data *data, int x, int y, int size)
{
	int			i;
	SDL_Rect	pos;

	i = -1;
	while (data->font.str[++i])
	{
		data->font.pos = set_font_pos(data->font.str[i]);
		pos.w = size;
		pos.h = size;
		pos.x = x + ((pos.w - (size / 2.5)) * i);
		pos.y = y;
		SDL_RenderCopy(data->window.rend, data->font.font_maj,
			&data->font.pos, &pos);
	}
	if (data->font.str)
		free(data->font.str);
	return (0);
}

static SDL_Texture	*load_txt(t_data *data, char *path)
{
	t_tga		*load;
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
	if ((data->font.font_maj = load_txt(data, "./Assets/Letter2.tga")) == NULL)
		return (1);
	return (0);
}
