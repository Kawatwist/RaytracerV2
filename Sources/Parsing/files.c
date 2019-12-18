#include "rt.h"

int				parsing_files(t_data *data, char *old)
{
	char *line;
	
	printf("%s\n", old);
	if (!ft_strncmp("[camera", old, 7))
		parsing_camera(data);
	else if (!ft_strncmp("[object", old, 7))
		parsing_obj(data);
	else
		return (11);
	line = NULL;
	while (get_next_line(data->parse.fd, &line)) // free line
	{
		printf("Parsing : %s\n", line);
		if (!ft_strncmp("[camera", line, 7))
			parsing_camera(data);
		else if (!ft_strncmp("[object", line, 7))
			parsing_obj(data);
		else
			return (11);
	}
	return (0);
}