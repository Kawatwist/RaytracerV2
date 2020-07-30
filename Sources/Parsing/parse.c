/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:44:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/30 18:11:56 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		parsing(t_data *data, int nb, char *arg[])
{
	char	*line;
	int		error_value;

	line = NULL;
	if ((data->parse.fd = open(arg[nb - 1], O_RDONLY)) == -1 ||
		read(data->parse.fd, NULL, 0) || !ft_strcmp(arg[nb - 1], "/dev/zero"))
		return (10);
	if ((error_value = parsing_head(data, &line)) != 0)
		return (error_value);
	if ((error_value = parsing_files(data, line)) != 0)
		return (error_value);
	if (!data->window.x)
		data->window.x = XSCREEN;
	if (!data->window.y)
		data->window.y = YSCREEN;
	if ((error_value = initialize_cam(data)) != 0)
		return (error_value);
	return (0);
}
