/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/24 19:44:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

int     start_thread(t_data *data)
{
    int     i;
    int     err;

    i = -1;
    while (++i < 4)
    {
        ((t_thread *)data->thread)[i].percent = data->percent;
        ((t_thread *)data->thread)[i].bounce = data->bounce;
        ((t_thread *)data->thread)[i].len = (data->window.x * data->window.y) >> 2;
        ((t_thread *)data->thread)[i].pxl = &(((unsigned char *)data->window.pxl)[(((t_thread *)data->thread)[i].len * i) << 2]);
       if ((err = pthread_create(&((t_thread*)data->thread)[i].thd, NULL, &thread_function, &((t_thread*)data->thread)[i])) != 0)
            return (err);
    }
    i = -1;
    while (++i < 4)
        pthread_join(((t_thread *)data->thread)[i].thd, NULL);
    return (0);
}