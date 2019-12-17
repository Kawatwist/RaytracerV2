#include "rt.h"

int		initialize(t_data *data) // NEED TO GET WINDOW SIZE
{
	ft_bzero(*data, sizeof(t_data));
	if (initialize_sdl(data))
		return (1);
	return (0);
}