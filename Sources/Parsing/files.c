/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:14:45 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/14 19:21:24 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		parsing_files2(t_data *data, char **old, char **line)
{
	static int	curr = 12;

	if (!ft_strncmp("[camera", *line, 7))
	{
		curr = 14;
		parsing_camera(data, old);
	}
	else if (!ft_strncmp("[object", *line, 7))
	{
		curr = 15;
		parsing_obj(data, old, *line);
	}
	else if (!ft_strncmp("[light", *line, 6))
	{
		curr = 16;
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
	int		error_value;

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
		printf("Parsing Files : %d\n", error_value);
		if ((error_value = parsing_files2(data, &old, &line)) == 0)
			;
		else
			return (error_value);
		free(line);
	}
	return (0);
}
