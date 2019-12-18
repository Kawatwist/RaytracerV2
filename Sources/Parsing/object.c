#include "rt.h"

int         parsing_obj(t_data *data)
{
    static int  index = 0;
	char		*line;

	line = NULL;
	while (get_next_line(data->parse.fd, &line) && ft_strncmp("\t\t", line, 2))
	{
		printf("ObjectParsing : %s\n", line);
	}
	index++;
    return (0);
}