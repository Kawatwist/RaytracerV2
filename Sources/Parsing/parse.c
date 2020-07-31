/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:44:28 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/31 16:51:33 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_gen(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->generate)
	{
		ft_bzero(&data->obj.generate[i], sizeof(t_generate));
		data->obj.generate[i].rayon_i = 1;
		data->obj.generate[i].sphere.effect.color = 0xFFFFFF;
		data->obj.generate[i].sphere.rayon = 0.33;
		i++;
	}
}

int			parsing(t_data *data, int nb, char *arg[])
{
	char	*line;
	int		error_value;

	line = NULL;
	if ((data->parse.fd = open(arg[nb - 1], O_RDONLY)) == -1 ||
		read(data->parse.fd, NULL, 0) || !ft_strcmp(arg[nb - 1], "/dev/zero"))
		return (10);
	if ((error_value = parsing_head(data, &line)) != 0)
		return (error_value);
	init_gen(data);
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
