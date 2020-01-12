#include "rt.h"

int         parsing_camera(t_data *data, char **old)
{
    static int  index = 0;
	char		*line;

	line = NULL;
	if (index >= data->obj.nb_camera)
		return (11);
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1))
	{
		if (!ft_strncmp("\torigin : ", line, 10))
			data->obj.camera[index].pos.origin = get_point(line);
		else if (!ft_strncmp("\tdirection : ", line, 13))
			data->obj.camera[index].pos.direction = get_point(line);
		free(line);
	}
	*old = line;
	index++;
    return (0);
}