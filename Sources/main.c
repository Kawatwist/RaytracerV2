/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:29:35 by lomasse           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/02/21 17:17:25 by lomasse          ###   ########.fr       */
=======
/*   Updated: 2020/02/19 19:24:23 by luwargni         ###   ########.fr       */
>>>>>>> d1764d4c27891501798fc70bbeb0496308ffe52d
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "thread.h"

/*
**		Resize Screen ?
**
**		Check Leaks
*/

// void	__attribute__((destructor)) lost();


// void		lost()
// {
// 	while(1);
// }

int			main(int argc, char *argv[])
{
	int			value;
	t_data		data;

	if (argc != 2)
	{
		ft_putendl("Usage : ./rt [Map.rt]");
		return (0);
	}
	if ((value = initialize(&data)) != 0)
		return (stop_main_execute("Error Initalize : ", &data, value));
	if ((value = parsing(&data, argc, argv)) != 0)
		return (stop_main_execute("Error Parsing : ", &data, value));
	if ((value = check_parse(&data)) != 0)
		return (stop_main_execute("Error Parse Check : ", &data, value));
	if ((value = initialize_sdl(&data)) != 0)
		return (stop_main_execute("Error Initialize SDL : ", &data, value));
	if ((value = set_icone(&data)) != 0)
		return (stop_main_execute("Icon Not Setup Correctly : ", &data, value));
	if ((value = loop(&data)) != 0 && value != 50)
		return (stop_main_execute("Run Stopped : ", &data, value));
	printf("Ici\n");
	clear_memory(&data);
	ft_putstr("See you soon !\n");
	return (0);
}
