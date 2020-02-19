/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:04:01 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:04:01 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_inventory(t_infos *infos, t_hud *inv)
{
	int		x;
	int		y;
	t_ratio	r;
	t_coord	texture;
	int		actual_pixel;

	r.x = inv->w / (g_win_w * INVENTORY_RATIO);
	r.y = inv->h / (g_win_h * INVENTORY_RATIO / 3.0);
	x = g_win_w - (g_win_w * INVENTORY_RATIO);
	texture.x = -1;
	while (x + ++texture.x < g_win_w)
	{
		y = g_win_h - (g_win_h * INVENTORY_RATIO / 3.0);
		texture.y = -1;
		while (y + ++texture.y < g_win_h)
		{
			actual_pixel = inv->data[(int)(texture.y * r.y)
							* inv->w + (int)(texture.x * r.x)];
			if (actual_pixel != inv->data[0])
				infos->data[(y + texture.y) * g_win_w + x + texture.x] =
																actual_pixel;
		}
	}
}

void	draw_hud(t_infos *infos)
{
	if (infos->weapon != POTATO)
		draw_weapon(infos, infos->hud + infos->weapon_frame);
	if (infos->weapon == GUN)
		draw_crosshair(infos);
	draw_hb_int(infos);
	draw_inventory(infos, infos->hud + INVENTORY_SLOT1_TEXT + infos->weapon);
}

void	draw_weapon(t_infos *infos, t_hud *weapon)
{
	t_coord	start;
	int		x;
	int		y;
	t_ratio r;
	int		actual_pixel;

	r.x = weapon->w / (g_win_w * WEAPON_RATIO / 1.5);
	r.y = weapon->h / (g_win_h * WEAPON_RATIO);
	start.x = g_win_w / 2.0 - 1 - weapon->w / r.x / 2.0;
	start.y = g_win_h - weapon->h / r.y;
	x = -1;
	while (++x < (int)(weapon->w / r.x))
	{
		y = -1;
		while (start.y + ++y < g_win_h)
		{
			actual_pixel = weapon->data[(int)(y * r.y)
							* weapon->w + (int)(x * r.x)];
			if (actual_pixel != weapon->data[0])
				infos->data[(start.y + y) * g_win_w + (start.x + x)] =
																actual_pixel;
		}
	}
}
