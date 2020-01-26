/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:45 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/26 21:05:56 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		parsing_files2(t_data *data, char **old, char **line)
{
	static int	curr = 12;
	int			val;

	if (!ft_strncmp("[camera", *line, 7))
	{
		curr = 16;
		parsing_camera(data, old);
	}
	else if (!ft_strncmp("[object", *line, 7))
	{
		curr = 17;
		if ((val = parsing_obj(data, old, *line)) != 0)
			return (val);
	}
	else if (!ft_strncmp("[light", *line, 6))
	{
		curr = 15;
		parsing_light(data, old, *line);
	}
	else if ((*line)[0] == '#')
		;
	else
		return (curr);
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
			free(line);
			return (er);
		}
		free(line);
	}
	return (0);
}
