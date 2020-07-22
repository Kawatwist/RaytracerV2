/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:02:33 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 20:37:43 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		clear_texture(t_data *data, t_tga **tofree)
{
	int		i;

	i = -1;
	if (tofree != NULL)
	{
		while (++i < data->obj.nb_texture - 1)
			(tofree[i]) != NULL ? free_tga(tofree[i]) : 0;
		if (tofree != NULL)
			free((tofree));
	}
}

static void		clear_obj_item(t_data *data, t_object tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_item - 1 && (tofree).item)
		tofree.item[i] != NULL ? free(tofree.item[i]) : 0;
	if (tofree.item != NULL)
		free(tofree.item);
}

static void		clear_normal(t_data *data, t_tga **tofree)
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

static void		destroy_text(SDL_Texture *t)
{
	if (t != NULL)
	{
		SDL_DestroyTexture(t);
		t = NULL;
	}
}

//
/*
**	Destroy Window ?
*/

static void		clear_cam(t_data *data, t_camera *cam)
{
	int	i;

	i = -1;
	while (++i < data->obj.nb_camera)
		cam[i].mode != 0 ? free(cam[i].stereo) : 0;
}

int				clear_memory(t_data *data)
{
	clear_texture(data, data->texture);
	clear_obj_item(data, data->obj);
	clear_normal(data, data->normal);
	clear_cam(data, data->obj.camera);
	ft_memdel((void **)&data->obj.camera);
	ft_memdel((void **)&data->obj.light);
	ft_memdel((void **)&data->input.rkey);
	destroy_text(data->load.load);
	destroy_text(data->load.loading);
	destroy_text(data->load.lolz);
	clear_thread((t_thread *)data->thread);
	return (0);
}
