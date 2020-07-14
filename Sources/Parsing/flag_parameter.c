/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parameter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:24:29 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/14 23:18:27 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			word_flag(t_data *data, int argc, char **argv, int *index)
{
	if (!ft_strncmp("screenshot", &(argv[*index][2]), 10))
	{
		data->flag.screen = 1;
		return (0);
	}
	else if (!ft_strncmp("help", &(argv[*index][2]), 4))
	{
		if (*index + 1 >= argc)
			flag_help(0);
		else
			flag_help(ft_atoi(argv[*index + 1]));
		return (0);
	}
	else
		return (10);
}

int			short_flag(t_data *data, int argc, char **argv, int *index, int *index2)
{
	if (argv[*index][*index2] == 's')
	{
		data->flag.screen = 1;
		return (2);
	}
	else if (argv[*index][*index2] == 'h')
	{
		if (*index + 1 >= argc)
			flag_help(0);
		else
			flag_help(ft_atoi(argv[*index + 1]));
		return (2);
	}
	else if (argv[*index][1] == '-' && !word_flag(data, argc, argv, index))
		;
	else
		return (10);
	return (0);
}

int			flag(t_data *data, int argc, char **argv)
{
	int		index;
	int		index2;
	int		value;

	index = 1;
	while(index < argc)
	{
		if (argv[index][0] == '-')
		{
			index2 = 1;
			while ((value = short_flag(data, argc, argv, &index, &index2)) == 2)
			{
				index2++;
				if (argv[index][index2] == '\0')
					break;
			}
			if (value == 10)
			{
				ft_putstr("Flag Doesnt exsit\n");
				return (10);
			}
		}
		else if (index < argc - 1)
			return (0);
		index++;
	}
	return (0);
}
