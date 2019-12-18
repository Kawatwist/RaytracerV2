#include "rt.h"

unsigned int			set_color(unsigned int base, unsigned int new, float percent)
{
	unsigned char	color[4];
	unsigned int	ret;

	color[0] = 0xFF;
	color[1] = (((base & 0xFF0000) >> 16) * (1 - percent)) +
		(((new & 0xFF0000) >> 16) * percent);
	color[2] = (((base & 0xFF00) >> 8) * (1 - percent)) +
		(((new & 0xFF00) >> 8) * percent);
	color[3] = ((base & 0xFF) * (1 - percent)) + ((new & 0xFF) * percent);
	ret = color[0] + (color[1] << 8) + (color[2] << 16) + (color[3] << 24);
	return (ret);
}

static unsigned int     find_texture_color(t_data *data, void *obj, t_vec ray)
{
    t_point     uv;
	unsigned int ret;

	uv = data->txt[(int)((t_base *)obj)->effect.type] (data, obj, ray);
	ret = data->texture[((t_base *)obj)->effect.id_texture].data[(int)(uv.x + (uv.y * data->texture[((t_base *)obj)->effect.id_texture].w))];
    return (ret);
}

unsigned int			find_color(t_data *data, void *obj, t_vec ray)
{
	Uint32	colortmp;

    if (!((t_base *)obj)->effect.texture)
		return (((t_base *)obj)->effect.color);
	colortmp = find_texture_color(data, obj, ray);
	return (set_color(((t_base *)obj)->effect.color, colortmp,
		((t_base *)obj)->effect.texture / 255));
}
