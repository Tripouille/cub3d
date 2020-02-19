/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:08:19 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/16 10:08:10 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Calculate ratio to know which x pixel to draw in the sprite.
*/

void		set_sprite_ratio(t_sprite *sprite, t_texture *sprite_frame,
							double angle)
{
	sprite->ratio = true_angle(sprite->start_ang
	+ sprite_frame->start_r * sprite->ang_size - angle) / sprite->ang_size;
}

void		set_sprite_x_startend(t_sprite *sprite, int x)
{
	if (sprite->start_x == -1 || x < sprite->start_x)
		sprite->start_x = x;
	if (x > sprite->end_x)
		sprite->end_x = x;
}

/*
** Returns if angle is between start and end ang of sprite.
*/

int			is_in_sprite(t_sprite *sprite, double angle)
{
	if (true_angle(angle) >= sprite->end_ang
	&& true_angle(angle) <= sprite->start_ang)
		return (1);
	else if (true_angle(angle + 180.0) >= true_angle(sprite->end_ang + 180.0)
	&& true_angle(angle + 180.0) <= true_angle(sprite->start_ang + 180.0))
		return (1);
	return (0);
}

/*
** Draw all visible sprites. Sets start x, end x and middle end y for crosshair.
** if -> normal sprites
** else if -> sprites above walls
*/

void		draw_sprites(t_infos *infos, double angle, double wall_dist, int x)
{
	t_sprite					*spr;
	static pthread_mutex_t		m = PTHREAD_MUTEX_INITIALIZER;

	spr = infos->sprite_list;
	pthread_mutex_lock(&m);
	while (spr)
	{
		set_sprite_ratio(spr, infos->texture + spr->frame, angle);
		if (is_in_sprite(spr, angle) && spr->dist < wall_dist)
		{
			draw_sprite(infos, spr, x, g_win_h);
			set_sprite_x_startend(spr, x);
			if (x == (g_win_w - 1) / 2)
				spr->middle_end_y = spr->start_y + spr->height;
		}
		else if (is_in_sprite(spr, angle) && spr->start_y < infos->wall_start)
		{
			draw_sprite(infos, spr, x, infos->wall_start);
			set_sprite_x_startend(spr, x);
			if (x == (g_win_w - 1) / 2)
				spr->middle_end_y = infos->wall_start;
		}
		spr = spr->next;
	}
	pthread_mutex_unlock(&m);
}

/*
** Draws one column of the sprite.
*/

void		draw_sprite(t_infos *infos, t_sprite *sprite, int screen_x,
							int limit)
{
	int			screen_y;
	double		r;
	double		color_r;
	t_coord		texture;
	int			actual_pixel;

	texture.x = sprite->ratio * infos->texture[sprite->frame].w;
	r = (double)infos->texture[sprite->frame].h / sprite->height;
	color_r = sprite->height / sprite->size_mult * LIGHT_RATIO / g_win_h;
	if (color_r > 1.0)
		color_r = 1.0;
	screen_y = sprite->start_y < 0 ? 0 : sprite->start_y;
	texture.y = sprite->start_y < 0 ? -sprite->start_y : 0;
	while (screen_y < limit && texture.y < (int)sprite->height
	&& texture.x < infos->texture[sprite->frame].w)
	{
		actual_pixel = infos->texture[sprite->frame].data[(int)(texture.y * r)
								* infos->texture[sprite->frame].w + texture.x];
		if (actual_pixel != infos->texture[sprite->frame].data[0])
			infos->data[screen_y * g_win_w + screen_x] =
											get_color(actual_pixel, color_r);
		screen_y++;
		texture.y++;
	}
}
