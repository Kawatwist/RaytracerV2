/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:21:10 by cbilga            #+#    #+#             */
/*   Updated: 2020/07/08 15:22:58 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

void init_perlin(t_point uv, t_perl *p)
{
    p->x0 = (int)uv.x;
    p->x1 = p->x0 + 1;
    p->y0 = (int)uv.y;
    p->y1 = p->y0 + 1;
    p->sx = uv.x - (float)p->x0;
    p->sy = uv.y - (float)p->y0;
    p->xPeriod = 50;
    p->yPeriod = 100;
    p->turbPower = 5;
}
void init_perlin_wood(t_point uv, t_perl *p)
{
    p->x0 = (int)uv.x;
    p->x1 = p->x0 + 1;
    p->y0 = (int)uv.y;
    p->y1 = p->y0 + 1;
    p->sx = uv.x - (float)p->x0;
    p->sy = uv.y - (float)p->y0;
    p->xPeriod = 50;
    p->yPeriod = 100;
    p->turbPower = 0.02;
    p->turbSize = 20.0;
    p->xvalue = (uv.x - GRADIENT / 4) / (float)GRADIENT;
    p->yvalue = (uv.y - GRADIENT / 4) / (float)GRADIENT;

}

void init_grad(t_point uv, t_perl *p, t_grad *g)
{
    g->ix = p->x0;
    g->iy = p->y0;
    g->x = uv.x;
    g->y = uv.y;
}