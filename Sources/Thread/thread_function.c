/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:16:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/22 00:29:08 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void		*thread_function(void	*arg)
{
	t_thread		*data;
	unsigned int	ray;

	data = arg;
	while (TRUE)
	{
		pthread_cond_signal(&data->cond);
		pthread_cond_wait(&data->cond, &data->mutex);
		pthread_mutex_unlock(&data->mutex);
		ray = -1;
		while (++ray < data->len)
		{
			printf("HOLALA J'ENVOI UN RAYON EN [%d] Avec Len : [%d] Pixel\tPOS : [%d]\n", ray, data->len, data->index);
			// Cast Ray And Get The Color
			// Store The Color At the Right Place
			// Index Is The Position On The All Screen
			// Don't Store in The Index Pos
			// Need to use ray (data->pxl[ray] = color)
			break ;
		}
		pthread_mutex_lock(&data->mutex);
	}
	return (arg);
}