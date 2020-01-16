/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:44:09 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/15 23:55:26 by luwargni         ###   ########.fr       */
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
		else if (!ft_strncmp("\tcolor : ", line, 9))
			data->obj.light[index].color = ft_atoi_base(line + 9, 16);
		else if (!ft_strncmp("\tdistance : ", line, 12))
			data->obj.light[index].distance = ft_atof(line + 12);
		else if (!ft_strncmp("\tintensity : ", line, 13))
			data->obj.light[index].intensity = ft_atof(line + 13);
		else if (ft_strchr(line, '#'))
			;
		else
			break;
		free(line);
	}
	data->parse.error_line -= 1;
	*old = line;
	index++;
	return (0);
}
