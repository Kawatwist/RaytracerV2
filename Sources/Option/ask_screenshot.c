/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_screenshot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 00:50:30 by luwargni          #+#    #+#             */
/*   Updated: 2020/07/22 22:23:24 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void							set_button(
		SDL_MessageBoxButtonData *buttons)
{
	buttons[0].flags = 1;
	buttons[0].buttonid = 0;
	buttons[0].text = "TGA";
	buttons[1].flags = 0;
	buttons[1].buttonid = 1;
	buttons[1].text = "BMP";
	buttons[2].flags = 2;
	buttons[2].buttonid = 2;
	buttons[2].text = "Cancel";
}

static SDL_MessageBoxColorScheme	set_colorscheme(void)
{
	SDL_MessageBoxColorScheme colorscheme;

	colorscheme.colors[0].r = 255;
	colorscheme.colors[0].g = 0;
	colorscheme.colors[0].b = 0;
	colorscheme.colors[1].r = 0;
	colorscheme.colors[1].g = 255;
	colorscheme.colors[1].b = 0;
	colorscheme.colors[2].r = 255;
	colorscheme.colors[2].g = 255;
	colorscheme.colors[2].b = 0;
	colorscheme.colors[3].r = 0;
	colorscheme.colors[3].g = 0;
	colorscheme.colors[3].b = 255;
	colorscheme.colors[4].r = 255;
	colorscheme.colors[4].g = 0;
	colorscheme.colors[4].b = 255;
	return (colorscheme);
}

void								ask_screenshot(t_data *data)
{
	char							*path;
	int								buttonid;
	SDL_MessageBoxButtonData		buttons[3];
	SDL_MessageBoxColorScheme		colorscheme;
	SDL_MessageBoxData				messagebox;

	colorscheme = set_colorscheme();
	set_button(&(buttons[0]));
	messagebox.flags = SDL_MESSAGEBOX_INFORMATION;
	messagebox.buttons = buttons;
	messagebox.colorScheme = &(colorscheme);
	messagebox.title = "Screenshot";
	messagebox.window = NULL;
	messagebox.numbuttons = 3;
	messagebox.message = "Select a format for the Screenshot";
	if (SDL_ShowMessageBox(&messagebox, &buttonid) < 0)
		SDL_Log("Error displaying message box");
	if (buttonid == 0)
		create_screenshot(data, data->window.pxl);
	else if (buttonid == 1)
	{
		path = ft_strdup("./Screenshot/screenshot_0\0");
		create_screenshot_bmp(data, data->window.pxl, &(path), 1);
	}
}
