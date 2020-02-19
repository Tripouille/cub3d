/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_sprite_infos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgambard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:08:14 by jgambard          #+#    #+#             */
/*   Updated: 2020/02/15 12:39:17 by jgambard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Calculate the center_ang then the ang size (total) to determine
** the start and end angle with the tranparency ratio.
*/

void	get_sprite_angles(t_sprite *sprite, t_object *player,
								t_texture *texture)
{
	double		sinus;
	t_object	*obj;

	obj = &(sprite->object);
	sinus = (player->y - obj->y) / sprite->dist;
	if (player->x <= obj->x && player->y >= obj->y)
		sprite->center_ang = asin(sinus) / (M_PI / 180.0);
	else if (player->x > obj->x && player->y >= obj->y)
		sprite->center_ang = WEST - (asin(sinus) / (M_PI / 180.0));
	else if (player->x >= obj->x && player->y < obj->y)
		sprite->center_ang = WEST - (asin(sinus) / (M_PI / 180.0));
	else
		sprite->center_ang = 360.0 + (asin(sinus) / (M_PI / 180.0));
	sprite->ang_size = (atan((g_win_h * sprite->size_mult) / 2.0 / sprite->dist)
						/ (M_PI / 180.0)) * 2.0;
	sprite->start_ang = true_angle(sprite->center_ang
						+ (0.5 - texture->start_r) * sprite->ang_size);
	sprite->end_ang = true_angle(sprite->center_ang
						- (texture->end_r - 0.5) * sprite->ang_size);
}

/*
** Set the required sprite info for the next draw,
** and reset start_x and end_x for the crosshair.
*/

void	calculate_sprite_infos(t_infos *infos)
{
	t_sprite	*sprite;
	double		sprite_end;

	sprite = infos->sprite_list;
	while (sprite)
	{
		sprite->dist = sqrt(square(infos->player.x - sprite->object.x)
						+ square(infos->player.y - sprite->object.y));
		get_sprite_angles(sprite, &(infos->player),
							&(infos->texture[sprite->frame]));
		sprite->height = (g_win_h * sprite->size_mult) * g_win_h / (sprite->dist
			* cos((infos->player.angle - sprite->center_ang) * (M_PI / 180.0)));
		sprite_end = g_win_h / 2.0 + sprite->height / sprite->size_mult / 2.0;
		sprite->start_y = sprite_end - sprite->height
							- infos->player.z - infos->player.angle_z;
		sprite->start_x = -1;
		sprite->end_x = -1;
		sprite = sprite->next;
	}
}
