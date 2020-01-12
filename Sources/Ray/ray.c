#include "rt.h"

static t_vec		setup_refraction(t_data data, void *obj, t_vec ray, float dist)
{
	t_vec tmp;

	tmp.origin = set_neworigin_op(ray, dist);
	tmp.direction = find_refraction(data, obj, ray);
	return (tmp);
}

static t_vec		setup_opacity(t_data *data, void *obj, t_vec ray, float dist)
{
	t_vec tmp;

	(void)data;
	(void)obj;
	tmp.origin = set_neworigin_op(ray, dist);
	tmp.direction = veccpy(ray.direction);
	return (tmp);
}

static t_vec		setup_reflection(t_data *data, void *obj, t_vec ray, float dist)
{
	t_vec tmp;

	tmp.origin = set_neworigin_neg(ray, dist);
	tmp.direction = find_reflexion(obj, ray, *data);
	return (tmp);
}

unsigned int		send_ray(t_data *data, t_vec ray, int bounce)
{
	t_vec			tmp;
	unsigned int	color[2];
	void			*obj;
	float			dist[2];

	if (!(obj = check_object(data, ray, &dist[0])) || dist[0] == -1)
		return (0);

/********* Texture Color ****************/
	tmp.origin = set_neworigin(ray, dist[0]);
	tmp.direction = veccpy(ray.direction);
	color[0] = find_color(data, obj, tmp);
/********* Light Color ****************/
	tmp.origin = set_neworigin_neg(ray, dist[0]);
	tmp.direction = veccpy(ray.direction);
	tmp.direction = find_normal(obj, tmp);
	color[0] = ray_to_light(data, tmp, color[0]);

	if (bounce)
	{
		bounce--;
		if (((t_base *)obj)->effect.reflection)
		{
			tmp = setup_reflection(data, obj, ray, dist[0]);
			color[1] = send_ray(data, tmp, bounce);
			color[0] = set_color(color[0], color[1], ((t_base *)obj)->effect.reflection / 255.0);
		}
		if (((t_base *)obj)->effect.refraction)
		{
			tmp = setup_refraction(*data, obj, ray, dist[0]);
			color[1] = send_ray(data, tmp, bounce);
			color[0] = set_color(color[0], color[1], ((t_base *)obj)->effect.refraction / 255.0);
		}
		if (((t_base *)obj)->effect.opacity)
		{
			tmp = setup_opacity(data, obj, ray, dist[0]);
			color[1] = send_ray(data, tmp, bounce);
			color[0] = set_color(color[0], color[1], ((t_base *)obj)->effect.opacity / 255.0);
		}
	}
	return (color[0]);
}