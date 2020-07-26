/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:49:42 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/25 13:48:56 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	first_normal(t_data *data)
{
	int	i;

	i = 0;
	if ((data->obj.normal = malloc(sizeof(char *) *
			data->obj.nb_normal + 1)) == NULL)
		return (1);
	while (i < data->obj.nb_normal)
	{
		data->obj.normal[i] = NULL;
		i++;
	}
	return (0);
}

int			fill_normal(t_data *data, char *line)
{
	static int	index = 0;
	int			len;

	if (index >= data->obj.nb_normal)
		return (14);
	if (index == 0)
		if (first_normal(data))
			return (1);
	len = ft_strrchr(line, '"') - ft_strchr(line, '"') - 1;
	if (!(len > 0 && len < 100))
		return (14);
	data->obj.normal[index] = ft_strndup(ft_strchr(line, '"') + 1, len);
	index++;
	return (0);
}

static int	first_texture(t_data *data)
{
	int	i;

	i = 0;
	if ((data->obj.texture = malloc(sizeof(char *) *
		data->obj.nb_texture + 1)) == NULL)
		return (1);
	while (i < data->obj.nb_texture)
	{
		data->obj.texture[i] = NULL;
		i++;
	}
	return (0);
}

int			fill_texture(t_data *data, char *line)
{
	static int	index = 0;
	int			len;

	if (index >= data->obj.nb_texture)
		return (14);
	if (index == 0)
		if (first_texture(data))
			return (1);
	len = ft_strrchr(line, '"') - ft_strchr(line, '"') - 1;
	if (!(len > 0 && len < 100))
		return (14);
	if ((data->obj.texture[index] =
		ft_strndup(ft_strchr(line, '"') + 1, len)) == NULL)
		return (14);
	index++;
	return (0);
}
