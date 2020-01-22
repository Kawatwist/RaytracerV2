/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/22 20:49:06 by lomasse          ###   ########.fr       */
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
       if ((err = pthread_create(&((t_thread*)data->thread)[i].thd, NULL, &thread_function, &((t_thread*)data->thread)[i])) != 0)
            return (err);
    }
    return (0);
}