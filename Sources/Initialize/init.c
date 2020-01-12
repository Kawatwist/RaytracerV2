#include "rt.h"

int		initialize(t_data *data)
{
	int error_value;

	ft_bzero(data, sizeof(t_data));
	if ((error_value = initialize_sdl(data)))
		return (error_value);
	data->dist[0] = sphere;
	data->dist[1] = plane;
	data->dist[2] = cone;
	data->dist[3] = cylinder;
	data->txt[0] = texture_sphere;
	data->txt[1] = texture_plan;
	data->txt[2] = texture_cone;
	data->txt[3] = texture_cylinder;
	data->move[0] = move_cam;
	data->move[1] = move_obj;
	data->move[2] = move_light;
	return (0);
}