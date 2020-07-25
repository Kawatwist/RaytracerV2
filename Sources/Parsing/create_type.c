/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:11 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/25 12:18:09 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				create_light(t_data *data)
{
	if (data->obj.nb_light == 0)
		data->obj.nb_light = 1;
	if ((data->obj.light =
	malloc(sizeof(t_light) * (data->obj.nb_light + 2))) == NULL)
		return (1);
	ft_bzero(data->obj.light, sizeof(t_light) * (data->obj.nb_light + 2));
	return (0);
}

int				create_camera(t_data *data)
{
	if (data->obj.nb_camera == 0)
		data->obj.nb_camera = 1;
	if ((data->obj.camera =
	malloc(sizeof(t_camera) * (data->obj.nb_camera + 1))) == NULL)
		return (1);
	ft_bzero(data->obj.camera, sizeof(t_camera) * (data->obj.nb_camera + 1));
	return (0);
}

int				create_normal(t_data *data)
{
	t_tga	*img;
	int		index;

	if (data->obj.nb_normal < 0)
		data->obj.nb_normal = 0;
	if ((data->normal = malloc(sizeof(t_tga *) * data->obj.nb_normal)) == NULL)
		return (1);
	ft_bzero(data->normal, sizeof(t_tga*) * data->obj.nb_normal);
	index = 0;
	while (index < data->obj.nb_normal && data->obj.normal[index])
	{
		img = load_tga(data->obj.normal[index]);
		if (img == NULL)
			img = load_tga("./Assets/Invalid.tga");
		data->normal[index] = img;
		index++;
	}
	return (0);
}

int				create_texture(t_data *data)
{
	t_tga	*img;
	int		index;

	if (data->obj.nb_texture < 0)
		data->obj.nb_texture = 0;
	if ((data->texture =
	malloc(sizeof(t_tga *) * data->obj.nb_texture)) == NULL)
		return (1);
	ft_bzero(data->texture, sizeof(t_tga*) * data->obj.nb_texture);
	index = 0;
	while (index < data->obj.nb_texture)
	{
		img = load_tga(data->obj.texture[index]);
		if (img == NULL)
			img = load_tga("./Assets/Invalid.tga");
		free(data->obj.texture[index]);
		data->texture[index] = img;
		index++;
	}
	free(data->obj.texture);
	return (0);
}

int				create_item(t_data *data)
{
	int		i;

	if (data->obj.nb_item < 0)
		data->obj.nb_item = 0;
	if ((data->obj.item =
	malloc(sizeof(void *) * (data->obj.nb_item + 1))) == NULL)
		return (1);
	i = -1;
	while (++i <= data->obj.nb_item)
		data->obj.item[i] = NULL;
	data->obj.item[data->obj.nb_item - 1] = NULL;
	data->obj.item[data->obj.nb_item] = NULL;
	return (0);
}
