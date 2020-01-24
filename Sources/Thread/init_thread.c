/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:05 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/24 20:40:16 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static int		setup_txt_and_normal(t_data *data, t_thread *tmp)
{
	int				j;
	t_tga			*tgamp;

	if ((tmp->texture = malloc(sizeof(t_tga **) * data->obj.nb_texture)) == NULL)
		return (1);
	ft_bzero(tmp->texture, sizeof(t_tga **) * data->obj.nb_texture);
	j = -1;
	while (++j < data->obj.nb_texture)
	{
		if (data->texture[j] != NULL)
		{
			if ((tgamp = malloc(sizeof(t_tga))) == NULL)
				return (1);
			if ((tgamp->data = malloc(((size_t)(data->texture[j]->w * data->texture[j]->h) * 4))) == NULL)
				return (1);
			(*tmp).texture[j] = tgamp;
			ft_memcpy(((*tmp).texture[j]->data), (data->texture[j]->data), ((size_t)(data->texture[j]->w * data->texture[j]->h) * 4));
		}
	}
	if (((*tmp).normal = malloc(sizeof(t_tga **) * data->obj.nb_normal)) == NULL)
		return (1);
	ft_bzero(tmp->normal, sizeof(t_tga **) * data->obj.nb_normal);
	j = -1;
	while (++j < data->obj.nb_normal)
	{
		if (data->normal[j] != NULL)
		{
			if ((tgamp = malloc(sizeof(t_tga))) == NULL)
				return (1);
			if ((tgamp->data = malloc(((size_t)(data->normal[j]->w * data->normal[j]->h) * 4))) == NULL)
				return (1);
			(*tmp).normal[j] = tgamp;
			ft_memcpy(((*tmp).normal[j]->data), (data->normal[j]->data), ((size_t)(data->normal[j]->w * data->normal[j]->h) * 4));
		}
	}
	return (0);
}

static void		setup_function(t_thread *tmp)
{
	(*tmp).dist[0] = sphere;
	(*tmp).dist[1] = plane;
	(*tmp).dist[2] = cone;
	(*tmp).dist[3] = cylinder;
	(*tmp).txt[0] = texture_sphere;
	(*tmp).txt[1] = texture_plan;
	(*tmp).txt[2] = texture_cone;
	(*tmp).txt[3] = texture_cylinder;
	(*tmp).move[0] = move_cam;
	(*tmp).move[1] = move_obj;
	(*tmp).move[2] = move_light;
}

static int		setup_struct(t_data *data, t_thread *tmp)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		tmp[i].x = data->window.x;
		tmp[i].y = data->window.y;
		tmp[i].pxl = NULL;
		ft_memcpy(&tmp[i].flag, &data->flag, sizeof(t_flag));
		tmp[i].ray.origin = fill_vec(0, 0, 0);
		tmp[i].ray.direction = fill_vec(0, 0, 1);
		if (setup_txt_and_normal(data, &(tmp[i])))
			return (1);
		setup_function(&(tmp[i]));
		tmp[i].percent = data->percent;
		tmp[i].bounce = data->bounce;
		tmp[i].pos = i * ((data->window.y * data->window.x) >> 2);
	}
	return (0);
}

static int		copy_item(t_object base, t_object *dest, int nb)
{
	static	size_t	tab[4] = {sizeof(t_sphere)
			, sizeof(t_plan), sizeof(t_cone), sizeof(t_cylinder)};
	int		i;

	ft_bzero(dest->item, sizeof(void *) * nb + 1);
	i = -1;
	while (++i < base.nb_item)
	{
		if (base.item[i] != NULL)
		{
			if ((dest->item[i] = malloc(tab[(int)((t_base *)base.item[i])->effect.type])) == NULL)
				return (1);
			ft_memcpy(dest->item[i], base.item[i], tab[(int)((t_base *)base.item[i])->effect.type]); 
		}
		else
			dest->item[i] = NULL;
	}
	return (0);
}

static int		setup_obj(t_data *data, t_thread *tmp)
{
	int	i;

	ft_memcpy(&tmp->obj, &data->obj, sizeof(t_object));
	i = -1;
	while (++i < 4)
		if ((tmp[i].obj.item = malloc(sizeof(void *) * data->obj.nb_item + 1)) == NULL)
			return (1);
	i = -1;
	while (++i < 4)
	{
		if ((tmp[i].obj.light = malloc(sizeof(t_light) * data->obj.nb_light)) == NULL)
			return (1);
		ft_memcpy(&tmp[i].obj.light, &data->obj.light, sizeof(t_light) * data->obj.nb_light);
	}
	i = -1;
	while (++i < 4)
	{
		if ((tmp[i].obj.camera = malloc(sizeof(t_camera) * data->obj.nb_camera)) == NULL)
			return (1);
		ft_memcpy(&tmp[i].obj.light, &data->obj.light, sizeof(t_light) * data->obj.nb_light);
	}
	i = -1;
	while (++i < 4)
		if (copy_item(data->obj, &tmp[i].obj, data->obj.nb_item) != 0)
			return (1);
	return (0);
}

int		init_thread_memory(t_data *data)
{
	t_thread	*tmp;

	if ((data->thread = malloc(sizeof(t_thread) * 4)) == NULL)
		return (1);
	tmp = data->thread;
	ft_bzero(&(*data->thread), sizeof(t_thread) * 4);
	if (setup_struct(data, tmp))
		return (1);
	if (setup_obj(data, tmp))
		return (1);
	return (0);
}