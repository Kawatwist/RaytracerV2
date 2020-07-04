/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_screenshot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luwargni <luwargni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 00:50:30 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/04 21:19:17 by luwargni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ask_screenshot(t_data *data)
{
	const	SDL_MessageBoxButtonData buttons[] = {{
			SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "TGA" }, {
				0, 1, "BMP" }, { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
				2, "Cancel" }, };
	const	SDL_MessageBoxColorScheme colorScheme = {{{255, 0, 0},
			{0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255, 0, 255}}};
	const	SDL_MessageBoxData messageboxdata = {SDL_MESSAGEBOX_INFORMATION,
			NULL, "Screenshot", "Select a format :",
			SDL_arraysize(buttons), buttons, &colorScheme};
	int		buttonid;

	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		SDL_Log("error displaying message box");
	if (buttonid == 0)
		create_screenshot(data, data->window.pxl);
	else if (buttonid == 1)
		create_screenshot_bmp(data, data->window.pxl,
		(char **)(&(("./Screenshot/screenshot_0\0"))), 1);
}