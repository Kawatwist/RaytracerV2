#include "rt.h"

int		parsing(t_data *data, int nb, char *arg[])
{
	char	*line;

	line = NULL;
	if (nb != 2)
		return (11);
	if ((data->parse.fd = open(arg[1], O_RDONLY)) == -1)
		return (11);
	if (parsing_head(data, &line))
		return (11);
	if (parsing_files(data, line))
		return (11);
	printf("Continue\n");
	exit(0);
	return (0);
}