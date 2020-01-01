#include "rt.h"

void        setup_light(t_data *data)
{
	data->obj.nb_light = 3;
	data->obj.light = malloc(sizeof(t_light) * data->obj.nb_light);
	for (int i = 0; i < data->obj.nb_light; i++)
	{
		data->obj.light[i].color = (0xFF0000 >> (8 * i));
		data->obj.light[i].distance = 1;
		data->obj.light[i].intensity = 0.3;
		data->obj.light[i].origin = fill_vec(-1 + (1.5 * i), 0.5, -1);
	}
}