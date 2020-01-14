/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:48:50 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/14 19:16:18 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				parsing_obj(t_data *data, char **old, char *type)
{
	static int	index = 0;
	char		*line;
	char		val;

	line = NULL;
	val = find_type(type);
	if (index >= data->obj.nb_item)
		return (11);
	if (val == NONE || create_type(data, index, val))
		return (11);
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1))
	{
		if (fill_obj(data, &line, index) == 0)
			;
		else
			return (11);
		free(line);
	}
	*old = line;
	index++;
	return (0);
}
