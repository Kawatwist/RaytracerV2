#include "rt.h"

int				init_camera(t_data *data)
{
	int		i;

	if (data->obj.nb_camera == 0)
		data->obj.nb_camera = 1;
	if ((data->obj.camera = malloc(sizeof(t_camera) * (data->obj.nb_camera + 1))) == NULL)
		return (11);
	i = -1;
	while (++i <= data->obj.nb_camera)
		ft_bzero(&(data->obj.camera[i]), sizeof(t_camera));
	return (0);
}

int				init_item(t_data *data)
{
	int		i;

	if (data->obj.nb_item == 0)
		data->obj.nb_item = 1;
	if ((data->obj.item = malloc(sizeof(void *) * (data->obj.nb_item + 1))) == NULL)
		return (11);
	i = -1;
	while (++i < data->obj.nb_item)
		data->obj.item[i] = NULL;
	return (0);
}

int				parsing_files(t_data *data, char *old)
{
	char *line;
	
	line = NULL;
	init_camera(data);
	init_item(data);
	while (old != NULL || get_next_line(data->parse.fd, &line)) // free line
	{
		if (old != NULL)
		{
			line = old;
			old = NULL;
		}
		printf("Parsing : %s\n", line);
		if (!ft_strncmp("[camera", line, 7))
			parsing_camera(data, &old);
		else if (!ft_strncmp("[object", line, 7))
			parsing_obj(data, &old, line);
		else
			return (11);
	}
	return (0);
}