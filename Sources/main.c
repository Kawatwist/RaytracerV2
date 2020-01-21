/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:29:35 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/21 20:58:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int argc, char *argv[])
{
	int			value;
	t_data		data;

	if ((value = initialize(&data)) != 0)
		return (stop_main_execute("Error Initalize : ", &data, value));
	if ((value = parsing(&data, argc, argv)) != 0)
		return (stop_main_execute("Error Parsing : ", &data, value));
	if ((value = check_parse(&data)) != 0)
		return (stop_main_execute("Error Parsing : ", &data, value));
	if ((value = initialize_sdl(&data)) != 0)
		return (value);
	if ((value = loop(data)) != 0 && value != 50)
		return (stop_main_execute("Error in Parse Check : ", &data, value));
	clear_memory(&data);
	ft_putstr("See you soon !\n");
	return (0);
}
