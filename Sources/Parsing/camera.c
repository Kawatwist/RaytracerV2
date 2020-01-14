/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:06:01 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/14 21:29:04 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				parsing_camera(t_data *data, char **old)
{
	static int	index = 0;
	char		*line;

	line = NULL;
	if (index >= data->obj.nb_camera)
		return (13);
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1))
	{
		if (!ft_strncmp("\torigin : ", line, 10))
			data->obj.camera[index].pos.origin = get_point(line);
		else if (!ft_strncmp("\tdirection : ", line, 13))
			data->obj.camera[index].pos.direction = normalize(get_point(line));
		else if (ft_strchr(line, '#'))
			;
		else
			break;
		free(line);
	}
	*old = line;
	index++;
	return (0);
}
