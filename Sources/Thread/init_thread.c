/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:05 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/22 22:34:12 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void			reset_item(t_object base, t_object *dest)
{
	int		i;

	ft_memcpy(&dest->camera, &base.camera, sizeof(t_camera) * base.nb_camera);
	ft_memcpy(&dest->light, &base.light, sizeof(t_light) * base.nb_light);
	i = -1;
	while (++i < base.nb_item)
		if (base.item[i] != NULL)
			ft_memcpy(&dest->item[i], &base.item[i], sizeof(t_camera) * base.nb_camera);
}

static int		copy_item(t_object base, t_object *dest)
{
	static	size_t	tab[4] = {sizeof(t_sphere)
			, sizeof(t_plan), sizeof(t_cone), sizeof(t_cylinder)};
	int		i;

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

static int		init_thread_memory(t_object base, t_object *dest)
{
	ft_memcpy(dest, &base, sizeof(t_object));
	if ((dest->camera = malloc(sizeof(t_camera) * base.nb_camera)) == NULL)
		return (1);
	ft_memcpy(dest->camera, base.camera, sizeof(t_camera) * base.nb_camera - 1);
	if ((dest->light = malloc(sizeof(t_light) * base.nb_light)) == NULL)
		return (1);
	ft_memcpy(dest->light, base.light, sizeof(t_light) * base.nb_light);
	if ((dest->item = malloc(sizeof(void *) * base.nb_item)) == NULL)
		return (1);
	ft_bzero(dest->item, sizeof(void *) * base.nb_item);
	if (copy_item(base, dest) != 0) // COPY TEXTURE ?
		return (1);
	/*
	**	Fill The all struct
	**	Malloc Pointer tab
	**	Malloc Sub Pointer
	**	Fill Them
	*/
	return (0);
}

static void	fill_data(t_data *data, t_data *new)
{
	ft_memcpy(new, data, sizeof(t_data));
	ft_memcpy(&new->dist, &data->dist, sizeof(data->dist) * 4);
	ft_memcpy(&new->txt, &data->txt, sizeof(data->txt) * 4);
	ft_memcpy(&new->move, &data->move, sizeof(data->move) * 4);
	ft_memcpy(&new->cond, &data->cond, sizeof(data->cond) * 4);
}

int         init_thread(t_data *data, int nb)
{
	static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	static int		i = -1;

	if ((data->thread = malloc(sizeof(t_thread) * nb)) == NULL)
		return (1);
	while (++i < nb)
	{
		fill_data(data, &((t_thread *)data->thread)[nb].data);
		init_thread_memory(data->obj, &(((t_thread *)data->thread)[nb].obj));
		((t_thread *)data->thread)[nb].x = data->window.x;
		((t_thread *)data->thread)[nb].y = data->window.y;
		((t_thread *)data->thread)[nb].index = nb;
		((t_thread *)data->thread)[nb].len = 0;
		((t_thread *)data->thread)[nb].pxl = NULL;
		((t_thread *)data->thread)[nb].data.obj = ((t_thread *)data->thread)[nb].obj;
		((t_thread *)data->thread)[nb].cond = cond;
		((t_thread *)data->thread)[nb].mutex = mut;
		/*
		**	Setup Memory
		**	Setup Mutex
		**	Init Everything
		*/
	}
	data->cond = cond;
	data->mutex = mut;
	pthread_mutex_lock(&data->mutex);
	return (0);
}

int			get_thread(t_data *data)
{
	int				err;

	if ((err = init_thread(data, 4)) != 0)
		return (err);
	if ((err = start_thread(data)) != 0)
		return (err);
	return (0);
}