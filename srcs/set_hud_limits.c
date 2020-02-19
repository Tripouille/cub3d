/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hud_limits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:46 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:04:47 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_hud_limits(t_hud *hud)
{
	int		y;

	set_hud_start_x(hud);
	set_hud_end_x(hud);
	y = 0;
	while (y < hud->h && hud->data[y * hud->w + (hud->w / 3)] == hud->data[0])
		y++;
	while (y < hud->h && hud->data[y * hud->w + (hud->w / 3)] != hud->data[0])
		y++;
	hud->start_y = y - 1;
	while (y < hud->h && hud->data[y * hud->w + (hud->w / 3)] == hud->data[0])
		y++;
	hud->end_y = y;
}

void	set_hud_start_x(t_hud *hud)
{
	int		x;
	int		y;

	x = 0;
	hud->start_x = -1;
	while (x < hud->w && hud->start_x == -1)
	{
		y = 0;
		while (y < hud->h && hud->data[y * hud->w + x] == hud->data[0])
			y++;
		while (y < hud->h && hud->data[y * hud->w + x] != hud->data[0])
			y++;
		while (y < hud->h && hud->data[y * hud->w + x] == hud->data[0])
			y++;
		if (y < hud->h)
			hud->start_x = x;
		x++;
	}
}

void	set_hud_end_x(t_hud *hud)
{
	int		x;
	int		y;

	x = hud->w - 1;
	hud->end_x = -1;
	while (x >= 0 && hud->end_x == -1)
	{
		y = 0;
		while (y < hud->h && hud->data[y * hud->w + x] == hud->data[0])
			y++;
		while (y < hud->h && hud->data[y * hud->w + x] != hud->data[0])
			y++;
		while (y < hud->h && hud->data[y * hud->w + x] == hud->data[0])
			y++;
		if (y < hud->h)
			hud->end_x = x + 1;
		x--;
	}
}
