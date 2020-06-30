/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 14:24:24 by lomasse           #+#    #+#             */
/*   Updated: 2020/06/20 18:36:01 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rot_cam_video(t_data *data, t_camera *cam)
{
	(void)data;
	cam->sc = roty(cam->sc, 360.0 / (float)(data->flag.nb_video));
	cam->x = roty(cam->x, 360.0 / (float)(data->flag.nb_video));
	cam->y = roty(cam->y, 360.0 / (float)(data->flag.nb_video));
	cam->pos.origin = roty(cam->pos.origin, 360.0 / (float)(data->flag.nb_video));
	cam->pos.direction = roty(cam->pos.direction, 360.0 / (float)(data->flag.nb_video));
}
