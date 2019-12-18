#include "rt.h"

static int	find_type(char *type)
{
	type = ft_strchr(type, ':');
	printf("==>%s\n", (type + 1));
	if (type != NULL)
	{
		if (*(type + 1) == 's')
			return (SPHERE);
		else if (*(type + 1) == 'p')
			return (PLAN);
		else if (*(type + 1) == 'c')
			return (*(type + 2) == 'o' ? CONE : CYLINDER);
	}
	return (NONE);
}

static int	create_type(t_data *data, int index, char type)
{
	static	size_t	tab[NONE] = {sizeof(t_sphere)
			, sizeof(t_plan), sizeof(t_cone), sizeof(t_cylinder)};
	
	if ((data->obj.item[index] = malloc(tab[(int)type])) == NULL)
		return (11);
	((t_base *)data->obj.item[index])->effect.type = type;
	return (0);
}

int         parsing_obj(t_data *data, char **old, char *type)
{
    static int  index = 0;
	char		*line;
	char		val;

	line = NULL;
	printf("Yo\n");
	val = find_type(type);
	printf("Yo\n");
	if (val == NONE || create_type(data, index, val))
		return (11);
	printf("Yo\n");
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1))
	{
		printf("ObjectParsing %d : %s\n", index, line);
	}
	*old = line;
	index++;
    return (0);
}