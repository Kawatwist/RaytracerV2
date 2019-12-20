#include "rt.h"

int		parsing(t_data *data, int nb, char *arg[])
{
	char	*line;

	line = NULL;
	if (nb != 2)
		return (11);
	if ((data->parse.fd = open(arg[1], O_RDONLY)) == -1)
		return (11);
	if (parsing_head(data, &line))
		return (11);
	if (parsing_files(data, line))
		return (11);
	data->percent = 0;
    (data->obj.camera[0]).pos.origin = fill_vec(0.5, 0.5, -0.5);
    (data->obj.camera[0]).pos.direction = normalize(fill_vec(0, 0, 1));
    (data->obj.camera[0]).sc = fill_vec(0.0, 0.0, 0.0);
    (data->obj.camera[0]).x = fill_vec(1.0 / data->window.xscreen, 0, 0);
    (data->obj.camera[0]).y = fill_vec(0, 1.0 / data->window.yscreen, 0);
	return (0);
}