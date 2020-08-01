/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_torus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 15:38:32 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/01 16:39:08 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static t_sphere	*around_axe(t_sphere *sphere,
		t_data *data, int index, int value)
{
	if (!data->obj.generate[index].axe)
		((t_sphere *)sphere)->origin.origin =
			add_vec(data->obj.generate[index].origin,
			roty(fill_vec(0, 0, data->obj.generate[index].rayon_i),
			360.0 * ((float)value / (float)data->obj.generate[index].nb)));
	else if (data->obj.generate[index].axe == 1)
		((t_sphere *)sphere)->origin.origin =
			add_vec(data->obj.generate[index].origin,
			rotx(fill_vec(0, 0, data->obj.generate[index].rayon_i),
			360.0 * ((float)value / (float)data->obj.generate[index].nb)));
	else
		((t_sphere *)sphere)->origin.origin =
			add_vec(data->obj.generate[index].origin,
			rotz(fill_vec(0, 0, data->obj.generate[index].rayon_i),
			360.0 * ((float)value / (float)data->obj.generate[index].nb)));
	return (sphere);
}

static int		generate(t_data *data, int index)
{
	int		value;
	int		find;
	void	*sphere;

	find = 0;
	while (data->obj.item[find] != NULL)
		find++;
	value = 0;
	if (data->obj.generate[index].nb + find > data->obj.nb_item)
		return (97);
	while (value <= data->obj.generate[index].nb)
	{
		if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
			return (1);
		ft_memcpy(sphere, &data->obj.generate[index].sphere, sizeof(t_sphere));
		data->obj.item[find + value] = around_axe(sphere, data, index, value);
		value++;
	}
	return (0);
}

static int		parsing_torus2(t_data *data, char **line, int index)
{
	if (!(ft_strncmp("\tnb :", *line, 5)))
		data->obj.generate[index].nb = lowu(ft_atoi(*line + 5), 300);
	else if (!(ft_strncmp("\trayon_i :", *line, 10)))
		data->obj.generate[index].rayon_i = ft_atof(*line + 10);
	else if (!(ft_strncmp("\trayon : ", *line, 9)))
		data->obj.generate[index].sphere.rayon = ft_atof(*line + 9);
	else if (!ft_strncmp("\torigin :", *line, 9))
		data->obj.generate[index].origin = get_point(*line);
	else if (!ft_strncmp("\tcolor :", *line, 8))
		data->obj.generate[index].sphere.effect.color =
		((ft_atoi_base(*line + 11, 16) & 0xFFFFFF) + (255 << 24));
	else if (!fill_effect(&(data->obj.generate[index].sphere.effect),
			*line))
		return (0);
	else if (!(ft_strncmp("\taxe :", *line, 6)))
		data->obj.generate[index].axe = ft_atoi(*line + 6);
	else
		return (99);
	return (0);
}

int				parsing_torus(t_data *data, char **old, char *line)
{
	static int	index = 0;
	int			val;

	if (index > data->generate)
		return (98);
	line = NULL;
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1))
	{
		if ((val = parsing_torus2(data, &line, index)))
		{
			free(line);
			return (val);
		}
		free(line);
	}
	if ((val = generate(data, index)))
		return (val);
	*old = line;
	index++;
	return (0);
}
