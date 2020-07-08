/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:21:06 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/08 15:48:32 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

static float	lerp(float a, float b, float w)
{
	return (((1.0 - w)) * a + (w * b));
}

static float	dot_gradient(t_point perlin[GRADIENT * GRADIENT], t_grad g)
{
	float dx;
	float dy;

	dx = g.x - (float)g.ix;
	dy = g.y - (float)g.iy;
	g.iy = g.iy % GRADIENT;
	g.ix = g.ix % GRADIENT;
	return (dx * perlin[g.iy * GRADIENT + g.ix].x +
			dy * perlin[g.iy * GRADIENT + g.ix].y);
}

float			get_perlin_marble(t_point perlin[GRADIENT * GRADIENT],
					t_point uv)
{
	t_perl	p;
	t_grad	g;
	float	marble[GRADIENT * GRADIENT];

	generate_marble(&(marble));
	uv.x = fabs(uv.x);
	uv.y = fabs(uv.y);
	init_perlin(uv, &p);
	init_grad(uv, &p, &g);
	p.n0 = dot_gradient(perlin, g);
	g.ix = p.x1;
	p.n1 = dot_gradient(perlin, g);
	p.ix0 = lerp(p.n0, p.n1, p.sx);
	g.iy = p.y1;
	p.n1 = dot_gradient(perlin, g);
	g.ix = p.x0;
	p.n0 = dot_gradient(perlin, g);
	p.ix1 = lerp(p.n0, p.n1, p.sx);
	p.value = lerp(p.ix0, p.ix1, p.sy);
	p.xyvalue = uv.x * p.xPeriod / GRADIENT + uv.y
		* p.yPeriod / GRADIENT + p.turbPower * p.value;
	p.sinvalue = fabs(sin(p.xyvalue * 3.14159));
	p.value = p.sinvalue;
	return (p.value);
}

float			get_perlin_wood(t_point perlin[GRADIENT * GRADIENT], t_point uv)
{
	t_perl	p;
	t_grad	g;
	float	wood[GRADIENT * GRADIENT];

	generate_wood(&(wood));
	if (uv.x < 0)
		uv.x = -uv.x;
	if (uv.y < 0)
		uv.y = -uv.y;
	init_perlin_wood(uv, &p);
	init_grad(uv, &p, &g);
	p.n0 = dot_gradient(perlin, g);
	g.ix = p.x1;
	p.n1 = dot_gradient(perlin, g);
	p.ix0 = lerp(p.n0, p.n1, p.sx);
	g.iy = p.y1;
	p.n1 = dot_gradient(perlin, g);
	g.ix = p.x0;
	p.n0 = dot_gradient(perlin, g);
	p.ix1 = lerp(p.n0, p.n1, p.sx);
	p.value = lerp(p.ix0, p.ix1, p.sy);
	p.distvalue = sqrt(p.xvalue * p.xvalue
		+ p.yvalue * p.yvalue) + p.turbPower * p.value;
	p.sinvalue = fabs(sin(2 * p.xPeriod * p.distvalue * 3.14159));
	return (p.sinvalue);
}

float			get_perlin_cloud(t_point perlin[GRADIENT * GRADIENT],
					t_point uv, int level)
{
	t_perl	p;
	t_grad	g;
	t_point	local;

	uv.x = fabs(uv.x);
	uv.y = fabs(uv.y);
	local.x = uv.x / level;
	local.y = uv.y / level;
	init_perlin(local, &p);
	init_grad(local, &p, &g);
	p.n0 = dot_gradient(perlin, g);
	g.ix = p.x1;
	p.n1 = dot_gradient(perlin, g);
	p.ix0 = lerp(p.n0, p.n1, p.sx);
	g.iy = p.y1;
	p.n1 = dot_gradient(perlin, g);
	g.ix = p.x0;
	p.n0 = dot_gradient(perlin, g);
	p.ix1 = lerp(p.n0, p.n1, p.sx);
	if (level > 1)
		p.value = (lerp(p.ix0, p.ix1, p.sy)
			+ get_perlin_cloud(perlin, uv, level / 2)) / 2;
	else
		p.value = lerp(p.ix0, p.ix1, p.sy);
	return (p.value);
}
