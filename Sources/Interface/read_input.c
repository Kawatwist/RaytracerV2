/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 22:52:34 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/29 13:49:11 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static char	printable_key_check_ext(t_data *data, int i)
{
	if (i == SDL_SCANCODE_KP_DIVIDE ||
	(i == SDL_SCANCODE_SLASH && !data->input.key[SDL_SCANCODE_LSHIFT]))
		return ('/');
	else if (i == SDL_SCANCODE_MINUS || i == SDL_SCANCODE_KP_MINUS)
		return ('-');
	else if (i == SDL_SCANCODE_SLASH && data->input.key[SDL_SCANCODE_LSHIFT])
		return ('?');
	else if (i == SDL_SCANCODE_1 && data->input.key[SDL_SCANCODE_LSHIFT])
		return ('!');
	else
		return (0);
}

static char	printable_key_check(t_data *data, int i)
{
	if ((i >= SDL_SCANCODE_A) && (i <= SDL_SCANCODE_Z) &&
	!data->input.key[SDL_SCANCODE_LSHIFT])
		return (i - SDL_SCANCODE_A + 'a');
	else if ((i >= SDL_SCANCODE_A) && (i <= SDL_SCANCODE_Z) &&
	data->input.key[SDL_SCANCODE_LSHIFT])
		return (i - SDL_SCANCODE_A + 'A');
	else if ((i >= SDL_SCANCODE_1) && (i <= SDL_SCANCODE_9) &&
	!data->input.key[SDL_SCANCODE_LSHIFT])
		return (i - SDL_SCANCODE_1 + '1');
	else if ((i >= SDL_SCANCODE_KP_1) && (i <= SDL_SCANCODE_KP_9))
		return (i - SDL_SCANCODE_KP_1 + '1');
	else if (i == SDL_SCANCODE_SPACE)
		return (' ');
	else if (i == SDL_SCANCODE_0 || i == SDL_SCANCODE_KP_0)
		return ('0');
	else if (i == SDL_SCANCODE_GRAVE)
		return ('~');
	else if (i == SDL_SCANCODE_PERIOD || i == SDL_SCANCODE_KP_PERIOD)
		return ('.');
	else
		return (printable_key_check_ext(data, i));
}

char		*input_hud_text(t_data *data, char *text)
{
	int				i;
	char			str[2];
	char			key_val;

	i = 0;
	key_val = 0;
	while (i <= 98)
	{
		if (key_check(data, i))
		{
			key_val = printable_key_check(data, i);
			if (key_val != 0)
			{
				str[0] = key_val;
				str[1] = '\0';
				if (text == NULL)
					text = ft_strdup(str);
				else
					text = ft_strjoinfree(text, ft_strdup(str), 3);
			}
		}
		i++;
	}
	return (text);
}
