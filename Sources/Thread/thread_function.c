/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:16:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/29 15:50:01 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void				*thread_function(void *arg)
{
	t_thread		*data;
	int				x;
	int				y;
	int				curr;

	data = arg;
	curr = -1;
	data->signal = THREAD_ALIVE;
	while (++curr < data->len)
	{
		data->current = curr;
		if (!data->flag.screen && quitrequested(data) == THREAD_SIG)
			pthread_exit(NULL);
		if (data->flag.antialiasing == 0)
			basic_render(data, &curr);
		else
			aa_render(data, &x, &y, &curr);
		if (!(curr % 1000) && data->flag.time)
			SDL_Delay(2);
	}
	data->signal = NOTHREAD;
	return (arg);
}
