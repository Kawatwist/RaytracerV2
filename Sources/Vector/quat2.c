/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:20:02 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/31 13:22:49 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_quat	quat_prod(t_quat a, t_quat b)
{
	t_quat res;

	res.w = (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z);
	res.x = (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y);
	res.y = (a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x);
	res.z = (a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w);
	return (res);
}

t_quat	quat_conj(t_quat a)
{
	a.x = -(a.x);
	a.y = -(a.y);
	a.z = -(a.z);
	return (a);
}
