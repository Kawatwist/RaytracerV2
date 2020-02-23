/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_txt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:08:24 by lomasse           #+#    #+#             */
/*   Updated: 2020/02/22 22:25:39 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static int		setup_normal(t_data *data, t_thread *tmp, t_tga *tgamp)
{
	int		j;
	if ((tmp->normal = malloc(sizeof(void *)
		* data->obj.nb_normal)) == NULL)
		return (1);
	ft_bzero(tmp->normal, sizeof(void *) * data->obj.nb_normal);
	j = -1;
	while (++j < data->obj.nb_normal)
	{
		if (data->normal[j] != NULL)
		{
			if ((tgamp = malloc(sizeof(t_tga))) == NULL)
				return (1);
			if ((tgamp->data = malloc(((size_t)(data->normal[j]->w *
				data->normal[j]->h) * 4))) == NULL)
				return (1);
			tgamp->w = data->normal[j]->w;
			tgamp->h = data->normal[j]->h;
			ft_memcpy((tgamp->data), (data->normal[j]->data),
				((size_t)(data->normal[j]->w * data->normal[j]->h) * 4));
			tmp->normal[j] = tgamp;
		}
	}
	return (0);
}

int			setup_txt_and_normal(t_data *data, t_thread *tmp)
{
	int				j;
	t_tga			*tgamp;

	if (!(tmp->texture = ft_memalloc(sizeof(void *) * data->obj.nb_texture)))
		return (1);
	ft_bzero(tmp->texture, sizeof(void *) * data->obj.nb_texture);
	j = -1;
	while (++j < data->obj.nb_texture)
	{
		if (data->texture[j] != NULL)
		{
			if ((tgamp = malloc(sizeof(t_tga))) == NULL)
				return (1);
			if ((tgamp->data = malloc(((size_t)(data->texture[j]->w *
				data->texture[j]->h) * 4))) == NULL)
				return (1);
			tgamp->w = data->texture[j]->w;
			tgamp->h = data->texture[j]->h;
			ft_memcpy((tgamp->data), (data->texture[j]->data),
				((size_t)(data->texture[j]->w * data->texture[j]->h) * 4));
			tmp->texture[j] = tgamp;
		}
	}
	setup_normal(data, tmp, tgamp);
	return (0);
}
