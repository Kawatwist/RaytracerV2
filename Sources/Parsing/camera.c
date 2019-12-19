#include "rt.h"

int         parsing_camera(t_data *data, char **old)
{
    static int  index = 0;
	char		*line;

	line = NULL;
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1)) // FREE LINE
	{
		printf("CameraParsing %d : %s\n", index, line);
	}
	*old = line;
	index++;
    return (0);
}