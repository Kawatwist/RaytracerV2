/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 14:24:24 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/25 17:23:34 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rot_cam_video2(t_data *data, t_camera *cam)
{
	cam->axerot = add_vec(cam->pos.origin,
			div_vec2(sub_vec(cam->stereo->pos.origin, cam->pos.origin), 2));
	cam->sc = add_vec(roty(sub_vec(cam->sc, cam->axerot),
			360.0 / (float)(data->flag.nb_video)), cam->axerot);
	cam->x = roty(cam->x, 360.0 / (float)(data->flag.nb_video));
	cam->y = roty(cam->y, 360.0 / (float)(data->flag.nb_video));
	cam->pos.origin = add_vec(roty(sub_vec(cam->pos.origin, cam->axerot),
		360.0 / (float)(data->flag.nb_video)), cam->axerot);
	cam->pos.direction = roty(cam->pos.direction, 360.0 /
			(float)(data->flag.nb_video));
	cam->stereo->sc = add_vec(roty(sub_vec(cam->stereo->sc, cam->axerot),
			360.0 / (float)(data->flag.nb_video)), cam->axerot);
	cam->stereo->x = roty(cam->stereo->x, 360.0 / (float)(data->flag.nb_video));
	cam->stereo->y = roty(cam->stereo->y, 360.0 / (float)(data->flag.nb_video));
	cam->stereo->pos.origin =
		add_vec(roty(sub_vec(cam->stereo->pos.origin, cam->axerot),
		360.0 / (float)(data->flag.nb_video)), cam->axerot);
	cam->stereo->pos.direction = roty(cam->stereo->pos.direction, 360.0 /
			(float)(data->flag.nb_video));
}

void		rot_cam_video(t_data *data, t_camera *cam)
{
	(void)data;
	if (!cam->mode)
	{
		cam->sc = roty(cam->sc, 360.0 / (float)(data->flag.nb_video));
		cam->x = roty(cam->x, 360.0 / (float)(data->flag.nb_video));
		cam->y = roty(cam->y, 360.0 / (float)(data->flag.nb_video));
		cam->pos.origin = roty(cam->pos.origin, 360.0 /
			(float)(data->flag.nb_video));
		cam->pos.direction = roty(cam->pos.direction, 360.0 /
			(float)(data->flag.nb_video));
	}
	else
		rot_cam_video2(data, cam);
}
