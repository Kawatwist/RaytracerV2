#include "rt.h"

unsigned int		ray(t_thread data, t_vector ray, int bounce)
{
	t_vector		tmp;
	unsigned int	color[2];
	void			*obj;
	float			dist;
	float			coef;

	if ((obj = find_object(data, data.object, ray, &dist)) == NULL || dist == -1)
		return (0x000000);
	color[0] = find_color(obj, create_vec(set_neworigin(ray, dist), fill_vec(0,0,0)), data);
	tmp.origin = set_neworigin_neg(ray, dist);
	tmp.direction = veccpy(ray.direction);
	color[1] = find_closer_light(data, tmp, data.light, &coef);														// Shadow selon distance
	// color[0] = set_color(color[0], 0x0, coef - new_set_angle2(data, obj, data.light, tmp));
	new_set_angle(obj, data.light, tmp, &coef, data);
	color[0] = set_color(color[0], color[1], coef * 0.3);															// GAMMA
	color[0] = set_color(color[0], 0x0,  (1 - coef));
	bounce--;
	if (bounce > 0)
	{
		if (((t_sphere *)obj)->specs.effect & 0xFF)
		{
			tmp.origin = set_neworigin_neg(ray, dist);
			tmp.direction = find_reflexion(obj, tmp, data);
			color[1] = send_ray(data, tmp, bounce);
			color[0] = set_color(color[0], color[1], (((t_sphere *)obj)->specs.effect & 0xFF) / 255.0);
		}
		if (((t_sphere *)obj)->specs.effect & 0xFF00)
		{
			tmp.origin = set_neworigin_op(ray, dist);
			tmp.direction = veccpy(ray.direction); // normal texture
			color[1] = send_ray(data, tmp, bounce);
			color[0] = set_color(color[0], color[1], ((((t_sphere *)obj)->specs.effect & 0xFF00) >> 8) / 255.0);
		}
		if (((t_sphere *)obj)->specs.effect & 0xFF000000)
		{
			tmp.origin = set_neworigin_op(ray, dist);
			tmp.direction = refraction(obj, ray); // normal texture
			color[1] = send_ray(data, tmp, bounce);
			color[0] = set_color(color[0], color[1], ((((t_sphere *)obj)->specs.effect & 0xFF000000) >> 24) / 255.0);
		}
	}

	return (color[0]);
}