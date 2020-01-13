/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:16:57 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/13 20:49:30 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_tga(t_data *data, char *line)
{
	if (!ft_strncmp("\ttextures : ", line, 11))
	{
		if (fill_texture(data, line))
			return (11);
		return (0);
	}
	else if (!ft_strncmp("\tnormal : ", line, 10))
	{
		if (fill_normal(data, line))
			return (11);
		return (0);
	}
	return (1);
}

static int	parsing_head_v2(t_data *data, char **ret, char *line)
{
	int		val;

	while ((get_next_line(data->parse.fd, &line)) &&
			ft_strncmp("\t\t", line, 2))
	{
		if (!ft_strncmp("\tcamera : ", line, 10))
			data->obj.nb_camera = ft_atoi(&(line[10]));
		else if (!ft_strncmp("\tobject : ", line, 10))
			data->obj.nb_item = ft_atoi(&(line[10]));
		else if (!ft_strncmp("\tlight : ", line, 9))
			data->obj.nb_light = ft_atoi(&(line[9]));
		else if (!ft_strncmp("\tnb_texture : ", line, 14))
			data->obj.nb_texture = ft_atoi(&(line[14]));
		else if (!ft_strncmp("\tnb_normal : ", line, 13))
			data->obj.nb_normal = ft_atoi(&(line[13]));
		else if (!(val = is_tga(data, line)) || (line[0] == '#'))
			;
		else if (val == 11)
			return (11);
		else
			break ;
		free(line);
	}
	*ret = line;
	return (0);
}

int			parsing_head(t_data *data, char **ret)
{
	char		*line;

	line = NULL;
	while (get_next_line(data->parse.fd, &line) && line[0] == '#')
		;
	if (ft_strncmp("[header]", line, 8))
		return (11);
	if (parsing_head_v2(data, ret, line))
		return (11);
	if (ret && *ret[0] != '[')
		return (11);
	return (0);
}
