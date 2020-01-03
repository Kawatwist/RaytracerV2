#include "rt.h"

int		parsing_light(t_data *data, char **old, char *line)
{
	static int	index = 0;

	line = NULL;
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1)) // FREE LINE
	{
		// printf("LightParsing %d : %s\n", index, line);
		if (!ft_strncmp("\torigin : ", line, 10))
			data->obj.light->origin = get_point(line);
		else if (!ft_strncmp("\tcolor : ", line, 9))
			data->obj.light->color = ft_atoi_base(line + 9, 16);
		else if (!ft_strncmp("\tdistance : ", line, 12))
			data->obj.light->distance = ft_atof(line + 12);
		else if (!ft_strncmp("\tintensity : ", line, 13))
			data->obj.light->intensity = ft_atof(line + 13);
		// printf("yoooooooooo\n\n\n\n\n\n\n\n= %d\n", data->obj.light->color);
	}
	*old = line;
	index++;
	return (0);
}