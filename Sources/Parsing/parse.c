/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:44:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/01/14 19:19:37 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		parsing(t_data *data, int nb, char *arg[])
{
	char	*line;
	int		error_value;

	line = NULL;
	if (nb != 2)
		return (10);
	if ((data->parse.fd = open(arg[1], O_RDONLY)) == -1)
		return (10);
	if ((error_value = parsing_head(data, &line)) != 0)
		return (error_value);
	if ((error_value = parsing_files(data, line)) != 0)
		return (error_value);
	data->percent = 0;
	if ((error_value = initialize_cam(data)) != 0)
		return (error_value);
	return (0);
}
