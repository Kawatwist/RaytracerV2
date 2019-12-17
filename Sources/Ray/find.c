#include "rt.h"

void		*check_object(t_data *data, t_vec ray, float *dist)
{
	void	*close;
	int		index;
	float	value;

	*dist = -1;
	value = -1;
	close = NULL;
	while (data->obj.item[index])
	{
		value = data->dist[((t_base *)data->obj.item[index])->effect.type](data->obj.item[index], ray);
		if ((value > 0 && *dist == -1) || (value > 0 && value < *dist))
		{
			*dist = value;
			close = data->obj.item[index];
		}
		index++;
	}
	return (ret);
}