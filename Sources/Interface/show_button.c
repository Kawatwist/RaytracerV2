/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <anboilea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:49:48 by anboilea          #+#    #+#             */
/*   Updated: 2020/07/19 17:52:55 by anboilea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*

A mettre dans le header
void    boo_value_diapo(t_data *data, int val);
void    boo_value_normals(t_data *data, int val);
void    boo_value_show(t_data *data, int val);
void    boo_value_aa(t_data *data, int val);
void    boo_value_quality(t_data *data, int val);
void    boo_value_refresh(t_data *data, int val);
*/

void    boo_value_diapo(t_data *data, int val)
{
    if (data->flag.diapo == val)
        data->flag.diapo = 0;
    else
        data->flag.diapo = val;
}

void    boo_value_normals(t_data *data, int val)
{
    if (data->flag.normal == val)
        data->flag.normal = 0;
    else
        data->flag.normal = val;
}

void    boo_value_show(t_data *data, int val)
{
    if (data->flag.show == val)
        data->flag.show = 0;
    else
        data->flag.show = val;
}

void    boo_value_aa(t_data *data, int val)
{
    if (data->flag.antialiasing == val)
        data->flag.antialiasing = 0;
    else
        data->flag.antialiasing = val;
}

void    boo_value_quality(t_data *data, int val)
{
    if (data->flag.pixel  == val)
        data->flag.pixel = 0;
    else
        data->flag.pixel = val;
}

void    boo_value_refresh(t_data *data, int val)
{
    if (data->flag.asked  == val)
        data->flag.asked = 0;
    else
        data->flag.asked = val;
}

void    boo_value(t_data *data, int val)
{
    (void)data;
    (void)val;
    int value = 0;
    if (value == 1)
        value = 0;
    else
        value = 1;
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
    data->all_button[0].pf = &boo_value_refresh;
    data->all_button[0].to_print = "Single Refresh";
    data->all_button[0].val = data->flag.asked;
    data->all_button[0].i = 0;
}

void    button_aa(t_data *data)
{
    data->all_button[1].pf = &boo_value_aa;
    data->all_button[1].to_print = "AA";
    data->all_button[1].val = data->flag.antialiasing;
    data->all_button[1].i = 3;
}

void    button_normals(t_data *data)
{
    data->all_button[2].pf = &boo_value_normals;
    data->all_button[2].to_print = "Normals";
    data->all_button[2].val = data->flag.normal;
    data->all_button[2].i = 1;
}

void    button_quality(t_data *data)
{
    data->all_button[3].pf = &boo_value_quality;
    data->all_button[3].to_print = "Quality";
    data->all_button[3].val = data->flag.pixel;
    data->all_button[3].i = 3;
}

void    button_show(t_data *data)
{
    data->all_button[4].pf = &boo_value_show;
    data->all_button[4].to_print = "Show";
    data->all_button[4].val = data->flag.show;
    data->all_button[4].i = 1;
}

void    button_diapo(t_data *data)
{
    data->all_button[5].pf = &boo_value_diapo;
    data->all_button[5].to_print = "Diapo";
    data->all_button[5].val = data->flag.diapo;
    data->all_button[5].i = 1;
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
    button_quality(data);
    button_show(data);
    button_diapo(data);
}

void	draw_button(t_data *data, int x, int y, t_case c);
void	draw_background_box(t_data *data, int y);
char		*input_hud_text(t_data*data, char *text);

void draw_nbvideo_bg(t_data *data)
{
    SDL_Rect	dst;

	dst.x = 10;
	dst.y = 5;
	dst.w = 200;
	dst.h = 20;
	draw_rect(data, dst, 0xffffff);
    dst.x = 11;
	dst.y = 6;
	dst.w = 198;
	dst.h = 18;
	draw_rect(data, dst, 0x333333);    
}

void    video_settings(t_data *data)
{
    (void)data;

    static char *str = NULL;
    
    if (data->input.x >= 10 && data->input.x <= 210
        && data->input.y >= 5 && data->input.y <= 25
        && data->input.button & SDL_BUTTON_LEFT)
     {
        data->flag.typing = 1;
        if (str)
        free(str);
        str = NULL;
     }
     else if (data->input.button & SDL_BUTTON_LEFT)
        data->flag.typing = 0;

    if (data->flag.typing == 1 && ft_strlen(str) < 4)
        str = input_hud_text(data, str);
    if (str)
    {
        data->font.str = ft_strdup(str); // RENTRER LA VALEUR DANS NB_VIDEO
        print_text(data, 115, 4, 20);
    }
}

void    show_button(t_data *data)
{
    int     i;
    int         j;
    SDL_Rect    pos;

    pos.x = 245;
    pos.y = 95;
    i = (int)(data->screen.preview.slider[1].value * CASE_NBR);
    j = i;
    init_case(data);
    while (i < CASE_NBR && (i - j) * 45 < data->window.y * 0.5 - 92)
    {  
        draw_button(data, pos.x, pos.y, data->all_button[i]);
        draw_background_box(data, pos.y);
        i++;
        pos.y += 45;
    }
    
   
}

void click_button(t_data *data)
{
    int start;
    int val;
    int blabla;
    int max_val;

    start = (int)(data->screen.preview.slider[1].value * CASE_NBR);
    if (data->input.x <= 300 && data->input.y <= data->window.y * 0.55 && data->input.button != data->input.oldbutton && data->input.button == 1)
    {
        if (data->input.y >= 95 && data->input.x >= 245 && data->input.x <= 245 + 30)
        {
            blabla = (data->input.y) / 45;
            blabla = blabla - 2;
            data->input.y = data->input.y % 45;
            if (data->input.y > 6 && data->input.y < 41)
            {
                if (blabla + start < CASE_NBR)
                {
                    max_val = data->all_button[blabla + start].i;
                    if (max_val < 1)
                        max_val = 1;
                    val = (data->input.x - 245) / (30 / max_val);
                    data->all_button[blabla + start].pf(data, val + 1);
                }
            }
        }
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