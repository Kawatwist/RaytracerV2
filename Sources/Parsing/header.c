/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:16:57 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/28 14:50:06 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static int	is_tga(t_data *data, char *line)
{
	int		ret;

	if (!ft_strncmp("\ttextures : ", line, 11))
	{
		if ((ret = fill_texture(data, line)))
			return (ret);
		return (0);
	}
	else if (!ft_strncmp("\tnormal : ", line, 10))
	{
		if ((ret = fill_normal(data, line)))
			return (ret);
		return (0);
	}
	return (-1);
}

static int	parsing_head_v4(t_data *data, char *line)
{
	if (!ft_strncmp("\tambiant : ", line, 11))
		data->ambiant = set_ambiant(ft_atoi_base(&(line[11]), 16), 5);
	else if (!ft_strncmp("\tquality : ", line, 11))
		data->flag.pixel = (unsigned int)ft_atoi(&(line[11])) & 3;
	else if (!ft_strncmp("\taa : ", line, 6))
		data->flag.antialiasing =
			((unsigned int)ft_atoi(&(line[6])) & 0b11);
	else if (!ft_strncmp("\topti : ", line, 8))
		data->max_dist = ft_atoi(&(line[8]));
	else if (!ft_strncmp("\tscreenshot : ", line, 14))
		data->flag.screen = ft_atoi(&(line[14])) & 0b1;
	else if (!ft_strncmp("\ticone : ", line, 9))
		data->flag.icon = ft_atoi(&(line[9])) & 0b1;
	else if (!ft_strncmp("\ttile : ", line, 8))
	{
		data->tile = ft_atof(&(line[8]));
		data->flag.tile = 1;
	}
	else
		return (1);
	return (0);
}

static int	parsing_head_v3(t_data *data, char *line)
{
	if (!ft_strncmp("\txscreen : ", line, 11))
		data->window.x = maxu(ft_atoi(&(line[11])), 1000);
	else if (!ft_strncmp("\tyscreen : ", line, 11))
		data->window.y = maxu(ft_atoi(&(line[11])), 1000);
	else if (!ft_strncmp("\tbounce : ", line, 10))
		data->bounce = lowu(ft_atoi(&(line[10])), 500);
	else if (!ft_strncmp("\tcamera : ", line, 10))
		data->obj.nb_camera = lowu(ft_atoi(&(line[10])), 20);
	else if (!ft_strncmp("\tlight : ", line, 9))
		data->obj.nb_light = lowu(ft_atoi(&(line[9])), 20);
	else if (!ft_strncmp("\tobject : ", line, 10))
		data->obj.nb_item = lowu(ft_atoi(&(line[10])), 100);
	else if (!ft_strncmp("\trefresh : ", line, 11))
		data->flag.refresh = (ft_atoi(&(line[11])) & 0b1);
	else if (!ft_strncmp("\tnb_normal : ", line, 13))
		data->obj.nb_normal = lowu(ft_atoi(&(line[13])), 255);
	else if (!ft_strncmp("\tflag_hud : ", line, 11))
		data->hud.flag_hud = ft_atoi(&(line[11])) & 0xb1;
	else if (parsing_head_v4(data, line))
		return (1);
	return (0);
}

static int	parsing_head_v2(t_data *data, char **ret, char *line)
{
	int		val;

	while ((get_next_line(data->parse.fd, &line)) &&
			ft_strncmp("\t\t", line, 2))
	{
		data->parse.error_line += 1;
		if ((val = parsing_head_v3(data, line)) == 0)
			;
		else if (!ft_strncmp("\tnb_texture : ", line, 14))
			data->obj.nb_texture = lowu(ft_atoi(&(line[14])), 249);
		else if (!ft_strncmp("\tfilter : ", line, 10))
			data->flag.filter = ft_atoi(&(line[10])) & 0b111;
		else if (!(val = is_tga(data, line)) || (line[0] == '#'))
			;
		else if (val == 1 || val == 14)
		{
			ft_memdel((void **)&line);
			return (val);
		}
		else
			break ;
		ft_memdel((void **)&line);
	}
	if (!line)
		return (10);
	*ret = line;
	return (0);
}

int			parsing_head(t_data *data, char **ret)
{
	char		*line;
	int			er;

	line = NULL;
	while (get_next_line(data->parse.fd, &line) && line[0] == '#')
	{
		ft_memdel((void **)&line);
		data->parse.error_line += 1;
	}
	if (!line || ft_strncmp("[header]", line, 8))
	{
		ft_memdel((void **)&line);
		return (12);
	}
	ft_memdel((void **)(&line));
	if ((er = parsing_head_v2(data, ret, line)) != 0)
		return (er);
	if (*ret && *ret[0] != '[')
	{
		if (line)
			ft_memdel((void **)&line);
		return (12);
	}
	return (0);
}
