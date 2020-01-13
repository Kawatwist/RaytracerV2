/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:45 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/13 20:58:53 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		parsing_files2(t_data *data, char **old, char **line)
{
	if (!ft_strncmp("[camera", *line, 7))
	{
		if (parsing_camera(data, old))
			return (11);
	}
	else if (!ft_strncmp("[object", *line, 7))
	{
		if (parsing_obj(data, old, *line))
			return (11);
	}
	else if (!ft_strncmp("[light", *line, 6))
	{
		if (parsing_light(data, old, *line))
			return (11);
	}
	else if (ft_strchr(*line, '#'))
		;
	else
		return (11);
	return (0);
}

int				parsing_files(t_data *data, char *old)
{
	char *line;

	line = NULL;
	create_camera(data);
	create_item(data);
	create_light(data);
	create_texture(data);
	create_normal(data);
	while (old != NULL || get_next_line(data->parse.fd, &line))
	{
		if (old != NULL)
		{
			line = old;
			old = NULL;
		}
		if (parsing_files2(data, &old, &line) == 0)
			;
		else
			return (11);
		free(line);
	}
	return (0);
}
