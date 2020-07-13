/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:49:48 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/13 17:51:14 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void    boo_value(int *value)
{
    if (*value == 1)
        *value = 0;
    else
        *value = 1;
}

void    button_stand(t_data *data, int i)
{
    data->all_button[i].pf = &boo_value;
    data->all_button[i].i = 0;
    data->all_button[i].val = 0;

    data->all_button[i].to_print = "EMPTY";
}

void    button_once_refresh(t_data *data)
{
    data->all_button[0].pf = &boo_value;
    data->all_button[0].to_print = "Single Refresh";
    data->all_button[0].val = (data->flag.asked);
    data->all_button[0].i = 0;
}

void    button_aa(t_data *data)
{
    data->all_button[1].pf = &boo_value;
    data->all_button[1].to_print = "AA";
    data->all_button[1].val = (data->flag.antialiasing);
    data->all_button[1].i = 1;
}

void    button_normals(t_data *data)
{
    data->all_button[2].pf = &boo_value;
    data->all_button[2].to_print = "Normals";
    data->all_button[2].val = (data->flag.normal);
    data->all_button[2].i = 2;
}

void    init_case(t_data *data)
{
    int i;

    i = 0;
    if (!(data->all_button = (t_case *)malloc(sizeof(t_case) * CASE_NBR)))
			return ;
    while (i < CASE_NBR)
    {
        button_stand(data, i);
        i++;
    }
    button_once_refresh(data);
    button_aa(data);
    button_normals(data);
}
void	draw_button(t_data *data, int x, int y, int state);

void	draw_background_box(t_data *data, int y);
void show_button(t_data *data)
{
    int     i;
    int         j;
    SDL_Rect    pos;

    pos.x = 245;
    pos.y = 95;
    i = (int)(data->screen.preview.slider[1].value * CASE_NBR);
    j = i;
    while (i < CASE_NBR && (i - j) * 45 < data->window.y * 0.5 - 92)
    {
        draw_button(data, pos.x, pos.y, (int)data->all_button[i].val);
        draw_background_box(data, pos.y);
        i++;
        pos.y += 45;
    }
}


void show_txt(t_data *data)
{
    int     i;
    int         j;
    SDL_Rect    pos;

    pos.x = 245;
    pos.y = 95;
    i = (int)(data->screen.preview.slider[1].value * CASE_NBR);
    j = i;
    while (i < CASE_NBR && (i - j) * 45 < data->window.y * 0.5 - 92)
    {
        data->font.str = ft_strdup(data->all_button[i].to_print);
        print_text(data, 15, pos.y, 25);
        i++;

        pos.y += 45;
    }
    data->font.str = ft_strdup("Options");
    print_text(data, 100, 40, 25);
    data->font.str = ft_strdup("Color Picker");
    print_text(data, 60, data->window.y * 0.55 + 10, 25);
}