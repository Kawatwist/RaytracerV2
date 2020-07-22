/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:25:26 by lomasse           #+#    #+#             */
/*   Updated: 2020/07/22 22:43:47 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	flag_page2(int page)
{
	if (page == 2)
	{
		ft_putstr("Usage : ./RT [MAP]\n");
		ft_putstr("Maps Must be a valid file and contain 1 header\n\n");
	}
	else if (page < 8)
		ft_putstr("Page Not Actually Done\n\n");
	else
	{
		ft_putstr("Page Doesnt Exist\n\n");
		flag_help(0);
	}
}

void	flag_help(int page)
{
	static int	printed = 0;

	if (!printed)
	{
		if (!page)
		{
			ft_putstr("Usage :\t./RT <flag> [Map]\nMore info with -h / --help");
			ft_putstr(" <page number>\n\n");
			ft_putstr("Page 1 : Flag\nPage 2 : Maps Info\nPage 3 : ");
			ft_putstr("Header Maps Info\n");
			ft_putstr("Page 4 : Camera\nPage 5 : Light\nPage 6 : ");
			ft_putstr("Object (Parts 1)\nPage 7 : Object (Parts 2)\n\n");
		}
		else if (page == 1)
		{
			ft_putstr("Usage : ./RT [MAP]\n");
			ft_putstr("\n-s --screenshot : Enable Screenshot");
			ft_putstr(" option (No visual)\n");
			ft_putstr("-h --help <value> : Show help info\n\n");
		}
		else
			flag_page2(page);
	}
	printed = 1;
}
