/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 18:25:17 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/03 23:28:47 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		preset_cam(t_data *data, int index)
{
	float	coef;

	(data->obj.camera[index]).sc =
		add_vec((data->obj.camera[index]).pos.origin,
			fill_vec(-0.5, -0.5, 0.5));
	if (data->window.x >= data->window.y)
	{
		coef = (float)data->window.x / (float)data->window.y;
		(data->obj.camera[index]).x = fill_vec(coef / data->window.x, 0, 0);
		(data->obj.camera[index]).y = fill_vec(0, 1.0 / data->window.y, 0);
		(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).sc,
			fill_vec((1 - coef) / 2.0, 0, 0));
	}
	else
	{
		coef = (float)data->window.y / (float)data->window.x;
		(data->obj.camera[index]).x = fill_vec(1.0 / data->window.x, 0, 0);
		(data->obj.camera[index]).y = fill_vec(0, coef / data->window.y, 0);
		(data->obj.camera[index]).sc = add_vec((data->obj.camera[index]).sc,
			fill_vec(0, (1 - coef) / 2, 0));
	}
}

static int		init_cam(t_data *data)
{
	int			index;
	t_point		direction;
	t_point		base;

	index = 0;
	while (index < data->obj.nb_camera)
	{
		direction = normalize((data->obj.camera[index]).pos.direction);
		base = fill_vec(0, 0, 1);
		preset_cam(data, index);
		data->obj.camera[index].oldpos.origin =
			veccpy(data->obj.camera[index].pos.origin);
		data->obj.camera[index].oldpos.direction =
			veccpy(data->obj.camera[index].pos.direction);
		data->obj.camera[index].oldsc = veccpy(data->obj.camera[index].sc);
		data->obj.camera[index].oldx = veccpy(data->obj.camera[index].x);
		data->obj.camera[index].oldy = veccpy(data->obj.camera[index].y);
		index++;
	}
	return (0);
}

void			create_menu_texture(t_data *data)
{
	data->menu.background = SDL_CreateTexture(data->window.rend,
	SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, 300, data->window.y);
	// Move to Interface ?
}

static void		resize_size(t_data *data, int check[2])
{
	data->flag.asked = 1;
	if (check[0] < 600)
		check[0] = 600;
	if (check[1] < 600)
		check[1] = 601;
	data->window.x = check[0];
	data->window.y = check[1];
	if (check[1] % 4)
	{
		SDL_SetWindowSize(data->window.window, check[0], check[1] +
			(4 - (check[1] % 4)));
		check[1] = check[1] + (4 - (check[1] % 4));
	}
	else
		SDL_SetWindowSize(data->window.window, check[0], check[1]);
}

static void		resize_thread(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		((t_thread *)data->thread)[i].x = data->window.x;
		((t_thread *)data->thread)[i].y = data->window.y;
		ft_memcpy((((t_thread *)data->thread)[i].obj.camera),
			(data->obj.camera), sizeof(t_camera) * data->obj.nb_camera);
		((t_thread *)data->thread)[i].obj.nb_camera = data->obj.nb_camera;
	}
}

void			resize(t_data *data)
{
	static int	x;
	static int	y;
	int			check[2];

	x = data->window.x;
	y = data->window.y;
	SDL_GetWindowSize(data->window.window, &check[0], &check[1]);
	if (x != check[0] || y != check[1])
	{
		resize_size(data, check);
		create_menu_texture(data);
		SDL_DestroyTexture(data->window.txt);
		SDL_DestroyTexture(data->window.oldtxt);
		data->window.txt = SDL_CreateTexture(data->window.rend,
			SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
			data->window.y);
		data->window.oldtxt = SDL_CreateTexture(data->window.rend,
			SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, data->window.x,
			data->window.y);
		init_cam(data);
		resize_thread(data);
	}
}
