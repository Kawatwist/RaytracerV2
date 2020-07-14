/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 18:25:17 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/13 17:26:00 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void			create_menu_texture(t_data *data)
{
	data->menu.background = SDL_CreateTexture(data->window.rend,
	SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, 300, data->window.y);
	// Move to Interface ?
}

static void		resize_size(t_data *data, int check[2])
{
	data->flag.asked = 1;
	if (check[0] < 800)
		check[0] = 800;
	if (check[1] < 800)
		check[1] = 801;
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
