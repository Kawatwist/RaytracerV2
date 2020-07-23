/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:10:49 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/23 18:18:28 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static void		light_variance3(t_data *data, t_thread *thd, int *i, float *tmp)
{
	*tmp > data->obj.light[*i].distancesave +
			data->obj.light[*i].variance ? *tmp =
			data->obj.light[*i].distancesave + data->obj.light[*i].variance : 0;
	*tmp < data->obj.light[*i].distancesave -
			data->obj.light[*i].variance ? *tmp =
			data->obj.light[*i].distancesave - data->obj.light[*i].variance : 0;
	*tmp < 0 ? *tmp = 0 : 0;
	thd[0].obj.light[*i].distance = *tmp;
	thd[1].obj.light[*i].distance = *tmp;
	thd[2].obj.light[*i].distance = *tmp;
	thd[3].obj.light[*i].distance = *tmp;
}

static void		light_variance2(t_data *data, t_thread *thd, int *i, float *tmp)
{
	*tmp > data->obj.light[*i].intensitysave +
			data->obj.light[*i].variance ? *tmp =
				data->obj.light[*i].intensitysave
					+ data->obj.light[*i].variance : 0;
	*tmp < data->obj.light[*i].intensitysave -
				data->obj.light[*i].variance ? *tmp =
				data->obj.light[*i].intensitysave
					- data->obj.light[*i].variance : 0;
	thd[0].obj.light[*i].intensity = *tmp;
	thd[1].obj.light[*i].intensity = *tmp;
	thd[2].obj.light[*i].intensity = *tmp;
	thd[3].obj.light[*i].intensity = *tmp;
	*tmp < 0 ? *tmp = 0 : 0;
}

void			light_variance(t_data *data, t_thread *thd)
{
	float	tmp;
	float	change;
	int		i;

	i = -1;
	while (++i < data->obj.nb_light)
	{
		if (data->obj.light[i].variance != 0)
		{
			change = data->obj.light[i].variance *
				((((rand() % 10) - 5.0) / 500.0));
			tmp = data->obj.light[i].intensity + (change / 2);
			light_variance2(data, thd, &i, &tmp);
			tmp < 0 ? tmp = 0 : 0;
			tmp = data->obj.light[i].distance + change;
			light_variance3(data, thd, &i, &tmp);
		}
	}
}
