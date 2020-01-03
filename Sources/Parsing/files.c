#include "rt.h"

int				init_light(t_data *data)
{
	if (data->obj.nb_light == 0)
		data->obj.nb_light = 1;
	if ((data->obj.light = malloc(sizeof(t_light) * (data->obj.nb_light))) == NULL)
		return (1);
	ft_bzero(data->obj.light, sizeof(t_light) * (data->obj.nb_light));	
	return (0);
}

int				init_camera(t_data *data)
{
	if (data->obj.nb_camera == 0)
		data->obj.nb_camera = 1;
	if ((data->obj.camera = malloc(sizeof(t_camera) * (data->obj.nb_camera + 1))) == NULL)
		return (1);
	ft_bzero(data->obj.camera, sizeof(t_camera) * (data->obj.nb_camera + 1));
	return (0);
}

static int		init_texture(t_data *data)
{
	t_tga	*img;
	int		index;

	if (data->obj.nb_texture < 0)
		data->obj.nb_texture = 0;
	if ((data->texture = malloc(sizeof(t_tga *) * data->obj.nb_texture)) == NULL)
		return (1);
	ft_bzero(data->texture, sizeof(t_tga*) * data->obj.nb_texture);
	index = 0;

	printf("Debut Texture\n");
	while (index < data->obj.nb_texture)
	{
		printf("Before [%s]\n", data->obj.texture[index]);
		img = load_tga(data->obj.texture[index]);
		printf("Load %p\n", img);
		if (img == NULL)
			img = load_tga("./Texture/Invalid.tga");
		printf("Coucou %p\n", img);
		data->texture[index] = img;
		printf("Coucou %p\n", img);
		index++;
	}
	printf("End Texture\n");
	return (0);
}

int				init_item(t_data *data)
{
	int		i;

	if (data->obj.nb_item < 0)
		data->obj.nb_item = 0;
	if ((data->obj.item = malloc(sizeof(void *) * (data->obj.nb_item + 1))) == NULL)
		return (11);
	i = -1;
	while (++i <= data->obj.nb_item)
		data->obj.item[i] = NULL;
	data->obj.item[data->obj.nb_item - 1] = NULL;
	data->obj.item[data->obj.nb_item] = NULL;
	return (0);
}

int				parsing_files(t_data *data, char *old)
{
	char *line;

	line = NULL;
	init_camera(data);
	init_item(data);
	init_light(data);//rajout
	init_texture(data);
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
		else if (!ft_strncmp("[light", line, 6))
			parsing_light(data, &old, line);//rajout
		else
			return (11);
	}
	return (0);
}
