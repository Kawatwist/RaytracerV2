/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 14:24:24 by lomasse           #+#    #+#             */
/*   Updated: 2020/03/12 15:51:52 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rot_cam_video(t_data *data, t_camera *cam)
{
	(void)data;
	cam->sc = roty(cam->sc, 12.0);
	cam->x = roty(cam->x, 12.0);
	cam->y = roty(cam->y, 12.0);
	cam->pos.origin = roty(cam->pos.origin, 12.0);
	cam->pos.direction = roty(cam->pos.direction, 12.0);
}
