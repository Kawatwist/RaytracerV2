#include "rt.h"

int         parsing_camera(t_data *data)
{
    static int  index = 0;
	char		*line;

	line = NULL;
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1))
	{
		printf("CameraParsing %d : %s\n", index, line);
	}
	index++;
    return (0);
}