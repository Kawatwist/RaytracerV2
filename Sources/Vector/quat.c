/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:44:14 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/30 18:46:17 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_quat	quat_prod(t_quat a, t_quat b)
{
	t_quat res;

	res.w = (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z);
	res.x = (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y);
	res.y = (a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x);
	res.z = (a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w);
	return (res);
}

static t_quat	quat_conj(t_quat a)
{
	a.x = -(a.x);
	a.y = -(a.y);
	a.z = -(a.z);
	return (a);
}

static t_quat quat_rot(t_quat a, t_quat q)
{
	t_quat res;

	res = quat_prod(q, a);
	q = quat_conj(q);
	res = quat_prod(res, q);
	return (res);
}

static t_quat norm_quat(t_quat q)
{
	float s;

	s = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.x = q.x / s;
	q.y = q.y / s;
	q.z = q.z / s;
	q.w = q.w / s;
	return (q);
}

t_point	cam_rotx(t_point origin, float ang)
{
	t_quat q;
	t_quat a;

	a.w = 0;
	a.x = origin.x;
	a.y = origin.y;
	a.z = origin.z;
	q.w = cos(rad(ang) / 2);
	q.x = sin(rad(ang) / 2);
	q.y = 0;
	q.z = 0;
	q = norm_quat(q);
	a = quat_rot(a, q);
	origin.x = a.x;
	origin.y = a.y;
	origin.z = a.z;
	return (origin);
}

t_point	cam_roty(t_point origin, float ang)
{
	t_quat q;
	t_quat a;

	a.w = 0;
	a.x = origin.x;
	a.y = origin.y;
	a.z = origin.z;
	q.w = cos(rad(ang) / 2);
	q.x = 0;
	q.y = sin(rad(ang) / 2);
	q.z = 0;
	q = norm_quat(q);
	a = quat_rot(a, q);
	origin.x = a.x;
	origin.y = a.y;
	origin.z = a.z;
	return (origin);
}

t_point	cam_rotz(t_point origin, float ang)
{
	t_quat q;
	t_quat a;

	a.w = 0;
	a.x = origin.x;
	a.y = origin.y;
	a.z = origin.z;
	q.w = cos(rad(ang) / 2);
	q.x = 0;
	q.y = 0;
	q.z = sin(rad(ang) / 2);
	q = norm_quat(q);
	a = quat_rot(a, q);
	origin.x = a.x;
	origin.y = a.y;
	origin.z = a.z;
	return (origin);
}
