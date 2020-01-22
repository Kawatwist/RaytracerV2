/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:16:37 by lomasse           #+#    #+#             */
/*   Updated: 2020/01/22 22:42:03 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

// static	t_point	find_dir(t_data *data, int x, int y)
// {
// 	t_point		ret;

// 	ret = veccpy(data->obj.camera[data->obj.index[0]].sc);
// 	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
// 	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
// 	ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
// 	return (ret);
// }

// static void		setup_ray(t_data *data, int x, int y)
// {
// 	data->ray.origin = veccpy(data->obj.camera[data->obj.index[0]].pos.origin);
// 	data->ray.direction = normalize(find_dir(data, x, y));
// }

// void		*thread_function(void	*arg)
// {
// 	t_thread		*data;
// 	unsigned int	ray;

// 	data = arg;
// 	while (TRUE)
// 	{
// 		printf("Waiting [%d]\n", data->index);
// 		usleep(10);
// 		pthread_cond_wait(&data->cond, &data->mutex);
// 		pthread_mutex_unlock(&data->mutex);
// 		ray = -1;
// 		printf("inside\n");
// 		while (++ray < 100)
// 		{
// 			// printf("HOLALA J'ENVOI UN RAYON EN [%d] Avec Len : [%d] Pixel\tPOS : [%d]\n", ray, data->len, data->index);
// 			printf("Ray Will be Send[%d]\n", data->index);
// 			// setup_ray(&data->data, (data->index + ray) % data->x, (data->index + ray) / data->x);
// 			((unsigned int *)data->pxl)[ray] = 0xFFFFFFFF;
// 			// 		send_ray(&data->data, data->data.ray, data->bounce);
// 			// Cast Ray And Get The Color
// 			// Store The Color At the Right Place
// 			// Index Is The Position On The All Screen
// 			// Don't Store in The Index Pos
// 			// Need to use ray (data->pxl[ray] = color)
// 			break ;
// 		}
// 		pthread_cond_signal(&data->cond);
// 		pthread_mutex_lock(&data->mutex);
// 	}
// 	return (arg);
// }

void	*thread_function(void *arg)
{
	t_thread 		*data;
	Uint32			color;

	data = arg;
	while (TRUE)
	{
		printf("I will wait to start (Say : %d)\n", data->index);
		pthread_mutex_lock(&data->mutex);
		while (!data->len)
			pthread_cond_wait(&data->cond, &data->mutex);	//Wait To start
		pthread_mutex_unlock(&data->mutex);
		printf("I'm Starting to Work (NewSay : %d) FOR [%d]\n", data->index, data->len);
		while (data->len > 0)
		{
			// Find The color
			color = (Uint32)rand();
			usleep(10);
			pthread_mutex_lock(&data->mutex);
			((Uint32 *)data->pxl)[data->len] = color;
			pthread_mutex_unlock(&data->mutex);
			data->len -= 1;
		}
		printf("Work Done : (NewSay : %d)\n", data->index);
	}
	return (arg);
}