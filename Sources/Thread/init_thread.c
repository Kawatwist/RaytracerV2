/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:05 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/22 00:02:42 by lomasse          ###   ########.fr       */
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
			ft_memcpy(dest->item[i], base.item[i], sizeof(base.item[i])); 
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
	ft_memcpy(dest->camera, base.camera, sizeof(t_camera) * base.nb_camera);
	if ((dest->light = malloc(sizeof(t_light) * base.nb_light)) == NULL)
		return (1);
	ft_memcpy(dest->light, base.light, sizeof(t_light) * base.nb_light);
	if ((dest->item = malloc(sizeof(void *) * base.nb_item)) == NULL)
		return (1);
	ft_bzero(dest->camera, sizeof(void *) * base.nb_item);
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

int         init_thread(t_data *data, t_thread *thd, int nb)
{
	static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

	while (--nb > -1)
	{
		init_thread_memory(data->obj, &(thd[nb].obj));
		thd[nb].mutex = mut;
		thd[nb].cond = cond;
		thd[nb].x = data->window.x;
		thd[nb].y = data->window.y;
		thd[nb].index = nb;
		thd[nb].len = 0;
		thd[nb].pxl = NULL;
		pthread_attr_init(&data->thd[nb]); // DESTROY AT THE END ? IDK
		thd[nb].signal = data->thd[nb];
		pthread_mutex_lock(&thd[nb].mutex);
		/*
		**	Setup Memory
		**	Setup Mutex
		**	Init Everything
		*/
	}
	return (0);
}

int			get_thread(t_data *data)
{
	int				err;
	static t_thread	thd[4];

	if ((err = init_thread(data, thd, 4)) != 0)
		return (err);
	data->thread = thd;
	if ((err = start_thread(data)) != 0)
		return (err);
	return (0);
}