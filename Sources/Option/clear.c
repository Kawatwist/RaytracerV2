/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:02:33 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/25 12:11:58 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		clear_obj_item(t_data *data, t_object tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_item - 1)
		tofree.item[i] != NULL ? free(tofree.item[i]) : 0;
	if (tofree.item != NULL)
		free(tofree.item);
}

static void		clear_sdl(t_data *data)
{
	if (data->window.window)
		SDL_DestroyWindow(data->window.window);
	if (SDL_WasInit(SDL_INIT_VIDEO))
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
}

int				clear_memory(t_data *data)
{
	int	i;

	clear_texture_main(data, data->texture);
	data->flag.parsing ? clear_obj_item(data, data->obj) : 0;
	clear_normal_main(data, data->normal);
	i = -1;
	while (++i < data->obj.nb_camera && data->flag.parsing)
		data->obj.camera[i].mode ? free(data->obj.camera[i].stereo) : 0;
	ft_memdel((void **)&data->obj.camera);
	ft_memdel((void **)&data->obj.light);
	ft_memdel((void **)&data->input.rkey);
	destroy_text_main(data->load.load);
	destroy_text_main(data->load.loading);
	data->flag.parsing ? clear_thread((t_thread *)data->thread) : 0;
	clear_sdl(data);
	return (0);
}
