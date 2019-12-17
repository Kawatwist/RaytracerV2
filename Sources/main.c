#include "rt.h"

int		main(int argc, char *argv[])
{
	t_data		data;

	if ((value = initialize(&data)) != 0)
		return (stop_main_execute("Error Initalize : ", data, value));
	if ((value = parsing(&data, argc, argv)) != 0)
		return (stop_main_execute("Error Parsing : ", data, value));
	if ((value = loop(&data)) != 0 && value != 50)
		return (stop_main_execute("Error in Runing : ", data, value));
	ft_putstr("See you soon !\n");
	return (0);
}