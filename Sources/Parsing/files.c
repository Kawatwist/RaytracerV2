#include "rt.h"

int				parsing_files(t_data *data, char *old)
{
	char *line;
	
	(void)old;
	line = NULL;
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