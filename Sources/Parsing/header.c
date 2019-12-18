#include "rt.h"

static int	first_texture(t_data *data)
{
	int		i;

	i = 0;
	if ((data->obj.texture = malloc(sizeof(char *) * data->obj.nb_texture + 1)) == NULL)
		return (1);
	while (i < data->obj.nb_texture)
	{
		data->obj.texture[i] = NULL;
		i++;
	}
	return (0);
}

static int	fill_texture(t_data *data, char *line)
{
	static int	index = 0;
	int			len;

	if (index == 0)
		if (first_texture(data))
			return (1);
	len = ft_strrchr(line, '"') - ft_strchr(line, '"') - 1;
	if (!(len > 0 && len < 100))
		return (11);
	data->obj.texture[index] = ft_strndup(ft_strchr(line, '"') + 1, len);
	index++;
	return (0);
}

int         parsing_head(t_data *data ,char **ret)
{
    char        *line;

    line = NULL;
    if (!(get_next_line(data->parse.fd, &line)))
        return (11);
    if (ft_strncmp("[header]", line, 8))
        return (11);
    while ((get_next_line(data->parse.fd, &line)) && ft_strncmp("\t\t", line, 2)) // Free line
    {
        if (!ft_strncmp("\tcamera : ", line, 10))
			data->obj.nb_camera = ft_atoi(&(line[10]));
        else if (!ft_strncmp("\tobject : ", line, 10))
			data->obj.nb_item = ft_atoi(&(line[10]));
        else if (!ft_strncmp("\tnb_texture : ", line, 14))
			data->obj.nb_texture = ft_atoi(&(line[14]));
		else if (!ft_strncmp("\ttextures : ", line, 11))
		{
			if (fill_texture(data, line))
				return (11);
		}
		else
			break ;
    }
	*ret = line;
    return (0);
}