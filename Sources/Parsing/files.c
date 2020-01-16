/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:45 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/15 23:54:14 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		parsing_files2(t_data *data, char **old, char **line)
{
	static int	curr = 12;

	if (!ft_strncmp("[camera", *line, 7))
	{
		curr = 16;
		parsing_camera(data, old);
	}
	else if (!ft_strncmp("[object", *line, 7))
	{
		curr = 17;
		parsing_obj(data, old, *line);
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
	char	*line;
	int		er;

	line = NULL;
	if ((er = create_camera(data)) || (er = create_item(data)) ||
		(er = create_light(data)) || (er = create_texture(data)) ||
		(er = create_normal(data)))
		return (er);
	while (old != NULL || get_next_line(data->parse.fd, &line))
	{
		if (old != NULL)
		{
			line = old;
			old = NULL;
		}
		data->parse.error_line += 1;
		if ((er = parsing_files2(data, &old, &line)) == 0)
			;
		else
			return (er);
		free(line);
	}
	return (0);
}
