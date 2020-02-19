/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:03:57 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:03:57 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		hp_color(double hp)
{
	int		red;
	int		green;

	green = 255 - ((1.0 - hp) / 2.0 * 255);
	if (hp > 0.75)
		red = 0;
	else if (hp > 0.5)
		red = (0.75 - hp) * 255;
	else if (hp > 0.25)
	{
		red = 255 * 0.25 + ((0.5 - hp) * 2.0) * 255;
		green = 255 * 0.75 - ((0.5 - hp) * 255);
	}
	else
	{
		red = 255 * 0.75 - (0.25 - hp) * 255;
		green = 255 * 0.5 - ((0.25 - hp) * 2.0 * 255);
	}
	return (red * 256 * 256 + green * 256);
}

void	draw_hb_int(t_infos *infos)
{
	t_coord		screen;
	t_coord		hp_start;
	t_ratio		r;
	int			life_end_x;

	r.x = infos->hud[HP_TEXT].w / (g_win_w * HP_RATIO);
	r.y = infos->hud[HP_TEXT].h / (g_win_h * HP_RATIO / 6.0);
	hp_start.x = g_win_w / 45;
	hp_start.y = g_win_h - g_win_h / 45 - infos->hud[HP_TEXT].h / r.y;
	screen.x = hp_start.x + infos->hud[HP_TEXT].start_x / r.x;
	life_end_x = screen.x
	+ (infos->hud[HP_TEXT].end_x - infos->hud[HP_TEXT].start_x + 1) / r.x
		* infos->player.hp;
	while (screen.x <= life_end_x)
	{
		screen.y = hp_start.y + infos->hud[HP_TEXT].start_y / r.y;
		while (screen.y <= hp_start.y + (int)(infos->hud[HP_TEXT].end_y / r.y))
			infos->data[screen.y++ * g_win_w + screen.x] =
				hp_color(infos->player.hp);
		screen.x++;
	}
	draw_hb_ext(infos, &hp_start, &r);
}

void	draw_hb_ext(t_infos *infos, t_coord *hp_start, t_ratio *r)
{
	int		x;
	int		y;
	int		actual_pixel;

	x = -1;
	while (++x < (int)(infos->hud[HP_TEXT].w / r->x))
	{
		y = -1;
		while (++y < (int)(infos->hud[HP_TEXT].h / r->y))
		{
			actual_pixel = infos->hud[HP_TEXT].data[(int)(y * r->y)
									* infos->hud[HP_TEXT].w + (int)(x * r->x)];
			if (actual_pixel != infos->hud[HP_TEXT].data[0])
				infos->data[(hp_start->y + y) * g_win_w + (hp_start->x + x)] =
																actual_pixel;
		}
	}
}
