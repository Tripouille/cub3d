/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:08:23 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:08:23 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_ratio_xy(t_hud *hud, t_sprite *sprite, double *rx, double *ry)
{
	*rx = hud->w / (double)(sprite->end_x - sprite->start_x + 1);
	*ry = hud->h / ((sprite->height < g_win_h ? sprite->height : g_win_h)
					* SPRITE_HP_RATIO);
}

void	draw_sprites_life(t_infos *infos, t_sprite *sprite)
{
	while (sprite)
	{
		if (sprite->type + SPRITE >= SPRITE2 && sprite->start_x != -1)
			draw_sprite_hb_int(infos, sprite);
		sprite = sprite->next;
	}
}

/*
** Draw interior of hb, then calls draw_sprite_hb_ext to draw exterior around.
** hud->start_x = where interior begins in hb texture.
*/

void	draw_sprite_hb_int(t_infos *infos, t_sprite *sprite)
{
	t_coord		screen;
	t_ratio		r;
	t_coord		hp_start;
	int			life_end_x;
	t_hud		*hud;

	hud = infos->hud
		+ (sprite->size_mult == BIG ? BOSS_HP_TEXT : ENEMY_HP_TEXT);
	set_ratio_xy(hud, sprite, &r.x, &r.y);
	hp_start.y = sprite->start_y - sprite->height * SPRITE_HP_RATIO;
	hp_start.x = sprite->start_x;
	if (hp_start.y < 0)
		hp_start.y = 0;
	screen.x = hp_start.x + hud->start_x / r.x;
	life_end_x = screen.x + (hud->end_x - hud->start_x + 1) / r.x
											* sprite->object.hp;
	while (screen.x <= life_end_x)
	{
		screen.y = hp_start.y + hud->start_y / r.y;
		while (screen.y <= (int)(hp_start.y + hud->end_y / r.y))
			infos->data[screen.y++ * g_win_w + screen.x] =
				hp_color(sprite->object.hp);
		screen.x++;
	}
	draw_sprite_hb_ext(infos, sprite, &hp_start, &r);
}

void	draw_sprite_hb_ext(t_infos *infos, t_sprite *sprite,
							t_coord *hp_start, t_ratio *r)
{
	int			x;
	int			y;
	t_hud		*hud;
	int			actual_pixel;

	hud = infos->hud
		+ (sprite->size_mult == BIG ? BOSS_HP_TEXT : ENEMY_HP_TEXT);
	x = -1;
	while (++x < (int)(hud->w / r->x))
	{
		y = -1;
		while (++y < (int)(hud->h / r->y))
		{
			actual_pixel =
				hud->data[(int)(y * r->y) * hud->w + (int)(x * r->x)];
			if (actual_pixel != hud->data[0])
				infos->data[(hp_start->y + y) * g_win_w + (hp_start->x + x)] =
																actual_pixel;
		}
	}
}
