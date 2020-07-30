/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_matrice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:27:49 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/30 14:50:29 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point			rotx(t_point origin, float ang)
{
	float	tmp;

	tmp = (origin.y * cos(rad(ang))) + (origin.z * (-sin(rad(ang))));
	origin.z = (origin.y * sin(rad(ang))) + (origin.z * (cos(rad(ang))));
	origin.y = tmp;
	return (origin);
}

t_point			roty(t_point origin, float ang)
{
	float	tmp;

	tmp = (origin.x * cos(rad(ang))) + (origin.z * (-sin(rad(ang))));
	origin.z = (origin.x * sin(rad(ang))) + (origin.z * (cos(rad(ang))));
	origin.x = tmp;
	origin.y = origin.y;
	return (origin);
}

t_point			rotz(t_point origin, float ang)
{
	float	tmp;

	tmp = (origin.x * cos(rad(ang))) + (origin.y * (-sin(rad(ang))));
	origin.y = (origin.x * sin(rad(ang))) + (origin.y * (cos(rad(ang))));
	origin.x = tmp;
	return (origin);
}