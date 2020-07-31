/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:44:14 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/31 16:44:22 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_quat	quat_rot(t_quat a, t_quat q)
{
	t_quat res;

	res = quat_prod(q, a);
	q = quat_conj(q);
	res = quat_prod(res, q);
	return (res);
}

static	t_quat	norm_quat(t_quat q)
{
	float s;

	s = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.x = q.x / s;
	q.y = q.y / s;
	q.z = q.z / s;
	q.w = q.w / s;
	return (q);
}

static t_point	cam_rot2(t_point origin, t_quat q)
{
	t_quat a;

	a.w = 0;
	a.x = origin.x;
	a.y = origin.y;
	a.z = origin.z;
	q = norm_quat(q);
	a = quat_rot(a, q);
	origin.x = a.x;
	origin.y = a.y;
	origin.z = a.z;
	return (origin);
}

t_point			cam_rot(t_point origin, float ang, t_point axe)
{
	t_quat q;

	axe = normalize(axe);
	q.w = cos(rad(ang) / 2);
	q.x = sin(rad(ang) / 2) * axe.x;
	q.y = sin(rad(ang) / 2) * axe.y;
	q.z = sin(rad(ang) / 2) * axe.z;
	return (cam_rot2(origin, q));
}
