/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:29:35 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/23 19:10:39 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			runtime(t_data *data)
{
	int		value;

	if ((value = initialize_sdl(data)) != 0)
		return (stop_main_execute("Error Initialize SDL : ", data, value));
	if ((value = set_icone(data)) != 0)
		return (stop_main_execute("Icon Not Setup Correctly : ", data, value));
	if ((value = loop(data)) != 0 && value != 50)
		return (stop_main_execute("Run Stopped : ", data, value));
	return (0);
}

int			main(int argc, char *argv[])
{
	int			value;
	t_data		data;

	if (argc < 2)
	{
		ft_putendl("Usage : ./rt [Map.rt]");
		return (0);
	}
	if ((value = initialize(&data)) != 0)
		return (stop_main_execute("Error Initalize : ", &data, value));
	if ((value = flag(&data, argc, argv)) != 0)
		return (stop_main_execute("Error Flag : ", &data, value));
	if ((value = parsing(&data, argc, argv)) != 0)
		return (stop_main_execute("Error Parsing : ", &data, value));
	if ((value = check_parse(&data)) != 0)
		return (stop_main_execute("Error Parse Check : ", &data, value));
	if (data.flag.screen)
		single_screen(&data);
	else if ((value = runtime(&data)))
		return (value);
	clear_memory(&data);
	ft_putstr("See you soon !\n");
	return (0);
}
