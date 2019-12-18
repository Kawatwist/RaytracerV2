#include "rt.h"

float		cone(void *coo, t_vec ray)
{
	t_cone	cone;
	float	ang;
	t_point	co;
	t_calc	c;

	cone = *(t_cone *)coo;
	co = sub_vec(cone.origin.origin, ray.origin);
	ang = square(cos(rad(cone.ang)));
	c.a = square(dot_product(ray.direction, cone.origin.direction)) - ang;
	c.b = 2 * ((dot_product(ray.direction, cone.origin.direction) *
		dot_product(co, cone.origin.direction)) -
		(dot_product(ray.direction, co) * ang));
	c.c = square(dot_product(co, cone.origin.direction)) -
		(dot_product(co, co) * ang);
	c.delta = square(c.b) - (4 * c.a * c.c);
	if (c.delta < 0 || (c.a > 0 && !c.b))
		return (-1);
	c.c = (-c.b + (sqrt(c.delta) / (2 * c.a)));
	if (c.c <= (-c.b - (sqrtf(c.delta) / (2 * c.a))) && c.c > 0)
		return (c.c);
	else
		return (-c.b - sqrtf(c.delta) / (2 * c.a));
	return (-1);
}

float		cylinder(void *cylinder, t_vec ray)
{
	t_cylinder	c;
	t_point		os;
	t_point		tmp;
	t_calc		d;

	c = *(t_cylinder *)cylinder;
	os = cross_vec(c.origin.direction, ray.direction);
	tmp = cross_vec(c.origin.direction, sub_vec(ray.origin, c.origin.origin));
	d.a = dot_product(os, os);
	d.b = dot_product(os, cross_vec(c.origin.direction,
		sub_vec(ray.origin, c.origin.origin))) * 2.0;
	d.c = dot_product(tmp, tmp) - square(c.rayon);
	if (!d.a && d.b)
		return (-1);
	d.delta = square(d.b) - (4.0 * d.a * d.c);
	if (d.delta < 0)
		return (-1);
	d.sqt = sqrtf(d.delta);
	if ((d.c = (((-d.b) - d.sqt) / (2.0 * d.a))) > 0)
		return (d.c);
	else
		return ((-d.b) + d.sqt / (2.0 * d.a));
	return (d.c);
}

float		sphere(void *sphere, t_vec ray)
{
	t_sphere	s;
	t_point		os;
	t_calc		d;

	s = *(t_sphere *)sphere;
	os = sub_vec(ray.origin, s.origin.origin);
	d.a = dot_product(ray.direction, ray.direction);
	d.b = dot_product(ray.direction, os) * 2.0;
	d.c = dot_product(os, os) - square(s.rayon);
	d.delta = square(d.b) - (4.0 * d.a * d.c);
	d.sqt = sqrtf(d.delta);
	d.c = ((-d.b) - d.sqt) / (2.0 * d.a);
	if (d.c <= ((-d.b) + d.sqt) / (2.0 * d.a) && d.c > 0)
		return (d.c);
	else
		return (((-d.b) + d.sqt) / (2.0 * d.a));
	return (d.c);
}

float		plane(void *plane, t_vec ray)
{
	t_plan	p;
	float	t;
	float	div;

	p = *(t_plan *)plane;
	div = dot_product(ray.direction, p.origin.direction);
	if (div <= 0)
		return (-1);
	t = dot_product(sub_vec(p.origin.origin, ray.origin), p.origin.direction);
	return (t / div);
}
