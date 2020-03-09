/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:44:09 by luwargni          #+#    #+#             */
/*   Updated: 2020/03/09 02:13:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		parsing_light(t_data *data, char **old, char *line)
{
	static int	index = 0;

	line = NULL;
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1))
	{
		data->parse.error_line += 1;
		if (!ft_strncmp("\torigin : ", line, 10))
			data->obj.light[index].origin = get_point(line);
		else if (!ft_strncmp("\tdirection : ", line, 13))
			data->obj.light[index].direction = get_point(line);
		else if (!ft_strncmp("\tspot : ", line, 8))
			data->obj.light[index].type = ft_atoi(line + 8);
		else if (!ft_strncmp("\tang : ", line, 7))
			data->obj.light[index].ang = ft_atof(line + 7);
		else if (!ft_strncmp("\tcolor : ", line, 9))
			data->obj.light[index].color = ft_atoi_base(line + 9, 16);
		else if (!ft_strncmp("\tdistance : ", line, 12))
			data->obj.light[index].distance = ft_atof(line + 12);
		else if (!ft_strncmp("\tintensity : ", line, 13))
			data->obj.light[index].intensity = ft_atof(line + 13);
		else if (!ft_strncmp("\tvariance : ", line, 12))
			data->obj.light[index].variance = ft_atof(line + 12);
		else if (ft_strchr(line, '#'))
			;
		else
			break ;
		free(line);
	}
	data->parse.error_line -= 1;
	*old = line;
	index++;
	return (0);
}
