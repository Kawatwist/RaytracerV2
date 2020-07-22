/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:30:22 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 21:42:58 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static int	single_loop(t_data *data)
{
	int		err;

	if ((err = start_thread(data)))
		return (err);
	generate_perlin(data);
	post_processing(data);
	data->percent++;
	if (data->percent > 99)
		data->percent = 0;
	check_folder_screenshot();
	create_screenshot(data, data->window.pxl);
	return (0);
}

int			single_screen(t_data *data)
{
	int		err;

	if (SDL_Init(SDL_INIT_EVENTS))
		return (1);
	if (!(data->window.pxl = malloc(sizeof(Uint32) * data->window.x * data->window.y)))
		return (1);
	data->obj.type_index = 0;
	if ((err = init_thread_memory(data)) != 0)
		return (err);
	single_loop(data);
	return (0);
}
