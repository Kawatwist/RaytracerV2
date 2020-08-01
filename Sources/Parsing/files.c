/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:45 by luwargni          #+#    #+#             */
/*   Updated: 2020/08/01 16:28:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		parsing_files3(t_data *data, char **old, char **line)
{
	static int	curr = 12;
	int			val;

	if (!ft_strncmp("[light:", *line, 7))
	{
		curr = 15;
		if ((val = parsing_light(data, old, *line)))
			return (val);
	}
	else if ((*line)[0] == '#')
		;
	else
		return (curr);
	return (0);
}

static int		parsing_files2(t_data *data, char **old, char **line)
{
	static int	curr = 12;
	int			val;

	if (!ft_strncmp("[camera:", *line, 8))
	{
		curr = 16;
		if ((val = parsing_camera(data, old)))
			return (val);
	}
	else if (!ft_strncmp("[object:", *line, 8))
	{
		curr = 17;
		if ((val = parsing_obj(data, old, *line)))
			return (val);
	}
	else if (!ft_strncmp("[gen:torus", *line, 10))
	{
		curr = 99;
		if ((val = parsing_torus(data, old, *line)))
			return (val);
	}
	else
	{
		if ((val = parsing_files3(data, old, line)))
			return (val);
		return (0);
	}
	return (0);
}

int				parsing_files(t_data *data, char *old)
{
	char		*line;
	int			er;

	line = NULL;
	if ((er = create_camera(data)) ||
		(er = create_item(data)) ||
		(er = create_light(data)) ||
		(er = create_texture(data)) ||
		(er = create_normal(data)))
		return (er);
	while (old != NULL || get_next_line(data->parse.fd, &line))
	{
		old != NULL ? line = old : 0;
		old != NULL ? old = NULL : 0;
		data->parse.error_line += 1;
		if ((er = parsing_files2(data, &old, &line)) != 0)
		{
			ft_memdel((void **)&line);
			return (er);
		}
		ft_memdel((void **)&line);
	}
	return (0);
}
