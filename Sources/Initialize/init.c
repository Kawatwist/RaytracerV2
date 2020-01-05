#include "rt.h"

int		initialize(t_data *data) // NEED TO GET WINDOW SIZE
{
	ft_bzero(data, sizeof(t_data));
	if (initialize_sdl(data))
		return (1);
	data->dist[0] = sphere;
	data->dist[1] = plane;
	data->dist[2] = cone;
	data->dist[3] = cylinder;
	data->txt[0] = texture_sphere;
	data->txt[1] = texture_plan;
	data->txt[2] = texture_cylinder;
	return (0);
}