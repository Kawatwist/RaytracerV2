#include "rt.h"

// float		cone(void *coo, t_vec hit)
// {
// 	t_calc	c;
// 	double	tan_r2;

// 	tan_r2 = tan(((t_cone *)coo)->ang) * tan(((t_cone *)coo)->ang);
// 	c.a = hit.direction.x * hit.direction.x
// 		+ hit.direction.y * hit.direction.y
// 		- hit.direction.z * hit.direction.z * tan_r2;
// 	c.b = 2 * (hit.direction.x * hit.origin.x
// 			+ hit.direction.y * hit.origin.y
// 			- hit.direction.z * hit.origin.z * tan_r2);
// 	c.c = hit.origin.x * hit.origin.x + hit.origin.y * hit.origin.y
// 		- hit.origin.z * hit.origin.z * tan_r2;
// 	c.delta = (square(c.b) - (4 * c.a * c.c));
// 	if (c.delta > 0)
// 	{
// 		c.a *= 2;
// 		c.sqt = sqrt(c.delta);
// 		c.delta = (-c.b - c.sqt) / c.a;
// 		c.a = (-c.b + c.sqt) / c.a;
// 		if (c.delta < c.a && c.delta > 0)
// 			c.a = c.delta;
// 	}
// 	if (c.a < 0)
// 		return (-1);
// 	return (c.a);
// }

//    a   = D|D - (1+k*k)*(D|V)^2
//    b/2 = D|X - (1+k*k)*(D|V)*(X|V)
//    c   = X|X - (1+k*k)*(X|V)^2

float		cone(void *coo, t_vec ray)
{
	t_cone	cone;
	float	ang;
	t_point	co;
	t_calc	c;

	cone = *(t_cone *)coo;
	co = sub_vec(cone.origin.origin, ray.origin);
	ang = square(cos(rad(cone.ang)));
	c.a = dot_product(ray.direction, ray.direction) - (1 + square(tan(rad(cone.ang)))) * square((dot_product(ray.direction, cone.origin.direction)));
	c.b = 2 * (dot_product(ray.direction, sub_vec(cone.origin.origin, ray.origin)) - (1 + square(tan(rad(cone.ang)))) * (dot_product(ray.direction, cone.origin.direction)) * dot_product(sub_vec(cone.origin.origin, ray.origin), cone.origin.direction));
	c.c = dot_product(sub_vec(cone.origin.origin, ray.origin), sub_vec(cone.origin.origin, ray.origin)) 
	- (1 + square(tan(rad(cone.ang)))) * 
	square(dot_product(sub_vec(cone.origin.origin, ray.origin), cone.origin.direction));
	if (!c.a && c.b)
		return (-1);
	c.delta = (square(c.b) - (4 * c.a * c.c));
	if (c.delta > 0)
	{
		c.a *= 2;
		c.sqt = sqrt(c.delta);
		c.delta = (-c.b - c.sqt) / c.a;
		c.a = (-c.b + c.sqt) / c.a;
	}
	if (c.a < 0 && c.delta < 0)
		return (-1);
	else if (c.a < 0)
		return (c.delta);
	else if (c.delta < 0)
		return (c.a);

	return (c.a < c.delta ? c.a : c.delta);
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
