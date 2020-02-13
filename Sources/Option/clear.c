/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:02:33 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/13 04:04:10 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		clear_texture(t_data *data, t_tga **tofree)
{
	int		i;

	i = -1;
	while (i++ < data->obj.nb_texture - 1 && (tofree))
		(tofree)[i] != NULL ? free_tga((tofree)[i]) : 0;
	if (tofree != NULL)
		free((tofree));
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

static void		destroy_text(SDL_Texture *t)
{
	if (t != NULL)
		SDL_DestroyTexture(t);
}

int				clear_memory(t_data *data)
{
	printf("Segv ? [1]\n");
	clear_texture(data, data->texture);
	printf("Segv ? [2]\n");
	clear_obj_item(data, data->obj);
	printf("Segv ? [3]\n");
	clear_normal(data, data->normal);
	printf("Segv ? [4]\n");
	ft_memdel((void **)&data->obj.camera);
	ft_memdel((void **)&data->obj.light);
	ft_memdel((void **)&data->input.rkey);
	printf("Segv ? [5]\n");
	destroy_text(data->load.load);
	printf("Segv ? [6]\n");
	destroy_text(data->load.loading);
	printf("Segv ? [7]\n");
	destroy_text(data->load.lolz);
	printf("Segv ? [8]\n");
	destroy_text(data->window.txt);
	printf("Segv ? [9]\n");
	if (data->window.window != NULL)
		SDL_DestroyWindow(data->window.window);
	printf("Segv ? [10]\n");
	clear_thread(data->thread);
	printf("Segv ? [11]\n");
	ft_memdel(data->thread);
	printf("Segv ? [12]\n");
	data = NULL;
	return (0);
}
